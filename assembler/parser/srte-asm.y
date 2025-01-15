%require "3.2"
%define parse.error verbose
%define api.namespace {srte_parser}
%define api.value.type variant
%param {token_buf &tbuf}
%parse-param {parser_drv &driver}
%parse-param {const std::string &filename}
%parse-param {parser_private &privd} // only way to make a class member in bison
%locations

%code requires {

#include "ast.hpp"
#include "type.hpp"
#include "drv/drv.hpp"
#include "drv/parser-private.hpp"
#include <cstdint>

class token_buf;

}

%code provides {

srte_parser::parser::token_type yylex(srte_parser::parser::value_type *value, srte_parser::parser::location_type *location, token_buf &tbuf);

}

%token DECL_KW_VERSION ".version"
%token DECL_KW_GLOBAL ".global"

%token KW_STATIC "static"
%token KW_CONST "const"

%token<rt_type_basic *> TYPE_I8
%token<rt_type_basic *> TYPE_I16
%token<rt_type_basic *> TYPE_I32
%token<rt_type_basic *> TYPE_I64
%token<rt_type_basic *> TYPE_I128
%token<rt_type_basic *> TYPE_U8
%token<rt_type_basic *> TYPE_U16
%token<rt_type_basic *> TYPE_U32
%token<rt_type_basic *> TYPE_U64
%token<rt_type_basic *> TYPE_U128
%token<rt_type_basic *> TYPE_BOOL
%token<rt_type_basic *> TYPE_VOID
%token<rt_type_basic *> TYPE_STR

%token<std::string> V_DEC
%token<std::string> V_HEX
%token<std::string> V_BIN
%token<std::string> V_STR

%token<std::string> NAME

%token LBRACKET
%token RBRACKET
%token COMMA
%token COLON
%token EQUALS
%token NEWLINES
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
#define CLM() privd.mods = 0

#define BASIC(t) std::make_shared<rt_type_basic>(t)

%}

%type <std::shared_ptr<version_decl>> version_statement
%type <std::vector<std::shared_ptr<global_var>>> global_vars
%type <std::shared_ptr<global_var>> global_var
%type <std::string> name
%type <std::shared_ptr<value_base>> value
%type <std::shared_ptr<type_id>> type
%type <std::shared_ptr<rt_type_base>> any_type
%type <std::shared_ptr<rt_type_basic>> builtin_type
%type <std::shared_ptr<rt_type_ref>> reference_type

%%

program:
    version_statement global_vars end_of_stmt {
        auto as_unit = new assembly_unit(filename);
        for (auto gv : $2) {
            as_unit->push_constant(gv);
        }

        as_unit->set_version($1);
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
        $$.push_back($2);
        $$.insert($$.end(), $1.begin(), $1.end());
    }
    ;

global_var:
    DECL_KW_GLOBAL modifiers name COLON type
    {
        $$ = std::make_shared<global_var>(B_LOC(@$), privd.mods, $name, $type, nullptr);
        CLM();
    }
    | DECL_KW_GLOBAL modifiers name COLON type EQUALS value
    {
        $$ = std::make_shared<global_var>(B_LOC(@$), privd.mods, $name, $type, $value);
        CLM();
    }
    ;

modifiers:
    /* empty */
    | modifiers KW_CONST
    {
        if ((privd.mods & global_var::MOD_CONST) != 0) {
            WARN(@$, "Modifier 'const' already present");
        } else {
            privd.mods |= global_var::MOD_CONST;
        }
    }
    | modifiers KW_STATIC
    {
        if ((privd.mods & global_var::MOD_STATIC) != 0) {
            WARN(@$, "Modifier 'static' already present");
        } else {
            privd.mods |= global_var::MOD_STATIC;
        }
    }
    ;

type:
    any_type
    {
        $$ = std::make_shared<type_id>(B_LOC(@$), $1);
    }    

any_type:
    builtin_type { $$ = $1; }
    | reference_type { $$ = $1; }
    //| array_type { $$ = $1; }
    ;

reference_type:
    AMP any_type
    {
        $$ = std::make_shared<rt_type_ref>($2);
    }
    ;

array_type:
    LBRACKET V_DEC COLON type RBRACKET
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

value:
    V_DEC 
    {
        $$ = std::make_shared<int_value>(B_LOC(@$), $1, PLI(@$, $1, 10), int_value::format::Dec);
    }
    | V_BIN
    {
        $$ = std::make_shared<int_value>(B_LOC(@$), $1, PLI(@$, $1, 2), int_value::format::Bin);
    }
    | V_HEX
    {
        $$ = std::make_shared<int_value>(B_LOC(@$), $1, PLI(@$, $1, 16), int_value::format::Hex);
    }
    | V_STR
    {
        $$ = std::make_shared<str_value>(B_LOC(@$), $1, str_value::format::Utf8, std::vector<unsigned char>($1.begin(), $1.end()));
    }
    //| array_literal
    //| address_of
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
    value |
    value_list COMMA value
    ;

end_of_stmt:
    NEWLINES |
    YYEOF
    ;
