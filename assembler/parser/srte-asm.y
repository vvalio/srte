%require "3.2"
%define parse.error verbose
%define api.namespace {srte_parser}
%define api.value.type variant
%param {token_buf &tbuf}
%parse-param {parser_drv &driver}
%parse-param {const std::string &filename}
%locations

%code requires {

#include "ast.hpp"
#include "type.hpp"
#include "drv/drv.hpp"
#include <cstdint>

class token_buf;

}

%code provides {

srte_parser::parser::token_type yylex(srte_parser::parser::value_type *value, srte_parser::parser::location_type *location, token_buf &tbuf);

}

%token DECL_KW_VERSION ".version"
%token DECL_KW_GLOBAL ".global"
%token DECL_KW_FUNC ".func"
%token DECL_KW_END ".end"

%token KW_STATIC "static"
%token KW_CONST "const"
%token KW_FUNC "func"
%token KW_EXPORT "export"
%token KW_PURE "pure"

%token KW_UTF8
%token KW_UTF16
%token KW_UTF32

%token TYPE_I8
%token TYPE_I16
%token TYPE_I32
%token TYPE_I64
%token TYPE_I128
%token TYPE_U8
%token TYPE_U16
%token TYPE_U32
%token TYPE_U64
%token TYPE_U128
%token TYPE_BOOL
%token TYPE_VOID
%token TYPE_STR

%token<std::string> V_DEC
%token<std::string> V_HEX
%token<std::string> V_BIN
%token<std::string> V_STR

%token<std::string> NAME

%token LBRACKET
%token RBRACKET
%token LPAREN
%token RPAREN
%token COMMA
%token COLON
%token EQUALS
%token NEWLINES
%token UNDERSCORE
%token RET_ARROW
%token AMP

%{
#include "srte-asm-parser.hpp"
#include "numparse.hpp"

using location = srte_parser::location;
using syntax_error = srte_parser::parser::syntax_error;

static std::shared_ptr<ast_location> get_loc(location l, const std::string &filename) {
    return ast_location::from_bison_location(l, filename);
}

static void  __attribute__((noreturn)) fatal(location l, std::string msg) {
    std::cerr << "At " << l << ":\n";
    std::cerr << "\t" << msg << "\n";
    std::abort();
}

void srte_parser::parser::error(const location& l, const std::string& msg) {
    driver.add_error(parse_error(msg, l));
}

void warning(srte_parser::parser *p, const location &l, const std::string& msg) {
    std::cerr << "WARN: " << msg << "\n";
    std::cerr << "At: " << l << "\n";
}

static std::uint8_t parse_byte(srte_parser::parser *p, const std::string &d, location l) {
    bool ofw = false,
        err = false;
    const std::uint8_t result = parse_native(d.c_str(), 16, 8, ofw, err);
    if (ofw) {
        p->error(l, "Expected byte between 0-255");
    } else if (err) {
        fatal(l, "Value token of type V_HEX was unparsable");
    }

    return result;
}

static std::uint64_t parse_int(srte_parser::parser *p, location l, const std::string &d, int base) {
    bool ofw = false,
        err = false;
    const std::uint64_t result = parse_native(d.c_str(), base, 64, ofw, err);
    if (ofw) {
        p->error(l, "Integer value too large!");
    } else if (err) {
        fatal(l, "Value token was unparsable");
    }

    return result;
}

#define PB(d, l) parse_byte(this, d, l)
#define PLI(l, d, b) parse_int(this, l, d, b)
#define B_LOC(rp) std::shared_ptr(get_loc(rp, filename))
#define WARN(rp, msg) warning(this, rp, msg)

#define BASIC(t) std::make_shared<rt_type_basic>(t)

#define APPEND_MOD(at, result, accum, bit)                                  \
    do {                                                                    \
        if ((accum & bit) != 0) {                                           \
            WARN(at, "Effective modifier bit " #bit " declared twice");     \
        }                                                                   \
                                                                            \
        result = accum | bit;                                               \
    } while (0)

#define APPEND_LR_VECTOR(result, previous, newelem)                             \
    std::copy(previous.begin(), previous.end(), std::back_inserter(result));    \
    result.push_back(newelem)                                                   \

%}

%type <std::shared_ptr<version_decl>> version_statement

%type <std::vector<std::shared_ptr<global_var>>> global_vars
%type <std::shared_ptr<global_var>> global_var
%type <std::uint32_t> modifiers function_modifiers

%type <std::string> name
%type <std::shared_ptr<literal_base>> literal
%type <std::shared_ptr<int_literal>> num_literal

%type <std::shared_ptr<type_id>> type
%type <std::shared_ptr<rt_type_base>> any_type
%type <std::shared_ptr<rt_type_basic>> builtin_type
%type <std::shared_ptr<rt_type_ref>> reference_type
%type <std::shared_ptr<rt_type_function>> function_type

%type <std::shared_ptr<rt_type_base>> return_type
%type <std::vector<std::shared_ptr<rt_type_base>>> param_types
%type <std::shared_ptr<rt_type_array>> array_type

%type <str_literal::encoding> str_encoding_specifier

%type <std::shared_ptr<function_def>> function_def
%type <std::vector<std::shared_ptr<function_def>>> function_defs
%type <std::shared_ptr<function_param>> function_param
%type <std::vector<std::shared_ptr<function_param>>> function_params

%%

program:
    NEWLINES version_statement global_vars function_defs end_of_stmt {
        auto as_unit = new assembly_unit(filename);
        as_unit->add_globals($global_vars);
        as_unit->add_functions($function_defs);

        as_unit->set_version($version_statement);
        driver.set_result(std::shared_ptr<assembly_unit>(as_unit));
    }
    ;

version_statement:
    /* empty */ { $$ = nullptr; }
    | DECL_KW_VERSION V_HEX V_HEX V_HEX end_of_stmt
    {
        $$ = std::make_shared<version_decl>(B_LOC(@$), PB($2, @2), PB($3, @3), PB($4, @4)); 
    }
    ;

global_vars: { $$ = {}; }
    | global_vars global_var end_of_stmt
    {
        APPEND_LR_VECTOR($$, $1, $2);
    }
    ;

global_var:
    DECL_KW_GLOBAL modifiers name COLON type
    {
        $$ = std::make_shared<global_var>(B_LOC(@$), $modifiers, $name, $type, nullptr);
    }
    | DECL_KW_GLOBAL modifiers name COLON type EQUALS literal
    {
        $$ = std::make_shared<global_var>(B_LOC(@$), $modifiers, $name, $type, $literal);
    }
    ;

modifiers:
    /* empty */ { $$ = 0; }
    | modifiers KW_CONST
    {
        APPEND_MOD(@$, $$, $1, global_var::MOD_CONST);
    }
    | modifiers KW_STATIC
    {
        APPEND_MOD(@$, $$, $1, global_var::MOD_STATIC);
    }
    ;

function_defs: { $$ = {}; }
    | function_defs function_def end_of_stmt
    {
        APPEND_LR_VECTOR($$, $1, $2);
    }
    ;

function_def:
    DECL_KW_FUNC function_modifiers name function_params RET_ARROW type NEWLINES function_end
    {
        $$ = std::make_shared<function_def>(B_LOC(@$), $function_modifiers, $name, $type, $function_params);
    }
    ;

function_params: { $$ = {}; }
    | function_param
    {
        $$.push_back($1);
    }
    | function_params COMMA function_param
    {
        APPEND_LR_VECTOR($$, $1, $3);
    }
    ;

function_param:
    type
    {
        $$ = std::make_shared<function_param>(B_LOC(@$), $type, 0, 0);
    }
    ;

function_modifiers: { $$ = 0; }
    | function_modifiers KW_EXPORT
    {
        APPEND_MOD(@$, $$, $1, function_def::MOD_EXPORT);
    }
    | function_modifiers KW_PURE
    {
        APPEND_MOD(@$, $$, $1, function_def::MOD_PURE);
    }
    | function_modifiers KW_STATIC
    {
        APPEND_MOD(@$, $$, $1, function_def::MOD_STATIC);
    }
    ;

function_end:
    DECL_KW_END KW_FUNC
    | DECL_KW_END
    ;

type:
    any_type
    {
        $$ = std::make_shared<type_id>(B_LOC(@$), $1);
    }
    ; 

any_type:
    builtin_type { $$ = $1; }
    | reference_type { $$ = $1; }
    | function_type { $$ = $1; }
    | array_type { $$ = $1; }
    ;

reference_type:
    AMP any_type
    {
        $$ = std::make_shared<rt_type_ref>($2);
    }
    ;

array_type:
    LBRACKET num_literal COLON any_type RBRACKET
    {
        auto capacity = $2->get_val();
        if (capacity > UINT32_MAX) {
            error(@$, "Integer value out of range for array capacity");
            capacity = 0;
        }

        $$ = std::make_shared<rt_type_array>($4, (std::uint32_t) capacity);
    }
    ;

function_type:
    KW_FUNC param_types RET_ARROW return_type
    {
        $$ = std::make_shared<rt_type_function>($4, $2);
    }
    ;

param_types:
    {
        $$ = {};
    }
    | any_type
    {
        $$.push_back($1);
    }
    | param_types COMMA any_type
    {
        APPEND_LR_VECTOR($$, $1, $3);
    }
    ;

return_type:
    {
        $$ = nullptr;
    }
    | UNDERSCORE
    {
        $$ = nullptr;
    }
    | any_type
    {
        $$ = $1;
    }
    ;

builtin_type:
    TYPE_I8     { $$ = BASIC(rt_type_kind::I8); }
    | TYPE_I16  { $$ = BASIC(rt_type_kind::I16); }
    | TYPE_I32  { $$ = BASIC(rt_type_kind::I32); }
    | TYPE_I64  { $$ = BASIC(rt_type_kind::I64); }
    | TYPE_I128 { $$ = BASIC(rt_type_kind::I128); }
    | TYPE_U8   { $$ = BASIC(rt_type_kind::U8); }
    | TYPE_U16  { $$ = BASIC(rt_type_kind::U16); }
    | TYPE_U32  { $$ = BASIC(rt_type_kind::U32); }
    | TYPE_U64  { $$ = BASIC(rt_type_kind::U64); }
    | TYPE_U128 { $$ = BASIC(rt_type_kind::U128); }
    | TYPE_BOOL { $$ = BASIC(rt_type_kind::Bool); }
    | TYPE_VOID { $$ = BASIC(rt_type_kind::Void); }
    | TYPE_STR  { $$ = BASIC(rt_type_kind::String); }
    ;

literal:
    num_literal
    {
        $$ = $1;
    }
    | str_encoding_specifier V_STR
    {
        $$ = std::make_shared<str_literal>(B_LOC(@$), $2, $1, std::vector<unsigned char>($2.begin(), $2.end()));
    }
    //| array_literal
    //| address_of
    ;

str_encoding_specifier:
    {
        $$ = str_literal::encoding::Utf8;
    }
    | KW_UTF8
    {
        $$ = str_literal::encoding::Utf8;
    }
    | KW_UTF16
    {
        $$ = str_literal::encoding::Utf16;
    }
    | KW_UTF32
    {
        $$ = str_literal::encoding::Utf32;
    }
    ;

num_literal:
    V_DEC 
    {
        $$ = std::make_shared<int_literal>(B_LOC(@$), $1, PLI(@$, $1, 10), int_literal::format::Dec);
    }
    | V_BIN
    {
        $$ = std::make_shared<int_literal>(B_LOC(@$), $1, PLI(@$, $1, 2), int_literal::format::Bin);
    }
    | V_HEX
    {
        $$ = std::make_shared<int_literal>(B_LOC(@$), $1, PLI(@$, $1, 16), int_literal::format::Hex);
    }
    ;

address_of:
    AMP name
    ;

name:
    NAME
    {
        $$ = $1;
    }
    | V_STR
    {
        $$ = $1;
    }
    ;

array_literal:
    LBRACKET RBRACKET |
    LBRACKET value_list RBRACKET
    ;

value_list:
    literal |
    value_list COMMA literal
    ;

end_of_stmt:
    NEWLINES |
    YYEOF
    ;
