// A Bison parser, made by GNU Bison 3.8.2.

// Skeleton implementation for Bison LALR(1) parsers in C++

// Copyright (C) 2002-2015, 2018-2021 Free Software Foundation, Inc.

// This program is free software: you can redistribute it and/or modify
// it under the terms of the GNU General Public License as published by
// the Free Software Foundation, either version 3 of the License, or
// (at your option) any later version.

// This program is distributed in the hope that it will be useful,
// but WITHOUT ANY WARRANTY; without even the implied warranty of
// MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
// GNU General Public License for more details.

// You should have received a copy of the GNU General Public License
// along with this program.  If not, see <https://www.gnu.org/licenses/>.

// As a special exception, you may create a larger work that contains
// part or all of the Bison parser skeleton and distribute that work
// under terms of your choice, so long as that work isn't itself a
// parser generator using the skeleton or a modified version thereof
// as a parser skeleton.  Alternatively, if you modify or redistribute
// the parser skeleton itself, you may (at your option) remove this
// special exception, which will cause the skeleton and the resulting
// Bison output files to be licensed under the GNU General Public
// License without this special exception.

// This special exception was added by the Free Software Foundation in
// version 2.2 of Bison.

// DO NOT RELY ON FEATURES THAT ARE NOT DOCUMENTED in the manual,
// especially those whose name start with YY_ or yy_.  They are
// private implementation details that can be changed or removed.

// First part of user prologue.
#line 62 "assembler/parser/srte-asm.y"

#include "srte-asm-parser.hpp"
#include "numparse.hpp"

using location = srte_parser::location;
using syntax_error = srte_parser::parser::syntax_error;

static std::shared_ptr<ast_location> get_loc(location l, const std::string &filename) {
    return ast_location::from_bison_location(l, filename);
}

static void __attribute__((noreturn)) fatal(location l, std::string msg) {
    std::cerr << "At " << l << ":\n";
    std::cerr << "\t" << msg << "\n";
    std::abort();
}

void srte_parser::parser::error(const location &l, const std::string &msg) { driver.add_error(parse_error(msg, l)); }

static std::uint8_t parse_byte(srte_parser::parser *p, const std::string &d, location l) {
    bool ofw = false, err = false;
    const std::uint8_t result = parse_native(d.c_str(), 16, 8, ofw, err);
    if (ofw) {
        p->error(l, "Expected byte between 0-255");
    } else if (err) {
        fatal(l, "Value token of type V_HEX was unparsable");
    }

    return result;
}

#define PB(d, l) parse_byte(this, d, l)
#define B_LOC(rp) std::shared_ptr(get_loc(rp, filename))
#define BASIC(t) new rt_type_basic(t)

#line 81 "assembler/parser/srte-asm-parser.cpp"

#include "srte-asm-parser.hpp"

#ifndef YY_
#if defined YYENABLE_NLS && YYENABLE_NLS
#if ENABLE_NLS
#include <libintl.h> // FIXME: INFRINGES ON USER NAME SPACE.
#define YY_(msgid) dgettext("bison-runtime", msgid)
#endif
#endif
#ifndef YY_
#define YY_(msgid) msgid
#endif
#endif

// Whether we are compiled with exception support.
#ifndef YY_EXCEPTIONS
#if defined __GNUC__ && !defined __EXCEPTIONS
#define YY_EXCEPTIONS 0
#else
#define YY_EXCEPTIONS 1
#endif
#endif

#define YYRHSLOC(Rhs, K) ((Rhs)[K].location)
/* YYLLOC_DEFAULT -- Set CURRENT to span from RHS[1] to RHS[N].
   If N is 0, then set CURRENT to the empty location which ends
   the previous symbol: RHS[0] (always defined).  */

#ifndef YYLLOC_DEFAULT
#define YYLLOC_DEFAULT(Current, Rhs, N)                                                                                \
    do                                                                                                                 \
        if (N) {                                                                                                       \
            (Current).begin = YYRHSLOC(Rhs, 1).begin;                                                                  \
            (Current).end = YYRHSLOC(Rhs, N).end;                                                                      \
        } else {                                                                                                       \
            (Current).begin = (Current).end = YYRHSLOC(Rhs, 0).end;                                                    \
        }                                                                                                              \
    while (false)
#endif

// Enable debugging if requested.
#if YYDEBUG

// A pseudo ostream that takes yydebug_ into account.
#define YYCDEBUG                                                                                                       \
    if (yydebug_)                                                                                                      \
    (*yycdebug_)

#define YY_SYMBOL_PRINT(Title, Symbol)                                                                                 \
    do {                                                                                                               \
        if (yydebug_) {                                                                                                \
            *yycdebug_ << Title << ' ';                                                                                \
            yy_print_(*yycdebug_, Symbol);                                                                             \
            *yycdebug_ << '\n';                                                                                        \
        }                                                                                                              \
    } while (false)

#define YY_REDUCE_PRINT(Rule)                                                                                          \
    do {                                                                                                               \
        if (yydebug_)                                                                                                  \
            yy_reduce_print_(Rule);                                                                                    \
    } while (false)

#define YY_STACK_PRINT()                                                                                               \
    do {                                                                                                               \
        if (yydebug_)                                                                                                  \
            yy_stack_print_();                                                                                         \
    } while (false)

#else // !YYDEBUG

#define YYCDEBUG                                                                                                       \
    if (false)                                                                                                         \
    std::cerr
#define YY_SYMBOL_PRINT(Title, Symbol) YY_USE(Symbol)
#define YY_REDUCE_PRINT(Rule) static_cast<void>(0)
#define YY_STACK_PRINT() static_cast<void>(0)

#endif // !YYDEBUG

#define yyerrok (yyerrstatus_ = 0)
#define yyclearin (yyla.clear())

#define YYACCEPT goto yyacceptlab
#define YYABORT goto yyabortlab
#define YYERROR goto yyerrorlab
#define YYRECOVERING() (!!yyerrstatus_)

#line 3 "assembler/parser/srte-asm.y"
namespace srte_parser {
#line 179 "assembler/parser/srte-asm-parser.cpp"

/// Build a parser object.
parser::parser(token_buf &tbuf_yyarg, parser_drv &driver_yyarg, const std::string &filename_yyarg)
#if YYDEBUG
    : yydebug_(false), yycdebug_(&std::cerr),
#else
    :
#endif
      tbuf(tbuf_yyarg), driver(driver_yyarg), filename(filename_yyarg) {
}

parser::~parser() {}

parser::syntax_error::~syntax_error() YY_NOEXCEPT YY_NOTHROW {}

/*---------.
| symbol.  |
`---------*/

// basic_symbol.
template <typename Base>
parser::basic_symbol<Base>::basic_symbol(const basic_symbol &that) : Base(that), value(), location(that.location) {
    switch (this->kind()) {
        case symbol_kind::S_TYPE_I8:      // TYPE_I8
        case symbol_kind::S_TYPE_I16:     // TYPE_I16
        case symbol_kind::S_TYPE_I32:     // TYPE_I32
        case symbol_kind::S_TYPE_I64:     // TYPE_I64
        case symbol_kind::S_TYPE_I128:    // TYPE_I128
        case symbol_kind::S_TYPE_U8:      // TYPE_U8
        case symbol_kind::S_TYPE_U16:     // TYPE_U16
        case symbol_kind::S_TYPE_U32:     // TYPE_U32
        case symbol_kind::S_TYPE_U64:     // TYPE_U64
        case symbol_kind::S_TYPE_U128:    // TYPE_U128
        case symbol_kind::S_TYPE_BOOL:    // TYPE_BOOL
        case symbol_kind::S_TYPE_VOID:    // TYPE_VOID
        case symbol_kind::S_TYPE_STR:     // TYPE_STR
        case symbol_kind::S_builtin_type: // builtin_type
            value.copy<rt_type_basic *>(YY_MOVE(that.value));
            break;

        case symbol_kind::S_type: // type
            value.copy<std::shared_ptr<type_id>>(YY_MOVE(that.value));
            break;

        case symbol_kind::S_version_statement: // version_statement
            value.copy<std::shared_ptr<version_decl>>(YY_MOVE(that.value));
            break;

        case symbol_kind::S_V_DEC: // V_DEC
        case symbol_kind::S_V_HEX: // V_HEX
        case symbol_kind::S_V_BIN: // V_BIN
        case symbol_kind::S_V_STR: // V_STR
        case symbol_kind::S_NAME:  // NAME
        case symbol_kind::S_name:  // name
            value.copy<std::string>(YY_MOVE(that.value));
            break;

        case symbol_kind::S_global_vars: // global_vars
            value.copy<std::vector<std::shared_ptr<global_var>>>(YY_MOVE(that.value));
            break;

        default: break;
    }
}

template <typename Base> parser::symbol_kind_type parser::basic_symbol<Base>::type_get() const YY_NOEXCEPT {
    return this->kind();
}

template <typename Base> bool parser::basic_symbol<Base>::empty() const YY_NOEXCEPT {
    return this->kind() == symbol_kind::S_YYEMPTY;
}

template <typename Base> void parser::basic_symbol<Base>::move(basic_symbol &s) {
    super_type::move(s);
    switch (this->kind()) {
        case symbol_kind::S_TYPE_I8:      // TYPE_I8
        case symbol_kind::S_TYPE_I16:     // TYPE_I16
        case symbol_kind::S_TYPE_I32:     // TYPE_I32
        case symbol_kind::S_TYPE_I64:     // TYPE_I64
        case symbol_kind::S_TYPE_I128:    // TYPE_I128
        case symbol_kind::S_TYPE_U8:      // TYPE_U8
        case symbol_kind::S_TYPE_U16:     // TYPE_U16
        case symbol_kind::S_TYPE_U32:     // TYPE_U32
        case symbol_kind::S_TYPE_U64:     // TYPE_U64
        case symbol_kind::S_TYPE_U128:    // TYPE_U128
        case symbol_kind::S_TYPE_BOOL:    // TYPE_BOOL
        case symbol_kind::S_TYPE_VOID:    // TYPE_VOID
        case symbol_kind::S_TYPE_STR:     // TYPE_STR
        case symbol_kind::S_builtin_type: // builtin_type
            value.move<rt_type_basic *>(YY_MOVE(s.value));
            break;

        case symbol_kind::S_type: // type
            value.move<std::shared_ptr<type_id>>(YY_MOVE(s.value));
            break;

        case symbol_kind::S_version_statement: // version_statement
            value.move<std::shared_ptr<version_decl>>(YY_MOVE(s.value));
            break;

        case symbol_kind::S_V_DEC: // V_DEC
        case symbol_kind::S_V_HEX: // V_HEX
        case symbol_kind::S_V_BIN: // V_BIN
        case symbol_kind::S_V_STR: // V_STR
        case symbol_kind::S_NAME:  // NAME
        case symbol_kind::S_name:  // name
            value.move<std::string>(YY_MOVE(s.value));
            break;

        case symbol_kind::S_global_vars: // global_vars
            value.move<std::vector<std::shared_ptr<global_var>>>(YY_MOVE(s.value));
            break;

        default: break;
    }

    location = YY_MOVE(s.location);
}

// by_kind.
parser::by_kind::by_kind() YY_NOEXCEPT : kind_(symbol_kind::S_YYEMPTY) {}

#if 201103L <= YY_CPLUSPLUS
parser::by_kind::by_kind(by_kind &&that) YY_NOEXCEPT : kind_(that.kind_) { that.clear(); }
#endif

parser::by_kind::by_kind(const by_kind &that) YY_NOEXCEPT : kind_(that.kind_) {}

parser::by_kind::by_kind(token_kind_type t) YY_NOEXCEPT : kind_(yytranslate_(t)) {}

void parser::by_kind::clear() YY_NOEXCEPT { kind_ = symbol_kind::S_YYEMPTY; }

void parser::by_kind::move(by_kind &that) {
    kind_ = that.kind_;
    that.clear();
}

parser::symbol_kind_type parser::by_kind::kind() const YY_NOEXCEPT { return kind_; }

parser::symbol_kind_type parser::by_kind::type_get() const YY_NOEXCEPT { return this->kind(); }

// by_state.
parser::by_state::by_state() YY_NOEXCEPT : state(empty_state) {}

parser::by_state::by_state(const by_state &that) YY_NOEXCEPT : state(that.state) {}

void parser::by_state::clear() YY_NOEXCEPT { state = empty_state; }

void parser::by_state::move(by_state &that) {
    state = that.state;
    that.clear();
}

parser::by_state::by_state(state_type s) YY_NOEXCEPT : state(s) {}

parser::symbol_kind_type parser::by_state::kind() const YY_NOEXCEPT {
    if (state == empty_state)
        return symbol_kind::S_YYEMPTY;
    else
        return YY_CAST(symbol_kind_type, yystos_[+state]);
}

parser::stack_symbol_type::stack_symbol_type() {}

parser::stack_symbol_type::stack_symbol_type(YY_RVREF(stack_symbol_type) that)
    : super_type(YY_MOVE(that.state), YY_MOVE(that.location)) {
    switch (that.kind()) {
        case symbol_kind::S_TYPE_I8:      // TYPE_I8
        case symbol_kind::S_TYPE_I16:     // TYPE_I16
        case symbol_kind::S_TYPE_I32:     // TYPE_I32
        case symbol_kind::S_TYPE_I64:     // TYPE_I64
        case symbol_kind::S_TYPE_I128:    // TYPE_I128
        case symbol_kind::S_TYPE_U8:      // TYPE_U8
        case symbol_kind::S_TYPE_U16:     // TYPE_U16
        case symbol_kind::S_TYPE_U32:     // TYPE_U32
        case symbol_kind::S_TYPE_U64:     // TYPE_U64
        case symbol_kind::S_TYPE_U128:    // TYPE_U128
        case symbol_kind::S_TYPE_BOOL:    // TYPE_BOOL
        case symbol_kind::S_TYPE_VOID:    // TYPE_VOID
        case symbol_kind::S_TYPE_STR:     // TYPE_STR
        case symbol_kind::S_builtin_type: // builtin_type
            value.YY_MOVE_OR_COPY<rt_type_basic *>(YY_MOVE(that.value));
            break;

        case symbol_kind::S_type: // type
            value.YY_MOVE_OR_COPY<std::shared_ptr<type_id>>(YY_MOVE(that.value));
            break;

        case symbol_kind::S_version_statement: // version_statement
            value.YY_MOVE_OR_COPY<std::shared_ptr<version_decl>>(YY_MOVE(that.value));
            break;

        case symbol_kind::S_V_DEC: // V_DEC
        case symbol_kind::S_V_HEX: // V_HEX
        case symbol_kind::S_V_BIN: // V_BIN
        case symbol_kind::S_V_STR: // V_STR
        case symbol_kind::S_NAME:  // NAME
        case symbol_kind::S_name:  // name
            value.YY_MOVE_OR_COPY<std::string>(YY_MOVE(that.value));
            break;

        case symbol_kind::S_global_vars: // global_vars
            value.YY_MOVE_OR_COPY<std::vector<std::shared_ptr<global_var>>>(YY_MOVE(that.value));
            break;

        default: break;
    }

#if 201103L <= YY_CPLUSPLUS
    // that is emptied.
    that.state = empty_state;
#endif
}

parser::stack_symbol_type::stack_symbol_type(state_type s, YY_MOVE_REF(symbol_type) that)
    : super_type(s, YY_MOVE(that.location)) {
    switch (that.kind()) {
        case symbol_kind::S_TYPE_I8:      // TYPE_I8
        case symbol_kind::S_TYPE_I16:     // TYPE_I16
        case symbol_kind::S_TYPE_I32:     // TYPE_I32
        case symbol_kind::S_TYPE_I64:     // TYPE_I64
        case symbol_kind::S_TYPE_I128:    // TYPE_I128
        case symbol_kind::S_TYPE_U8:      // TYPE_U8
        case symbol_kind::S_TYPE_U16:     // TYPE_U16
        case symbol_kind::S_TYPE_U32:     // TYPE_U32
        case symbol_kind::S_TYPE_U64:     // TYPE_U64
        case symbol_kind::S_TYPE_U128:    // TYPE_U128
        case symbol_kind::S_TYPE_BOOL:    // TYPE_BOOL
        case symbol_kind::S_TYPE_VOID:    // TYPE_VOID
        case symbol_kind::S_TYPE_STR:     // TYPE_STR
        case symbol_kind::S_builtin_type: // builtin_type
            value.move<rt_type_basic *>(YY_MOVE(that.value));
            break;

        case symbol_kind::S_type: // type
            value.move<std::shared_ptr<type_id>>(YY_MOVE(that.value));
            break;

        case symbol_kind::S_version_statement: // version_statement
            value.move<std::shared_ptr<version_decl>>(YY_MOVE(that.value));
            break;

        case symbol_kind::S_V_DEC: // V_DEC
        case symbol_kind::S_V_HEX: // V_HEX
        case symbol_kind::S_V_BIN: // V_BIN
        case symbol_kind::S_V_STR: // V_STR
        case symbol_kind::S_NAME:  // NAME
        case symbol_kind::S_name:  // name
            value.move<std::string>(YY_MOVE(that.value));
            break;

        case symbol_kind::S_global_vars: // global_vars
            value.move<std::vector<std::shared_ptr<global_var>>>(YY_MOVE(that.value));
            break;

        default: break;
    }

    // that is emptied.
    that.kind_ = symbol_kind::S_YYEMPTY;
}

#if YY_CPLUSPLUS < 201103L
parser::stack_symbol_type &parser::stack_symbol_type::operator=(const stack_symbol_type &that) {
    state = that.state;
    switch (that.kind()) {
        case symbol_kind::S_TYPE_I8:      // TYPE_I8
        case symbol_kind::S_TYPE_I16:     // TYPE_I16
        case symbol_kind::S_TYPE_I32:     // TYPE_I32
        case symbol_kind::S_TYPE_I64:     // TYPE_I64
        case symbol_kind::S_TYPE_I128:    // TYPE_I128
        case symbol_kind::S_TYPE_U8:      // TYPE_U8
        case symbol_kind::S_TYPE_U16:     // TYPE_U16
        case symbol_kind::S_TYPE_U32:     // TYPE_U32
        case symbol_kind::S_TYPE_U64:     // TYPE_U64
        case symbol_kind::S_TYPE_U128:    // TYPE_U128
        case symbol_kind::S_TYPE_BOOL:    // TYPE_BOOL
        case symbol_kind::S_TYPE_VOID:    // TYPE_VOID
        case symbol_kind::S_TYPE_STR:     // TYPE_STR
        case symbol_kind::S_builtin_type: // builtin_type
            value.copy<rt_type_basic *>(that.value);
            break;

        case symbol_kind::S_type: // type
            value.copy<std::shared_ptr<type_id>>(that.value);
            break;

        case symbol_kind::S_version_statement: // version_statement
            value.copy<std::shared_ptr<version_decl>>(that.value);
            break;

        case symbol_kind::S_V_DEC: // V_DEC
        case symbol_kind::S_V_HEX: // V_HEX
        case symbol_kind::S_V_BIN: // V_BIN
        case symbol_kind::S_V_STR: // V_STR
        case symbol_kind::S_NAME:  // NAME
        case symbol_kind::S_name:  // name
            value.copy<std::string>(that.value);
            break;

        case symbol_kind::S_global_vars: // global_vars
            value.copy<std::vector<std::shared_ptr<global_var>>>(that.value);
            break;

        default: break;
    }

    location = that.location;
    return *this;
}

parser::stack_symbol_type &parser::stack_symbol_type::operator=(stack_symbol_type &that) {
    state = that.state;
    switch (that.kind()) {
        case symbol_kind::S_TYPE_I8:      // TYPE_I8
        case symbol_kind::S_TYPE_I16:     // TYPE_I16
        case symbol_kind::S_TYPE_I32:     // TYPE_I32
        case symbol_kind::S_TYPE_I64:     // TYPE_I64
        case symbol_kind::S_TYPE_I128:    // TYPE_I128
        case symbol_kind::S_TYPE_U8:      // TYPE_U8
        case symbol_kind::S_TYPE_U16:     // TYPE_U16
        case symbol_kind::S_TYPE_U32:     // TYPE_U32
        case symbol_kind::S_TYPE_U64:     // TYPE_U64
        case symbol_kind::S_TYPE_U128:    // TYPE_U128
        case symbol_kind::S_TYPE_BOOL:    // TYPE_BOOL
        case symbol_kind::S_TYPE_VOID:    // TYPE_VOID
        case symbol_kind::S_TYPE_STR:     // TYPE_STR
        case symbol_kind::S_builtin_type: // builtin_type
            value.move<rt_type_basic *>(that.value);
            break;

        case symbol_kind::S_type: // type
            value.move<std::shared_ptr<type_id>>(that.value);
            break;

        case symbol_kind::S_version_statement: // version_statement
            value.move<std::shared_ptr<version_decl>>(that.value);
            break;

        case symbol_kind::S_V_DEC: // V_DEC
        case symbol_kind::S_V_HEX: // V_HEX
        case symbol_kind::S_V_BIN: // V_BIN
        case symbol_kind::S_V_STR: // V_STR
        case symbol_kind::S_NAME:  // NAME
        case symbol_kind::S_name:  // name
            value.move<std::string>(that.value);
            break;

        case symbol_kind::S_global_vars: // global_vars
            value.move<std::vector<std::shared_ptr<global_var>>>(that.value);
            break;

        default: break;
    }

    location = that.location;
    // that is emptied.
    that.state = empty_state;
    return *this;
}
#endif

template <typename Base> void parser::yy_destroy_(const char *yymsg, basic_symbol<Base> &yysym) const {
    if (yymsg)
        YY_SYMBOL_PRINT(yymsg, yysym);
}

#if YYDEBUG
template <typename Base> void parser::yy_print_(std::ostream &yyo, const basic_symbol<Base> &yysym) const {
    std::ostream &yyoutput = yyo;
    YY_USE(yyoutput);
    if (yysym.empty())
        yyo << "empty symbol";
    else {
        symbol_kind_type yykind = yysym.kind();
        yyo << (yykind < YYNTOKENS ? "token" : "nterm") << ' ' << yysym.name() << " (" << yysym.location << ": ";
        YY_USE(yykind);
        yyo << ')';
    }
}
#endif

void parser::yypush_(const char *m, YY_MOVE_REF(stack_symbol_type) sym) {
    if (m)
        YY_SYMBOL_PRINT(m, sym);
    yystack_.push(YY_MOVE(sym));
}

void parser::yypush_(const char *m, state_type s, YY_MOVE_REF(symbol_type) sym) {
#if 201103L <= YY_CPLUSPLUS
    yypush_(m, stack_symbol_type(s, std::move(sym)));
#else
    stack_symbol_type ss(s, sym);
    yypush_(m, ss);
#endif
}

void parser::yypop_(int n) YY_NOEXCEPT { yystack_.pop(n); }

#if YYDEBUG
std::ostream &parser::debug_stream() const { return *yycdebug_; }

void parser::set_debug_stream(std::ostream &o) { yycdebug_ = &o; }

parser::debug_level_type parser::debug_level() const { return yydebug_; }

void parser::set_debug_level(debug_level_type l) { yydebug_ = l; }
#endif // YYDEBUG

parser::state_type parser::yy_lr_goto_state_(state_type yystate, int yysym) {
    int yyr = yypgoto_[yysym - YYNTOKENS] + yystate;
    if (0 <= yyr && yyr <= yylast_ && yycheck_[yyr] == yystate)
        return yytable_[yyr];
    else
        return yydefgoto_[yysym - YYNTOKENS];
}

bool parser::yy_pact_value_is_default_(int yyvalue) YY_NOEXCEPT { return yyvalue == yypact_ninf_; }

bool parser::yy_table_value_is_error_(int yyvalue) YY_NOEXCEPT { return yyvalue == yytable_ninf_; }

int parser::operator()() { return parse(); }

int parser::parse() {
    int yyn;
    /// Length of the RHS of the rule being reduced.
    int yylen = 0;

    // Error handling.
    int yynerrs_ = 0;
    int yyerrstatus_ = 0;

    /// The lookahead symbol.
    symbol_type yyla;

    /// The locations where the error started and ended.
    stack_symbol_type yyerror_range[3];

    /// The return value of parse ().
    int yyresult;

#if YY_EXCEPTIONS
    try
#endif // YY_EXCEPTIONS
    {
        YYCDEBUG << "Starting parse\n";

        /* Initialize the stack.  The initial state will be set in
           yynewstate, since the latter expects the semantical and the
           location values to have been already stored, initialize these
           stacks with a primary value.  */
        yystack_.clear();
        yypush_(YY_NULLPTR, 0, YY_MOVE(yyla));

    /*-----------------------------------------------.
    | yynewstate -- push a new symbol on the stack.  |
    `-----------------------------------------------*/
    yynewstate:
        YYCDEBUG << "Entering state " << int(yystack_[0].state) << '\n';
        YY_STACK_PRINT();

        // Accept?
        if (yystack_[0].state == yyfinal_)
            YYACCEPT;

        goto yybackup;

    /*-----------.
    | yybackup.  |
    `-----------*/
    yybackup:
        // Try to take a decision without lookahead.
        yyn = yypact_[+yystack_[0].state];
        if (yy_pact_value_is_default_(yyn))
            goto yydefault;

        // Read a lookahead token.
        if (yyla.empty()) {
            YYCDEBUG << "Reading a token\n";
#if YY_EXCEPTIONS
            try
#endif // YY_EXCEPTIONS
            {
                yyla.kind_ = yytranslate_(yylex(&yyla.value, &yyla.location, tbuf));
            }
#if YY_EXCEPTIONS
            catch (const syntax_error &yyexc) {
                YYCDEBUG << "Caught exception: " << yyexc.what() << '\n';
                error(yyexc);
                goto yyerrlab1;
            }
#endif // YY_EXCEPTIONS
        }
        YY_SYMBOL_PRINT("Next token is", yyla);

        if (yyla.kind() == symbol_kind::S_YYerror) {
            // The scanner already issued an error message, process directly
            // to error recovery.  But do not keep the error token as
            // lookahead, it is too special and may lead us to an endless
            // loop in error recovery. */
            yyla.kind_ = symbol_kind::S_YYUNDEF;
            goto yyerrlab1;
        }

        /* If the proper action on seeing token YYLA.TYPE is to reduce or
           to detect an error, take that action.  */
        yyn += yyla.kind();
        if (yyn < 0 || yylast_ < yyn || yycheck_[yyn] != yyla.kind()) {
            goto yydefault;
        }

        // Reduce or error.
        yyn = yytable_[yyn];
        if (yyn <= 0) {
            if (yy_table_value_is_error_(yyn))
                goto yyerrlab;
            yyn = -yyn;
            goto yyreduce;
        }

        // Count tokens shifted since error; after three, turn off error status.
        if (yyerrstatus_)
            --yyerrstatus_;

        // Shift the lookahead token.
        yypush_("Shifting", state_type(yyn), YY_MOVE(yyla));
        goto yynewstate;

    /*-----------------------------------------------------------.
    | yydefault -- do the default action for the current state.  |
    `-----------------------------------------------------------*/
    yydefault:
        yyn = yydefact_[+yystack_[0].state];
        if (yyn == 0)
            goto yyerrlab;
        goto yyreduce;

    /*-----------------------------.
    | yyreduce -- do a reduction.  |
    `-----------------------------*/
    yyreduce:
        yylen = yyr2_[yyn];
        {
            stack_symbol_type yylhs;
            yylhs.state = yy_lr_goto_state_(yystack_[yylen].state, yyr1_[yyn]);
            /* Variants are always initialized to an empty instance of the
               correct type. The default '$$ = $1' action is NOT applied
               when using variants.  */
            switch (yyr1_[yyn]) {
                case symbol_kind::S_TYPE_I8:      // TYPE_I8
                case symbol_kind::S_TYPE_I16:     // TYPE_I16
                case symbol_kind::S_TYPE_I32:     // TYPE_I32
                case symbol_kind::S_TYPE_I64:     // TYPE_I64
                case symbol_kind::S_TYPE_I128:    // TYPE_I128
                case symbol_kind::S_TYPE_U8:      // TYPE_U8
                case symbol_kind::S_TYPE_U16:     // TYPE_U16
                case symbol_kind::S_TYPE_U32:     // TYPE_U32
                case symbol_kind::S_TYPE_U64:     // TYPE_U64
                case symbol_kind::S_TYPE_U128:    // TYPE_U128
                case symbol_kind::S_TYPE_BOOL:    // TYPE_BOOL
                case symbol_kind::S_TYPE_VOID:    // TYPE_VOID
                case symbol_kind::S_TYPE_STR:     // TYPE_STR
                case symbol_kind::S_builtin_type: // builtin_type
                    yylhs.value.emplace<rt_type_basic *>();
                    break;

                case symbol_kind::S_type: // type
                    yylhs.value.emplace<std::shared_ptr<type_id>>();
                    break;

                case symbol_kind::S_version_statement: // version_statement
                    yylhs.value.emplace<std::shared_ptr<version_decl>>();
                    break;

                case symbol_kind::S_V_DEC: // V_DEC
                case symbol_kind::S_V_HEX: // V_HEX
                case symbol_kind::S_V_BIN: // V_BIN
                case symbol_kind::S_V_STR: // V_STR
                case symbol_kind::S_NAME:  // NAME
                case symbol_kind::S_name:  // name
                    yylhs.value.emplace<std::string>();
                    break;

                case symbol_kind::S_global_vars: // global_vars
                    yylhs.value.emplace<std::vector<std::shared_ptr<global_var>>>();
                    break;

                default: break;
            }

            // Default location.
            {
                stack_type::slice range(yystack_, yylen);
                YYLLOC_DEFAULT(yylhs.location, range, yylen);
                yyerror_range[1].location = yylhs.location;
            }

            // Perform the reduction.
            YY_REDUCE_PRINT(yyn);
#if YY_EXCEPTIONS
            try
#endif // YY_EXCEPTIONS
            {
                switch (yyn) {
                    case 2: // program: version_statement global_vars
#line 112 "assembler/parser/srte-asm.y"
                    {
                        auto as_unit = new assembly_unit(filename);
                        for (auto gv : yystack_[0].value.as<std::vector<std::shared_ptr<global_var>>>()) {
                            as_unit->push_constant(gv);
                        }

                        as_unit->set_version(yystack_[1].value.as<std::shared_ptr<version_decl>>());
                        driver.set_result(std::shared_ptr<assembly_unit>(as_unit));
                    }
#line 944 "assembler/parser/srte-asm-parser.cpp"
                    break;

                    case 3: // version_statement: %empty
#line 124 "assembler/parser/srte-asm.y"
                    {
                        yylhs.value.as<std::shared_ptr<version_decl>>() = nullptr;
                    }
#line 950 "assembler/parser/srte-asm-parser.cpp"
                    break;

                    case 4: // version_statement: ".version" V_HEX V_HEX V_HEX end_of_stmt
#line 126 "assembler/parser/srte-asm.y"
                    {
                        yylhs.value.as<std::shared_ptr<version_decl>>() = std::make_shared<version_decl>(
                            B_LOC(yylhs.location), PB(yystack_[3].value.as<std::string>(), yystack_[3].location),
                            PB(yystack_[2].value.as<std::string>(), yystack_[2].location),
                            PB(yystack_[1].value.as<std::string>(), yystack_[1].location));
                    }
#line 958 "assembler/parser/srte-asm-parser.cpp"
                    break;

                    case 5: // global_vars: %empty
#line 132 "assembler/parser/srte-asm.y"
                    {
                        yylhs.value.as<std::vector<std::shared_ptr<global_var>>>() = {};
                    }
#line 964 "assembler/parser/srte-asm-parser.cpp"
                    break;

                    case 6: // global_vars: global_vars ".global" modifiers name COLON type end_of_stmt
#line 134 "assembler/parser/srte-asm.y"
                    {
                        auto gvar =
                            std::make_shared<global_var>(B_LOC(yylhs.location), 0, yystack_[3].value.as<std::string>(),
                                                         yystack_[1].value.as<std::shared_ptr<type_id>>(), nullptr);
                        yylhs.value.as<std::vector<std::shared_ptr<global_var>>>().push_back(gvar);
                    }
#line 973 "assembler/parser/srte-asm-parser.cpp"
                    break;

                    case 7: // global_vars: global_vars ".global" modifiers name COLON type EQUALS value end_of_stmt
#line 139 "assembler/parser/srte-asm.y"
                    {
                        yylhs.value.as<std::vector<std::shared_ptr<global_var>>>() =
                            yystack_[8].value.as<std::vector<std::shared_ptr<global_var>>>();
                    }
#line 979 "assembler/parser/srte-asm-parser.cpp"
                    break;

                    case 11: // type: builtin_type
#line 149 "assembler/parser/srte-asm.y"
                    {
                        yylhs.value.as<std::shared_ptr<type_id>>() = std::make_shared<type_id>(
                            B_LOC(yylhs.location),
                            std::shared_ptr<rt_type_base>(yystack_[0].value.as<rt_type_basic *>()));
                    }
#line 985 "assembler/parser/srte-asm-parser.cpp"
                    break;

                    case 12: // builtin_type: TYPE_I8
#line 163 "assembler/parser/srte-asm.y"
                    {
                        yylhs.value.as<rt_type_basic *>() = BASIC(rt_type_kind::I8);
                    }
#line 991 "assembler/parser/srte-asm-parser.cpp"
                    break;

                    case 13: // builtin_type: TYPE_I16
#line 164 "assembler/parser/srte-asm.y"
                    {
                        yylhs.value.as<rt_type_basic *>() = BASIC(rt_type_kind::I16);
                    }
#line 997 "assembler/parser/srte-asm-parser.cpp"
                    break;

                    case 14: // builtin_type: TYPE_I32
#line 165 "assembler/parser/srte-asm.y"
                    {
                        yylhs.value.as<rt_type_basic *>() = BASIC(rt_type_kind::I32);
                    }
#line 1003 "assembler/parser/srte-asm-parser.cpp"
                    break;

                    case 15: // builtin_type: TYPE_I64
#line 166 "assembler/parser/srte-asm.y"
                    {
                        yylhs.value.as<rt_type_basic *>() = BASIC(rt_type_kind::I64);
                    }
#line 1009 "assembler/parser/srte-asm-parser.cpp"
                    break;

                    case 16: // builtin_type: TYPE_I128
#line 167 "assembler/parser/srte-asm.y"
                    {
                        yylhs.value.as<rt_type_basic *>() = BASIC(rt_type_kind::I128);
                    }
#line 1015 "assembler/parser/srte-asm-parser.cpp"
                    break;

                    case 17: // builtin_type: TYPE_U8
#line 168 "assembler/parser/srte-asm.y"
                    {
                        yylhs.value.as<rt_type_basic *>() = BASIC(rt_type_kind::U8);
                    }
#line 1021 "assembler/parser/srte-asm-parser.cpp"
                    break;

                    case 18: // builtin_type: TYPE_U16
#line 169 "assembler/parser/srte-asm.y"
                    {
                        yylhs.value.as<rt_type_basic *>() = BASIC(rt_type_kind::U16);
                    }
#line 1027 "assembler/parser/srte-asm-parser.cpp"
                    break;

                    case 19: // builtin_type: TYPE_U32
#line 170 "assembler/parser/srte-asm.y"
                    {
                        yylhs.value.as<rt_type_basic *>() = BASIC(rt_type_kind::U32);
                    }
#line 1033 "assembler/parser/srte-asm-parser.cpp"
                    break;

                    case 20: // builtin_type: TYPE_U64
#line 171 "assembler/parser/srte-asm.y"
                    {
                        yylhs.value.as<rt_type_basic *>() = BASIC(rt_type_kind::U64);
                    }
#line 1039 "assembler/parser/srte-asm-parser.cpp"
                    break;

                    case 21: // builtin_type: TYPE_U128
#line 172 "assembler/parser/srte-asm.y"
                    {
                        yylhs.value.as<rt_type_basic *>() = BASIC(rt_type_kind::U128);
                    }
#line 1045 "assembler/parser/srte-asm-parser.cpp"
                    break;

                    case 22: // builtin_type: TYPE_BOOL
#line 173 "assembler/parser/srte-asm.y"
                    {
                        yylhs.value.as<rt_type_basic *>() = BASIC(rt_type_kind::Bool);
                    }
#line 1051 "assembler/parser/srte-asm-parser.cpp"
                    break;

                    case 23: // builtin_type: TYPE_VOID
#line 174 "assembler/parser/srte-asm.y"
                    {
                        yylhs.value.as<rt_type_basic *>() = BASIC(rt_type_kind::Void);
                    }
#line 1057 "assembler/parser/srte-asm-parser.cpp"
                    break;

                    case 24: // builtin_type: TYPE_STR
#line 175 "assembler/parser/srte-asm.y"
                    {
                        yylhs.value.as<rt_type_basic *>() = BASIC(rt_type_kind::String);
                    }
#line 1063 "assembler/parser/srte-asm-parser.cpp"
                    break;

                    case 32: // name: NAME
#line 193 "assembler/parser/srte-asm.y"
                    {
                        yylhs.value.as<std::string>() = yystack_[0].value.as<std::string>();
                    }
#line 1071 "assembler/parser/srte-asm-parser.cpp"
                    break;

                    case 33: // name: V_STR
#line 197 "assembler/parser/srte-asm.y"
                    {
                        yylhs.value.as<std::string>() = yystack_[0].value.as<std::string>();
                    }
#line 1079 "assembler/parser/srte-asm-parser.cpp"
                    break;

#line 1083 "assembler/parser/srte-asm-parser.cpp"

                    default: break;
                }
            }
#if YY_EXCEPTIONS
            catch (const syntax_error &yyexc) {
                YYCDEBUG << "Caught exception: " << yyexc.what() << '\n';
                error(yyexc);
                YYERROR;
            }
#endif // YY_EXCEPTIONS
            YY_SYMBOL_PRINT("-> $$ =", yylhs);
            yypop_(yylen);
            yylen = 0;

            // Shift the result of the reduction.
            yypush_(YY_NULLPTR, YY_MOVE(yylhs));
        }
        goto yynewstate;

    /*--------------------------------------.
    | yyerrlab -- here on detecting error.  |
    `--------------------------------------*/
    yyerrlab:
        // If not already recovering from an error, report this error.
        if (!yyerrstatus_) {
            ++yynerrs_;
            context yyctx(*this, yyla);
            std::string msg = yysyntax_error_(yyctx);
            error(yyla.location, YY_MOVE(msg));
        }

        yyerror_range[1].location = yyla.location;
        if (yyerrstatus_ == 3) {
            /* If just tried and failed to reuse lookahead token after an
               error, discard it.  */

            // Return failure if at end of input.
            if (yyla.kind() == symbol_kind::S_YYEOF)
                YYABORT;
            else if (!yyla.empty()) {
                yy_destroy_("Error: discarding", yyla);
                yyla.clear();
            }
        }

        // Else will try to reuse lookahead token after shifting the error token.
        goto yyerrlab1;

    /*---------------------------------------------------.
    | yyerrorlab -- error raised explicitly by YYERROR.  |
    `---------------------------------------------------*/
    yyerrorlab:
        /* Pacify compilers when the user code never invokes YYERROR and
           the label yyerrorlab therefore never appears in user code.  */
        if (false)
            YYERROR;

        /* Do not reclaim the symbols of the rule whose action triggered
           this YYERROR.  */
        yypop_(yylen);
        yylen = 0;
        YY_STACK_PRINT();
        goto yyerrlab1;

    /*-------------------------------------------------------------.
    | yyerrlab1 -- common code for both syntax error and YYERROR.  |
    `-------------------------------------------------------------*/
    yyerrlab1:
        yyerrstatus_ = 3; // Each real token shifted decrements this.
        // Pop stack until we find a state that shifts the error token.
        for (;;) {
            yyn = yypact_[+yystack_[0].state];
            if (!yy_pact_value_is_default_(yyn)) {
                yyn += symbol_kind::S_YYerror;
                if (0 <= yyn && yyn <= yylast_ && yycheck_[yyn] == symbol_kind::S_YYerror) {
                    yyn = yytable_[yyn];
                    if (0 < yyn)
                        break;
                }
            }

            // Pop the current state because it cannot handle the error token.
            if (yystack_.size() == 1)
                YYABORT;

            yyerror_range[1].location = yystack_[0].location;
            yy_destroy_("Error: popping", yystack_[0]);
            yypop_();
            YY_STACK_PRINT();
        }
        {
            stack_symbol_type error_token;

            yyerror_range[2].location = yyla.location;
            YYLLOC_DEFAULT(error_token.location, yyerror_range, 2);

            // Shift the error token.
            error_token.state = state_type(yyn);
            yypush_("Shifting", YY_MOVE(error_token));
        }
        goto yynewstate;

    /*-------------------------------------.
    | yyacceptlab -- YYACCEPT comes here.  |
    `-------------------------------------*/
    yyacceptlab:
        yyresult = 0;
        goto yyreturn;

    /*-----------------------------------.
    | yyabortlab -- YYABORT comes here.  |
    `-----------------------------------*/
    yyabortlab:
        yyresult = 1;
        goto yyreturn;

    /*-----------------------------------------------------.
    | yyreturn -- parsing is finished, return the result.  |
    `-----------------------------------------------------*/
    yyreturn:
        if (!yyla.empty())
            yy_destroy_("Cleanup: discarding lookahead", yyla);

        /* Do not reclaim the symbols of the rule whose action triggered
           this YYABORT or YYACCEPT.  */
        yypop_(yylen);
        YY_STACK_PRINT();
        while (1 < yystack_.size()) {
            yy_destroy_("Cleanup: popping", yystack_[0]);
            yypop_();
        }

        return yyresult;
    }
#if YY_EXCEPTIONS
    catch (...) {
        YYCDEBUG << "Exception caught: cleaning lookahead and stack\n";
        // Do not try to display the values of the reclaimed symbols,
        // as their printers might throw an exception.
        if (!yyla.empty())
            yy_destroy_(YY_NULLPTR, yyla);

        while (1 < yystack_.size()) {
            yy_destroy_(YY_NULLPTR, yystack_[0]);
            yypop_();
        }
        throw;
    }
#endif // YY_EXCEPTIONS
}

void parser::error(const syntax_error &yyexc) { error(yyexc.location, yyexc.what()); }

/* Return YYSTR after stripping away unnecessary quotes and
   backslashes, so that it's suitable for yyerror.  The heuristic is
   that double-quoting is unnecessary unless the string contains an
   apostrophe, a comma, or backslash (other than backslash-backslash).
   YYSTR is taken from yytname.  */
std::string parser::yytnamerr_(const char *yystr) {
    if (*yystr == '"') {
        std::string yyr;
        char const *yyp = yystr;

        for (;;)
            switch (*++yyp) {
                case '\'':
                case ',': goto do_not_strip_quotes;

                case '\\':
                    if (*++yyp != '\\')
                        goto do_not_strip_quotes;
                    else
                        goto append;

                append:
                default: yyr += *yyp; break;

                case '"': return yyr;
            }
    do_not_strip_quotes:;
    }

    return yystr;
}

std::string parser::symbol_name(symbol_kind_type yysymbol) { return yytnamerr_(yytname_[yysymbol]); }

// parser::context.
parser::context::context(const parser &yyparser, const symbol_type &yyla) : yyparser_(yyparser), yyla_(yyla) {}

int parser::context::expected_tokens(symbol_kind_type yyarg[], int yyargn) const {
    // Actual number of expected tokens
    int yycount = 0;

    const int yyn = yypact_[+yyparser_.yystack_[0].state];
    if (!yy_pact_value_is_default_(yyn)) {
        /* Start YYX at -YYN if negative to avoid negative indexes in
           YYCHECK.  In other words, skip the first -YYN actions for
           this state because they are default actions.  */
        const int yyxbegin = yyn < 0 ? -yyn : 0;
        // Stay within bounds of both yycheck and yytname.
        const int yychecklim = yylast_ - yyn + 1;
        const int yyxend = yychecklim < YYNTOKENS ? yychecklim : YYNTOKENS;
        for (int yyx = yyxbegin; yyx < yyxend; ++yyx)
            if (yycheck_[yyx + yyn] == yyx && yyx != symbol_kind::S_YYerror &&
                !yy_table_value_is_error_(yytable_[yyx + yyn])) {
                if (!yyarg)
                    ++yycount;
                else if (yycount == yyargn)
                    return 0;
                else
                    yyarg[yycount++] = YY_CAST(symbol_kind_type, yyx);
            }
    }

    if (yyarg && yycount == 0 && 0 < yyargn)
        yyarg[0] = symbol_kind::S_YYEMPTY;
    return yycount;
}

int parser::yy_syntax_error_arguments_(const context &yyctx, symbol_kind_type yyarg[], int yyargn) const {
    /* There are many possibilities here to consider:
       - If this state is a consistent state with a default action, then
         the only way this function was invoked is if the default action
         is an error action.  In that case, don't check for expected
         tokens because there are none.
       - The only way there can be no lookahead present (in yyla) is
         if this state is a consistent state with a default action.
         Thus, detecting the absence of a lookahead is sufficient to
         determine that there is no unexpected or expected token to
         report.  In that case, just report a simple "syntax error".
       - Don't assume there isn't a lookahead just because this state is
         a consistent state with a default action.  There might have
         been a previous inconsistent state, consistent state with a
         non-default action, or user semantic action that manipulated
         yyla.  (However, yyla is currently not documented for users.)
       - Of course, the expected token list depends on states to have
         correct lookahead information, and it depends on the parser not
         to perform extra reductions after fetching a lookahead from the
         scanner and before detecting a syntax error.  Thus, state merging
         (from LALR or IELR) and default reductions corrupt the expected
         token list.  However, the list is correct for canonical LR with
         one exception: it will still contain any token that will not be
         accepted due to an error action in a later state.
    */

    if (!yyctx.lookahead().empty()) {
        if (yyarg)
            yyarg[0] = yyctx.token();
        int yyn = yyctx.expected_tokens(yyarg ? yyarg + 1 : yyarg, yyargn - 1);
        return yyn + 1;
    }
    return 0;
}

// Generate an error message.
std::string parser::yysyntax_error_(const context &yyctx) const {
    // Its maximum.
    enum { YYARGS_MAX = 5 };
    // Arguments of yyformat.
    symbol_kind_type yyarg[YYARGS_MAX];
    int yycount = yy_syntax_error_arguments_(yyctx, yyarg, YYARGS_MAX);

    char const *yyformat = YY_NULLPTR;
    switch (yycount) {
#define YYCASE_(N, S)                                                                                                  \
    case N: yyformat = S; break
        default: // Avoid compiler warnings.
            YYCASE_(0, YY_("syntax error"));
            YYCASE_(1, YY_("syntax error, unexpected %s"));
            YYCASE_(2, YY_("syntax error, unexpected %s, expecting %s"));
            YYCASE_(3, YY_("syntax error, unexpected %s, expecting %s or %s"));
            YYCASE_(4, YY_("syntax error, unexpected %s, expecting %s or %s or %s"));
            YYCASE_(5, YY_("syntax error, unexpected %s, expecting %s or %s or %s or %s"));
#undef YYCASE_
    }

    std::string yyres;
    // Argument number.
    std::ptrdiff_t yyi = 0;
    for (char const *yyp = yyformat; *yyp; ++yyp)
        if (yyp[0] == '%' && yyp[1] == 's' && yyi < yycount) {
            yyres += symbol_name(yyarg[yyi++]);
            ++yyp;
        } else
            yyres += *yyp;
    return yyres;
}

const signed char parser::yypact_ninf_ = -18;

const signed char parser::yytable_ninf_ = -1;

const signed char parser::yypact_[] = {23,  -17, 40,  -18, 25,  -18, 43,  28,  -18, 1,   -3,  -18, -18, -18,
                                       -18, -18, -18, -18, 16,  -2,  -18, -18, -18, -18, -18, -18, -18, -18,
                                       -18, -18, -18, -18, -18, 0,   -18, 14,  -18, -18, -18, -18, -18, 2,
                                       -5,  1,   -18, -18, -18, -18, 15,  -18, -18, -18, 14,  -18};

const signed char parser::yydefact_[] = {3, 0,  0,  5,  0,  1,  2,  0,  8,  0,  0,  39, 38, 4,  10, 9,  33, 32,
                                         0, 0,  12, 13, 14, 15, 16, 17, 18, 19, 20, 21, 22, 23, 24, 0,  11, 0,
                                         6, 25, 27, 26, 28, 0,  0,  0,  30, 29, 34, 36, 0,  31, 7,  35, 0,  37};

const signed char parser::yypgoto_[] = {-18, -18, -18, -18, -18, -18, -18, -9, -18, 8, -18, -18, 5};

const signed char parser::yydefgoto_[] = {0, 2, 3, 6, 10, 33, 34, 43, 44, 18, 45, 48, 13};

const signed char parser::yytable_[] = {11, 11, 14, 15, 4,  20, 21, 22, 23, 24, 25, 26, 27, 28, 29, 30, 31,
                                        32, 16, 17, 16, 17, 37, 38, 39, 40, 1,  41, 46, 35, 12, 12, 47, 42,
                                        37, 38, 39, 40, 36, 41, 5,  51, 52, 53, 19, 42, 7,  8,  50, 9,  49};

const signed char parser::yycheck_[] = {0,  0,  5,  6,  21, 7,  8,  9,  10, 11, 12, 13, 14, 15, 16, 17, 18,
                                        19, 23, 24, 23, 24, 20, 21, 22, 23, 3,  25, 26, 29, 30, 30, 41, 31,
                                        20, 21, 22, 23, 33, 25, 0,  26, 27, 52, 28, 31, 21, 4,  43, 21, 42};

const signed char parser::yystos_[] = {0,  3,  33, 34, 21, 0,  35, 21, 4,  21, 36, 0,  30, 44, 5,  6,  23, 24,
                                       41, 28, 7,  8,  9,  10, 11, 12, 13, 14, 15, 16, 17, 18, 19, 37, 38, 29,
                                       44, 20, 21, 22, 23, 25, 31, 39, 40, 42, 26, 39, 43, 41, 44, 26, 27, 39};

const signed char parser::yyr1_[] = {0,  32, 33, 34, 34, 35, 35, 35, 36, 36, 36, 37, 38, 38, 38, 38, 38, 38, 38, 38,
                                     38, 38, 38, 38, 38, 39, 39, 39, 39, 39, 39, 40, 41, 41, 42, 42, 43, 43, 44, 44};

const signed char parser::yyr2_[] = {0, 2, 2, 0, 5, 0, 7, 9, 0, 2, 2, 1, 1, 1, 1, 1, 1, 1, 1, 1,
                                     1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 2, 1, 1, 2, 3, 1, 3, 1, 1};

#if YYDEBUG || 1
// YYTNAME[SYMBOL-NUM] -- String name of the symbol SYMBOL-NUM.
// First, the terminals, then, starting at \a YYNTOKENS, nonterminals.
const char *const parser::yytname_[] = {"\"end of file\"",
                                        "error",
                                        "\"invalid token\"",
                                        "\".version\"",
                                        "\".global\"",
                                        "\"static\"",
                                        "\"const\"",
                                        "TYPE_I8",
                                        "TYPE_I16",
                                        "TYPE_I32",
                                        "TYPE_I64",
                                        "TYPE_I128",
                                        "TYPE_U8",
                                        "TYPE_U16",
                                        "TYPE_U32",
                                        "TYPE_U64",
                                        "TYPE_U128",
                                        "TYPE_BOOL",
                                        "TYPE_VOID",
                                        "TYPE_STR",
                                        "V_DEC",
                                        "V_HEX",
                                        "V_BIN",
                                        "V_STR",
                                        "NAME",
                                        "LBRACKET",
                                        "RBRACKET",
                                        "COMMA",
                                        "COLON",
                                        "EQUALS",
                                        "NEWLINES",
                                        "AMP",
                                        "$accept",
                                        "program",
                                        "version_statement",
                                        "global_vars",
                                        "modifiers",
                                        "type",
                                        "builtin_type",
                                        "value",
                                        "address_of",
                                        "name",
                                        "array_literal",
                                        "value_list",
                                        "end_of_stmt",
                                        YY_NULLPTR};
#endif

#if YYDEBUG
const unsigned char parser::yyrline_[] = {0,   112, 112, 124, 125, 132, 133, 139, 142, 144, 145, 149, 163, 164,
                                          165, 166, 167, 168, 169, 170, 171, 172, 173, 174, 175, 179, 180, 181,
                                          182, 183, 184, 188, 192, 196, 203, 204, 208, 209, 213, 214};

void parser::yy_stack_print_() const {
    *yycdebug_ << "Stack now";
    for (stack_type::const_iterator i = yystack_.begin(), i_end = yystack_.end(); i != i_end; ++i)
        *yycdebug_ << ' ' << int(i->state);
    *yycdebug_ << '\n';
}

void parser::yy_reduce_print_(int yyrule) const {
    int yylno = yyrline_[yyrule];
    int yynrhs = yyr2_[yyrule];
    // Print the symbols being reduced, and their result.
    *yycdebug_ << "Reducing stack by rule " << yyrule - 1 << " (line " << yylno << "):\n";
    // The symbols being reduced.
    for (int yyi = 0; yyi < yynrhs; yyi++)
        YY_SYMBOL_PRINT("   $" << yyi + 1 << " =", yystack_[(yynrhs) - (yyi + 1)]);
}
#endif // YYDEBUG

parser::symbol_kind_type parser::yytranslate_(int t) YY_NOEXCEPT {
    // YYTRANSLATE[TOKEN-NUM] -- Symbol number corresponding to
    // TOKEN-NUM as returned by yylex.
    static const signed char translate_table[] = {
        0, 2, 2, 2, 2,  2,  2,  2,  2,  2,  2,  2,  2,  2,  2,  2,  2,  2,  2,  2,  2,  2,  2,  2,  2,  2, 2, 2, 2,
        2, 2, 2, 2, 2,  2,  2,  2,  2,  2,  2,  2,  2,  2,  2,  2,  2,  2,  2,  2,  2,  2,  2,  2,  2,  2, 2, 2, 2,
        2, 2, 2, 2, 2,  2,  2,  2,  2,  2,  2,  2,  2,  2,  2,  2,  2,  2,  2,  2,  2,  2,  2,  2,  2,  2, 2, 2, 2,
        2, 2, 2, 2, 2,  2,  2,  2,  2,  2,  2,  2,  2,  2,  2,  2,  2,  2,  2,  2,  2,  2,  2,  2,  2,  2, 2, 2, 2,
        2, 2, 2, 2, 2,  2,  2,  2,  2,  2,  2,  2,  2,  2,  2,  2,  2,  2,  2,  2,  2,  2,  2,  2,  2,  2, 2, 2, 2,
        2, 2, 2, 2, 2,  2,  2,  2,  2,  2,  2,  2,  2,  2,  2,  2,  2,  2,  2,  2,  2,  2,  2,  2,  2,  2, 2, 2, 2,
        2, 2, 2, 2, 2,  2,  2,  2,  2,  2,  2,  2,  2,  2,  2,  2,  2,  2,  2,  2,  2,  2,  2,  2,  2,  2, 2, 2, 2,
        2, 2, 2, 2, 2,  2,  2,  2,  2,  2,  2,  2,  2,  2,  2,  2,  2,  2,  2,  2,  2,  2,  2,  2,  2,  2, 2, 2, 2,
        2, 2, 2, 2, 2,  2,  2,  2,  2,  2,  2,  2,  2,  2,  2,  2,  2,  2,  2,  2,  2,  2,  2,  2,  1,  2, 3, 4, 5,
        6, 7, 8, 9, 10, 11, 12, 13, 14, 15, 16, 17, 18, 19, 20, 21, 22, 23, 24, 25, 26, 27, 28, 29, 30, 31};
    // Last valid token kind.
    const int code_max = 286;

    if (t <= 0)
        return symbol_kind::S_YYEOF;
    else if (t <= code_max)
        return static_cast<symbol_kind_type>(translate_table[t]);
    else
        return symbol_kind::S_YYUNDEF;
}

#line 3 "assembler/parser/srte-asm.y"
} // namespace srte_parser
#line 1635 "assembler/parser/srte-asm-parser.cpp"
