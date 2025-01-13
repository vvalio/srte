// A Bison parser, made by GNU Bison 3.8.2.

// Skeleton interface for Bison LALR(1) parsers in C++

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

/**
 ** \file assembler/parser/srte-asm-parser.hpp
 ** Define the srte_parser::parser class.
 */

// C++ LALR(1) parser skeleton written by Akim Demaille.

// DO NOT RELY ON FEATURES THAT ARE NOT DOCUMENTED in the manual,
// especially those whose name start with YY_ or yy_.  They are
// private implementation details that can be changed or removed.

#ifndef YY_YY_ASSEMBLER_PARSER_SRTE_ASM_PARSER_HPP_INCLUDED
#define YY_YY_ASSEMBLER_PARSER_SRTE_ASM_PARSER_HPP_INCLUDED
// "%code requires" blocks.
#line 10 "assembler/parser/srte-asm.y"

#include "ast.hpp"
#include "drv/drv.hpp"
#include "type.hpp"
#include <cstdint>

class token_buf;

#line 60 "assembler/parser/srte-asm-parser.hpp"

#include <cstdlib> // std::abort
#include <iostream>
#include <stdexcept>
#include <string>
#include <vector>

#if defined __cplusplus
#define YY_CPLUSPLUS __cplusplus
#else
#define YY_CPLUSPLUS 199711L
#endif

// Support move semantics when possible.
#if 201103L <= YY_CPLUSPLUS
#define YY_MOVE std::move
#define YY_MOVE_OR_COPY move
#define YY_MOVE_REF(Type) Type &&
#define YY_RVREF(Type) Type &&
#define YY_COPY(Type) Type
#else
#define YY_MOVE
#define YY_MOVE_OR_COPY copy
#define YY_MOVE_REF(Type) Type &
#define YY_RVREF(Type) const Type &
#define YY_COPY(Type) const Type &
#endif

// Support noexcept when possible.
#if 201103L <= YY_CPLUSPLUS
#define YY_NOEXCEPT noexcept
#define YY_NOTHROW
#else
#define YY_NOEXCEPT
#define YY_NOTHROW throw()
#endif

// Support constexpr when possible.
#if 201703 <= YY_CPLUSPLUS
#define YY_CONSTEXPR constexpr
#else
#define YY_CONSTEXPR
#endif
#include "location.hh"

#ifndef YY_ATTRIBUTE_PURE
#if defined __GNUC__ && 2 < __GNUC__ + (96 <= __GNUC_MINOR__)
#define YY_ATTRIBUTE_PURE __attribute__((__pure__))
#else
#define YY_ATTRIBUTE_PURE
#endif
#endif

#ifndef YY_ATTRIBUTE_UNUSED
#if defined __GNUC__ && 2 < __GNUC__ + (7 <= __GNUC_MINOR__)
#define YY_ATTRIBUTE_UNUSED __attribute__((__unused__))
#else
#define YY_ATTRIBUTE_UNUSED
#endif
#endif

/* Suppress unused-variable warnings by "using" E.  */
#if !defined lint || defined __GNUC__
#define YY_USE(E) ((void)(E))
#else
#define YY_USE(E) /* empty */
#endif

/* Suppress an incorrect diagnostic about yylval being uninitialized.  */
#if defined __GNUC__ && !defined __ICC && 406 <= __GNUC__ * 100 + __GNUC_MINOR__
#if __GNUC__ * 100 + __GNUC_MINOR__ < 407
#define YY_IGNORE_MAYBE_UNINITIALIZED_BEGIN                                                                            \
    _Pragma("GCC diagnostic push") _Pragma("GCC diagnostic ignored \"-Wuninitialized\"")
#else
#define YY_IGNORE_MAYBE_UNINITIALIZED_BEGIN                                                                            \
    _Pragma("GCC diagnostic push") _Pragma("GCC diagnostic ignored \"-Wuninitialized\"")                               \
        _Pragma("GCC diagnostic ignored \"-Wmaybe-uninitialized\"")
#endif
#define YY_IGNORE_MAYBE_UNINITIALIZED_END _Pragma("GCC diagnostic pop")
#else
#define YY_INITIAL_VALUE(Value) Value
#endif
#ifndef YY_IGNORE_MAYBE_UNINITIALIZED_BEGIN
#define YY_IGNORE_MAYBE_UNINITIALIZED_BEGIN
#define YY_IGNORE_MAYBE_UNINITIALIZED_END
#endif
#ifndef YY_INITIAL_VALUE
#define YY_INITIAL_VALUE(Value) /* Nothing. */
#endif

#if defined __cplusplus && defined __GNUC__ && !defined __ICC && 6 <= __GNUC__
#define YY_IGNORE_USELESS_CAST_BEGIN _Pragma("GCC diagnostic push") _Pragma("GCC diagnostic ignored \"-Wuseless-cast\"")
#define YY_IGNORE_USELESS_CAST_END _Pragma("GCC diagnostic pop")
#endif
#ifndef YY_IGNORE_USELESS_CAST_BEGIN
#define YY_IGNORE_USELESS_CAST_BEGIN
#define YY_IGNORE_USELESS_CAST_END
#endif

#ifndef YY_CAST
#ifdef __cplusplus
#define YY_CAST(Type, Val) static_cast<Type>(Val)
#define YY_REINTERPRET_CAST(Type, Val) reinterpret_cast<Type>(Val)
#else
#define YY_CAST(Type, Val) ((Type)(Val))
#define YY_REINTERPRET_CAST(Type, Val) ((Type)(Val))
#endif
#endif
#ifndef YY_NULLPTR
#if defined __cplusplus
#if 201103L <= __cplusplus
#define YY_NULLPTR nullptr
#else
#define YY_NULLPTR 0
#endif
#else
#define YY_NULLPTR ((void *)0)
#endif
#endif

/* Debug traces.  */
#ifndef YYDEBUG
#define YYDEBUG 0
#endif

#line 3 "assembler/parser/srte-asm.y"
namespace srte_parser {
#line 196 "assembler/parser/srte-asm-parser.hpp"

/// A Bison parser.
class parser {
  public:
#ifdef YYSTYPE
#ifdef __GNUC__
#pragma GCC message "bison: do not #define YYSTYPE in C++, use %define api.value.type"
#endif
    typedef YYSTYPE value_type;
#else
    /// A buffer to store and retrieve objects.
    ///
    /// Sort of a variant, but does not keep track of the nature
    /// of the stored data, since that knowledge is available
    /// via the current parser state.
    class value_type {
      public:
        /// Type of *this.
        typedef value_type self_type;

        /// Empty construction.
        value_type() YY_NOEXCEPT : yyraw_() {}

        /// Construct and fill.
        template <typename T> value_type(YY_RVREF(T) t) { new (yyas_<T>()) T(YY_MOVE(t)); }

#if 201103L <= YY_CPLUSPLUS
        /// Non copyable.
        value_type(const self_type &) = delete;
        /// Non copyable.
        self_type &operator=(const self_type &) = delete;
#endif

        /// Destruction, allowed only if empty.
        ~value_type() YY_NOEXCEPT {}

#if 201103L <= YY_CPLUSPLUS
        /// Instantiate a \a T in here from \a t.
        template <typename T, typename... U> T &emplace(U &&...u) { return *new (yyas_<T>()) T(std::forward<U>(u)...); }
#else
        /// Instantiate an empty \a T in here.
        template <typename T> T &emplace() { return *new (yyas_<T>()) T(); }

        /// Instantiate a \a T in here from \a t.
        template <typename T> T &emplace(const T &t) { return *new (yyas_<T>()) T(t); }
#endif

        /// Instantiate an empty \a T in here.
        /// Obsolete, use emplace.
        template <typename T> T &build() { return emplace<T>(); }

        /// Instantiate a \a T in here from \a t.
        /// Obsolete, use emplace.
        template <typename T> T &build(const T &t) { return emplace<T>(t); }

        /// Accessor to a built \a T.
        template <typename T> T &as() YY_NOEXCEPT { return *yyas_<T>(); }

        /// Const accessor to a built \a T (for %printer).
        template <typename T> const T &as() const YY_NOEXCEPT { return *yyas_<T>(); }

        /// Swap the content with \a that, of same type.
        ///
        /// Both variants must be built beforehand, because swapping the actual
        /// data requires reading it (with as()), and this is not possible on
        /// unconstructed variants: it would require some dynamic testing, which
        /// should not be the variant's responsibility.
        /// Swapping between built and (possibly) non-built is done with
        /// self_type::move ().
        template <typename T> void swap(self_type &that) YY_NOEXCEPT { std::swap(as<T>(), that.as<T>()); }

        /// Move the content of \a that to this.
        ///
        /// Destroys \a that.
        template <typename T> void move(self_type &that) {
#if 201103L <= YY_CPLUSPLUS
            emplace<T>(std::move(that.as<T>()));
#else
            emplace<T>();
            swap<T>(that);
#endif
            that.destroy<T>();
        }

#if 201103L <= YY_CPLUSPLUS
        /// Move the content of \a that to this.
        template <typename T> void move(self_type &&that) {
            emplace<T>(std::move(that.as<T>()));
            that.destroy<T>();
        }
#endif

        /// Copy the content of \a that to this.
        template <typename T> void copy(const self_type &that) { emplace<T>(that.as<T>()); }

        /// Destroy the stored \a T.
        template <typename T> void destroy() { as<T>().~T(); }

      private:
#if YY_CPLUSPLUS < 201103L
        /// Non copyable.
        value_type(const self_type &);
        /// Non copyable.
        self_type &operator=(const self_type &);
#endif

        /// Accessor to raw memory as \a T.
        template <typename T> T *yyas_() YY_NOEXCEPT {
            void *yyp = yyraw_;
            return static_cast<T *>(yyp);
        }

        /// Const accessor to raw memory as \a T.
        template <typename T> const T *yyas_() const YY_NOEXCEPT {
            const void *yyp = yyraw_;
            return static_cast<const T *>(yyp);
        }

        /// An auxiliary type to compute the largest semantic type.
        union union_type {
            // TYPE_I8
            // TYPE_I16
            // TYPE_I32
            // TYPE_I64
            // TYPE_I128
            // TYPE_U8
            // TYPE_U16
            // TYPE_U32
            // TYPE_U64
            // TYPE_U128
            // TYPE_BOOL
            // TYPE_VOID
            // TYPE_STR
            // builtin_type
            char dummy1[sizeof(rt_type_basic *)];

            // type
            char dummy2[sizeof(std::shared_ptr<type_id>)];

            // version_statement
            char dummy3[sizeof(std::shared_ptr<version_decl>)];

            // V_DEC
            // V_HEX
            // V_BIN
            // V_STR
            // NAME
            // name
            char dummy4[sizeof(std::string)];

            // global_vars
            char dummy5[sizeof(std::vector<std::shared_ptr<global_var>>)];
        };

        /// The size of the largest semantic type.
        enum { size = sizeof(union_type) };

        /// A buffer to store semantic values.
        union {
            /// Strongest alignment constraints.
            long double yyalign_me_;
            /// A buffer large enough to store any of the semantic values.
            char yyraw_[size];
        };
    };

#endif
    /// Backward compatibility (Bison 3.8).
    typedef value_type semantic_type;

    /// Symbol locations.
    typedef location location_type;

    /// Syntax errors thrown from user actions.
    struct syntax_error : std::runtime_error {
        syntax_error(const location_type &l, const std::string &m) : std::runtime_error(m), location(l) {}

        syntax_error(const syntax_error &s) : std::runtime_error(s.what()), location(s.location) {}

        ~syntax_error() YY_NOEXCEPT YY_NOTHROW;

        location_type location;
    };

    /// Token kinds.
    struct token {
        enum token_kind_type {
            YYEMPTY = -2,
            YYEOF = 0,             // "end of file"
            YYerror = 256,         // error
            YYUNDEF = 257,         // "invalid token"
            DECL_KW_VERSION = 258, // ".version"
            DECL_KW_GLOBAL = 259,  // ".global"
            KW_STATIC = 260,       // "static"
            KW_CONST = 261,        // "const"
            TYPE_I8 = 262,         // TYPE_I8
            TYPE_I16 = 263,        // TYPE_I16
            TYPE_I32 = 264,        // TYPE_I32
            TYPE_I64 = 265,        // TYPE_I64
            TYPE_I128 = 266,       // TYPE_I128
            TYPE_U8 = 267,         // TYPE_U8
            TYPE_U16 = 268,        // TYPE_U16
            TYPE_U32 = 269,        // TYPE_U32
            TYPE_U64 = 270,        // TYPE_U64
            TYPE_U128 = 271,       // TYPE_U128
            TYPE_BOOL = 272,       // TYPE_BOOL
            TYPE_VOID = 273,       // TYPE_VOID
            TYPE_STR = 274,        // TYPE_STR
            V_DEC = 275,           // V_DEC
            V_HEX = 276,           // V_HEX
            V_BIN = 277,           // V_BIN
            V_STR = 278,           // V_STR
            NAME = 279,            // NAME
            LBRACKET = 280,        // LBRACKET
            RBRACKET = 281,        // RBRACKET
            COMMA = 282,           // COMMA
            COLON = 283,           // COLON
            EQUALS = 284,          // EQUALS
            NEWLINES = 285,        // NEWLINES
            AMP = 286              // AMP
        };
        /// Backward compatibility alias (Bison 3.6).
        typedef token_kind_type yytokentype;
    };

    /// Token kind, as returned by yylex.
    typedef token::token_kind_type token_kind_type;

    /// Backward compatibility alias (Bison 3.6).
    typedef token_kind_type token_type;

    /// Symbol kinds.
    struct symbol_kind {
        enum symbol_kind_type {
            YYNTOKENS = 32, ///< Number of tokens.
            S_YYEMPTY = -2,
            S_YYEOF = 0,              // "end of file"
            S_YYerror = 1,            // error
            S_YYUNDEF = 2,            // "invalid token"
            S_DECL_KW_VERSION = 3,    // ".version"
            S_DECL_KW_GLOBAL = 4,     // ".global"
            S_KW_STATIC = 5,          // "static"
            S_KW_CONST = 6,           // "const"
            S_TYPE_I8 = 7,            // TYPE_I8
            S_TYPE_I16 = 8,           // TYPE_I16
            S_TYPE_I32 = 9,           // TYPE_I32
            S_TYPE_I64 = 10,          // TYPE_I64
            S_TYPE_I128 = 11,         // TYPE_I128
            S_TYPE_U8 = 12,           // TYPE_U8
            S_TYPE_U16 = 13,          // TYPE_U16
            S_TYPE_U32 = 14,          // TYPE_U32
            S_TYPE_U64 = 15,          // TYPE_U64
            S_TYPE_U128 = 16,         // TYPE_U128
            S_TYPE_BOOL = 17,         // TYPE_BOOL
            S_TYPE_VOID = 18,         // TYPE_VOID
            S_TYPE_STR = 19,          // TYPE_STR
            S_V_DEC = 20,             // V_DEC
            S_V_HEX = 21,             // V_HEX
            S_V_BIN = 22,             // V_BIN
            S_V_STR = 23,             // V_STR
            S_NAME = 24,              // NAME
            S_LBRACKET = 25,          // LBRACKET
            S_RBRACKET = 26,          // RBRACKET
            S_COMMA = 27,             // COMMA
            S_COLON = 28,             // COLON
            S_EQUALS = 29,            // EQUALS
            S_NEWLINES = 30,          // NEWLINES
            S_AMP = 31,               // AMP
            S_YYACCEPT = 32,          // $accept
            S_program = 33,           // program
            S_version_statement = 34, // version_statement
            S_global_vars = 35,       // global_vars
            S_modifiers = 36,         // modifiers
            S_type = 37,              // type
            S_builtin_type = 38,      // builtin_type
            S_value = 39,             // value
            S_address_of = 40,        // address_of
            S_name = 41,              // name
            S_array_literal = 42,     // array_literal
            S_value_list = 43,        // value_list
            S_end_of_stmt = 44        // end_of_stmt
        };
    };

    /// (Internal) symbol kind.
    typedef symbol_kind::symbol_kind_type symbol_kind_type;

    /// The number of tokens.
    static const symbol_kind_type YYNTOKENS = symbol_kind::YYNTOKENS;

    /// A complete symbol.
    ///
    /// Expects its Base type to provide access to the symbol kind
    /// via kind ().
    ///
    /// Provide access to semantic value and location.
    template <typename Base> struct basic_symbol : Base {
        /// Alias to Base.
        typedef Base super_type;

        /// Default constructor.
        basic_symbol() YY_NOEXCEPT : value(), location() {}

#if 201103L <= YY_CPLUSPLUS
        /// Move constructor.
        basic_symbol(basic_symbol &&that) : Base(std::move(that)), value(), location(std::move(that.location)) {
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
                    value.move<rt_type_basic *>(std::move(that.value));
                    break;

                case symbol_kind::S_type: // type
                    value.move<std::shared_ptr<type_id>>(std::move(that.value));
                    break;

                case symbol_kind::S_version_statement: // version_statement
                    value.move<std::shared_ptr<version_decl>>(std::move(that.value));
                    break;

                case symbol_kind::S_V_DEC: // V_DEC
                case symbol_kind::S_V_HEX: // V_HEX
                case symbol_kind::S_V_BIN: // V_BIN
                case symbol_kind::S_V_STR: // V_STR
                case symbol_kind::S_NAME:  // NAME
                case symbol_kind::S_name:  // name
                    value.move<std::string>(std::move(that.value));
                    break;

                case symbol_kind::S_global_vars: // global_vars
                    value.move<std::vector<std::shared_ptr<global_var>>>(std::move(that.value));
                    break;

                default: break;
            }
        }
#endif

        /// Copy constructor.
        basic_symbol(const basic_symbol &that);

        /// Constructors for typed symbols.
#if 201103L <= YY_CPLUSPLUS
        basic_symbol(typename Base::kind_type t, location_type &&l) : Base(t), location(std::move(l)) {}
#else
        basic_symbol(typename Base::kind_type t, const location_type &l) : Base(t), location(l) {}
#endif

#if 201103L <= YY_CPLUSPLUS
        basic_symbol(typename Base::kind_type t, rt_type_basic *&&v, location_type &&l)
            : Base(t), value(std::move(v)), location(std::move(l)) {}
#else
        basic_symbol(typename Base::kind_type t, const rt_type_basic *&v, const location_type &l)
            : Base(t), value(v), location(l) {}
#endif

#if 201103L <= YY_CPLUSPLUS
        basic_symbol(typename Base::kind_type t, std::shared_ptr<type_id> &&v, location_type &&l)
            : Base(t), value(std::move(v)), location(std::move(l)) {}
#else
        basic_symbol(typename Base::kind_type t, const std::shared_ptr<type_id> &v, const location_type &l)
            : Base(t), value(v), location(l) {}
#endif

#if 201103L <= YY_CPLUSPLUS
        basic_symbol(typename Base::kind_type t, std::shared_ptr<version_decl> &&v, location_type &&l)
            : Base(t), value(std::move(v)), location(std::move(l)) {}
#else
        basic_symbol(typename Base::kind_type t, const std::shared_ptr<version_decl> &v, const location_type &l)
            : Base(t), value(v), location(l) {}
#endif

#if 201103L <= YY_CPLUSPLUS
        basic_symbol(typename Base::kind_type t, std::string &&v, location_type &&l)
            : Base(t), value(std::move(v)), location(std::move(l)) {}
#else
        basic_symbol(typename Base::kind_type t, const std::string &v, const location_type &l)
            : Base(t), value(v), location(l) {}
#endif

#if 201103L <= YY_CPLUSPLUS
        basic_symbol(typename Base::kind_type t, std::vector<std::shared_ptr<global_var>> &&v, location_type &&l)
            : Base(t), value(std::move(v)), location(std::move(l)) {}
#else
        basic_symbol(typename Base::kind_type t, const std::vector<std::shared_ptr<global_var>> &v,
                     const location_type &l)
            : Base(t), value(v), location(l) {}
#endif

        /// Destroy the symbol.
        ~basic_symbol() { clear(); }

        /// Destroy contents, and record that is empty.
        void clear() YY_NOEXCEPT {
            // User destructor.
            symbol_kind_type yykind = this->kind();
            basic_symbol<Base> &yysym = *this;
            (void)yysym;
            switch (yykind) {
                default: break;
            }

            // Value type destructor.
            switch (yykind) {
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
                    value.template destroy<rt_type_basic *>();
                    break;

                case symbol_kind::S_type: // type
                    value.template destroy<std::shared_ptr<type_id>>();
                    break;

                case symbol_kind::S_version_statement: // version_statement
                    value.template destroy<std::shared_ptr<version_decl>>();
                    break;

                case symbol_kind::S_V_DEC: // V_DEC
                case symbol_kind::S_V_HEX: // V_HEX
                case symbol_kind::S_V_BIN: // V_BIN
                case symbol_kind::S_V_STR: // V_STR
                case symbol_kind::S_NAME:  // NAME
                case symbol_kind::S_name:  // name
                    value.template destroy<std::string>();
                    break;

                case symbol_kind::S_global_vars: // global_vars
                    value.template destroy<std::vector<std::shared_ptr<global_var>>>();
                    break;

                default: break;
            }

            Base::clear();
        }

        /// The user-facing name of this symbol.
        std::string name() const YY_NOEXCEPT { return parser::symbol_name(this->kind()); }

        /// Backward compatibility (Bison 3.6).
        symbol_kind_type type_get() const YY_NOEXCEPT;

        /// Whether empty.
        bool empty() const YY_NOEXCEPT;

        /// Destructive move, \a s is emptied into this.
        void move(basic_symbol &s);

        /// The semantic value.
        value_type value;

        /// The location.
        location_type location;

      private:
#if YY_CPLUSPLUS < 201103L
        /// Assignment operator.
        basic_symbol &operator=(const basic_symbol &that);
#endif
    };

    /// Type access provider for token (enum) based symbols.
    struct by_kind {
        /// The symbol kind as needed by the constructor.
        typedef token_kind_type kind_type;

        /// Default constructor.
        by_kind() YY_NOEXCEPT;

#if 201103L <= YY_CPLUSPLUS
        /// Move constructor.
        by_kind(by_kind &&that) YY_NOEXCEPT;
#endif

        /// Copy constructor.
        by_kind(const by_kind &that) YY_NOEXCEPT;

        /// Constructor from (external) token numbers.
        by_kind(kind_type t) YY_NOEXCEPT;

        /// Record that this symbol is empty.
        void clear() YY_NOEXCEPT;

        /// Steal the symbol kind from \a that.
        void move(by_kind &that);

        /// The (internal) type number (corresponding to \a type).
        /// \a empty when empty.
        symbol_kind_type kind() const YY_NOEXCEPT;

        /// Backward compatibility (Bison 3.6).
        symbol_kind_type type_get() const YY_NOEXCEPT;

        /// The symbol kind.
        /// \a S_YYEMPTY when empty.
        symbol_kind_type kind_;
    };

    /// Backward compatibility for a private implementation detail (Bison 3.6).
    typedef by_kind by_type;

    /// "External" symbols: returned by the scanner.
    struct symbol_type : basic_symbol<by_kind> {
        /// Superclass.
        typedef basic_symbol<by_kind> super_type;

        /// Empty symbol.
        symbol_type() YY_NOEXCEPT {}

        /// Constructor for valueless symbols, and symbols from each type.
#if 201103L <= YY_CPLUSPLUS
        symbol_type(int tok, location_type l)
            : super_type(token_kind_type(tok), std::move(l))
#else
        symbol_type(int tok, const location_type &l)
            : super_type(token_kind_type(tok), l)
#endif
        {
        }
#if 201103L <= YY_CPLUSPLUS
        symbol_type(int tok, rt_type_basic *v, location_type l)
            : super_type(token_kind_type(tok), std::move(v), std::move(l))
#else
        symbol_type(int tok, const rt_type_basic *&v, const location_type &l)
            : super_type(token_kind_type(tok), v, l)
#endif
        {
        }
#if 201103L <= YY_CPLUSPLUS
        symbol_type(int tok, std::string v, location_type l)
            : super_type(token_kind_type(tok), std::move(v), std::move(l))
#else
        symbol_type(int tok, const std::string &v, const location_type &l)
            : super_type(token_kind_type(tok), v, l)
#endif
        {
        }
    };

    /// Build a parser object.
    parser(token_buf &tbuf_yyarg, parser_drv &driver_yyarg, const std::string &filename_yyarg);
    virtual ~parser();

#if 201103L <= YY_CPLUSPLUS
    /// Non copyable.
    parser(const parser &) = delete;
    /// Non copyable.
    parser &operator=(const parser &) = delete;
#endif

    /// Parse.  An alias for parse ().
    /// \returns  0 iff parsing succeeded.
    int operator()();

    /// Parse.
    /// \returns  0 iff parsing succeeded.
    virtual int parse();

#if YYDEBUG
    /// The current debugging stream.
    std::ostream &debug_stream() const YY_ATTRIBUTE_PURE;
    /// Set the current debugging stream.
    void set_debug_stream(std::ostream &);

    /// Type for debugging levels.
    typedef int debug_level_type;
    /// The current debugging level.
    debug_level_type debug_level() const YY_ATTRIBUTE_PURE;
    /// Set the current debugging level.
    void set_debug_level(debug_level_type l);
#endif

    /// Report a syntax error.
    /// \param loc    where the syntax error is found.
    /// \param msg    a description of the syntax error.
    virtual void error(const location_type &loc, const std::string &msg);

    /// Report a syntax error.
    void error(const syntax_error &err);

    /// The user-facing name of the symbol whose (internal) number is
    /// YYSYMBOL.  No bounds checking.
    static std::string symbol_name(symbol_kind_type yysymbol);

    // Implementation of make_symbol for each token kind.
#if 201103L <= YY_CPLUSPLUS
    static symbol_type make_YYEOF(location_type l) { return symbol_type(token::YYEOF, std::move(l)); }
#else
    static symbol_type make_YYEOF(const location_type &l) { return symbol_type(token::YYEOF, l); }
#endif
#if 201103L <= YY_CPLUSPLUS
    static symbol_type make_YYerror(location_type l) { return symbol_type(token::YYerror, std::move(l)); }
#else
    static symbol_type make_YYerror(const location_type &l) { return symbol_type(token::YYerror, l); }
#endif
#if 201103L <= YY_CPLUSPLUS
    static symbol_type make_YYUNDEF(location_type l) { return symbol_type(token::YYUNDEF, std::move(l)); }
#else
    static symbol_type make_YYUNDEF(const location_type &l) { return symbol_type(token::YYUNDEF, l); }
#endif
#if 201103L <= YY_CPLUSPLUS
    static symbol_type make_DECL_KW_VERSION(location_type l) {
        return symbol_type(token::DECL_KW_VERSION, std::move(l));
    }
#else
    static symbol_type make_DECL_KW_VERSION(const location_type &l) { return symbol_type(token::DECL_KW_VERSION, l); }
#endif
#if 201103L <= YY_CPLUSPLUS
    static symbol_type make_DECL_KW_GLOBAL(location_type l) { return symbol_type(token::DECL_KW_GLOBAL, std::move(l)); }
#else
    static symbol_type make_DECL_KW_GLOBAL(const location_type &l) { return symbol_type(token::DECL_KW_GLOBAL, l); }
#endif
#if 201103L <= YY_CPLUSPLUS
    static symbol_type make_KW_STATIC(location_type l) { return symbol_type(token::KW_STATIC, std::move(l)); }
#else
    static symbol_type make_KW_STATIC(const location_type &l) { return symbol_type(token::KW_STATIC, l); }
#endif
#if 201103L <= YY_CPLUSPLUS
    static symbol_type make_KW_CONST(location_type l) { return symbol_type(token::KW_CONST, std::move(l)); }
#else
    static symbol_type make_KW_CONST(const location_type &l) { return symbol_type(token::KW_CONST, l); }
#endif
#if 201103L <= YY_CPLUSPLUS
    static symbol_type make_TYPE_I8(rt_type_basic *v, location_type l) {
        return symbol_type(token::TYPE_I8, std::move(v), std::move(l));
    }
#else
    static symbol_type make_TYPE_I8(const rt_type_basic *&v, const location_type &l) {
        return symbol_type(token::TYPE_I8, v, l);
    }
#endif
#if 201103L <= YY_CPLUSPLUS
    static symbol_type make_TYPE_I16(rt_type_basic *v, location_type l) {
        return symbol_type(token::TYPE_I16, std::move(v), std::move(l));
    }
#else
    static symbol_type make_TYPE_I16(const rt_type_basic *&v, const location_type &l) {
        return symbol_type(token::TYPE_I16, v, l);
    }
#endif
#if 201103L <= YY_CPLUSPLUS
    static symbol_type make_TYPE_I32(rt_type_basic *v, location_type l) {
        return symbol_type(token::TYPE_I32, std::move(v), std::move(l));
    }
#else
    static symbol_type make_TYPE_I32(const rt_type_basic *&v, const location_type &l) {
        return symbol_type(token::TYPE_I32, v, l);
    }
#endif
#if 201103L <= YY_CPLUSPLUS
    static symbol_type make_TYPE_I64(rt_type_basic *v, location_type l) {
        return symbol_type(token::TYPE_I64, std::move(v), std::move(l));
    }
#else
    static symbol_type make_TYPE_I64(const rt_type_basic *&v, const location_type &l) {
        return symbol_type(token::TYPE_I64, v, l);
    }
#endif
#if 201103L <= YY_CPLUSPLUS
    static symbol_type make_TYPE_I128(rt_type_basic *v, location_type l) {
        return symbol_type(token::TYPE_I128, std::move(v), std::move(l));
    }
#else
    static symbol_type make_TYPE_I128(const rt_type_basic *&v, const location_type &l) {
        return symbol_type(token::TYPE_I128, v, l);
    }
#endif
#if 201103L <= YY_CPLUSPLUS
    static symbol_type make_TYPE_U8(rt_type_basic *v, location_type l) {
        return symbol_type(token::TYPE_U8, std::move(v), std::move(l));
    }
#else
    static symbol_type make_TYPE_U8(const rt_type_basic *&v, const location_type &l) {
        return symbol_type(token::TYPE_U8, v, l);
    }
#endif
#if 201103L <= YY_CPLUSPLUS
    static symbol_type make_TYPE_U16(rt_type_basic *v, location_type l) {
        return symbol_type(token::TYPE_U16, std::move(v), std::move(l));
    }
#else
    static symbol_type make_TYPE_U16(const rt_type_basic *&v, const location_type &l) {
        return symbol_type(token::TYPE_U16, v, l);
    }
#endif
#if 201103L <= YY_CPLUSPLUS
    static symbol_type make_TYPE_U32(rt_type_basic *v, location_type l) {
        return symbol_type(token::TYPE_U32, std::move(v), std::move(l));
    }
#else
    static symbol_type make_TYPE_U32(const rt_type_basic *&v, const location_type &l) {
        return symbol_type(token::TYPE_U32, v, l);
    }
#endif
#if 201103L <= YY_CPLUSPLUS
    static symbol_type make_TYPE_U64(rt_type_basic *v, location_type l) {
        return symbol_type(token::TYPE_U64, std::move(v), std::move(l));
    }
#else
    static symbol_type make_TYPE_U64(const rt_type_basic *&v, const location_type &l) {
        return symbol_type(token::TYPE_U64, v, l);
    }
#endif
#if 201103L <= YY_CPLUSPLUS
    static symbol_type make_TYPE_U128(rt_type_basic *v, location_type l) {
        return symbol_type(token::TYPE_U128, std::move(v), std::move(l));
    }
#else
    static symbol_type make_TYPE_U128(const rt_type_basic *&v, const location_type &l) {
        return symbol_type(token::TYPE_U128, v, l);
    }
#endif
#if 201103L <= YY_CPLUSPLUS
    static symbol_type make_TYPE_BOOL(rt_type_basic *v, location_type l) {
        return symbol_type(token::TYPE_BOOL, std::move(v), std::move(l));
    }
#else
    static symbol_type make_TYPE_BOOL(const rt_type_basic *&v, const location_type &l) {
        return symbol_type(token::TYPE_BOOL, v, l);
    }
#endif
#if 201103L <= YY_CPLUSPLUS
    static symbol_type make_TYPE_VOID(rt_type_basic *v, location_type l) {
        return symbol_type(token::TYPE_VOID, std::move(v), std::move(l));
    }
#else
    static symbol_type make_TYPE_VOID(const rt_type_basic *&v, const location_type &l) {
        return symbol_type(token::TYPE_VOID, v, l);
    }
#endif
#if 201103L <= YY_CPLUSPLUS
    static symbol_type make_TYPE_STR(rt_type_basic *v, location_type l) {
        return symbol_type(token::TYPE_STR, std::move(v), std::move(l));
    }
#else
    static symbol_type make_TYPE_STR(const rt_type_basic *&v, const location_type &l) {
        return symbol_type(token::TYPE_STR, v, l);
    }
#endif
#if 201103L <= YY_CPLUSPLUS
    static symbol_type make_V_DEC(std::string v, location_type l) {
        return symbol_type(token::V_DEC, std::move(v), std::move(l));
    }
#else
    static symbol_type make_V_DEC(const std::string &v, const location_type &l) {
        return symbol_type(token::V_DEC, v, l);
    }
#endif
#if 201103L <= YY_CPLUSPLUS
    static symbol_type make_V_HEX(std::string v, location_type l) {
        return symbol_type(token::V_HEX, std::move(v), std::move(l));
    }
#else
    static symbol_type make_V_HEX(const std::string &v, const location_type &l) {
        return symbol_type(token::V_HEX, v, l);
    }
#endif
#if 201103L <= YY_CPLUSPLUS
    static symbol_type make_V_BIN(std::string v, location_type l) {
        return symbol_type(token::V_BIN, std::move(v), std::move(l));
    }
#else
    static symbol_type make_V_BIN(const std::string &v, const location_type &l) {
        return symbol_type(token::V_BIN, v, l);
    }
#endif
#if 201103L <= YY_CPLUSPLUS
    static symbol_type make_V_STR(std::string v, location_type l) {
        return symbol_type(token::V_STR, std::move(v), std::move(l));
    }
#else
    static symbol_type make_V_STR(const std::string &v, const location_type &l) {
        return symbol_type(token::V_STR, v, l);
    }
#endif
#if 201103L <= YY_CPLUSPLUS
    static symbol_type make_NAME(std::string v, location_type l) {
        return symbol_type(token::NAME, std::move(v), std::move(l));
    }
#else
    static symbol_type make_NAME(const std::string &v, const location_type &l) {
        return symbol_type(token::NAME, v, l);
    }
#endif
#if 201103L <= YY_CPLUSPLUS
    static symbol_type make_LBRACKET(location_type l) { return symbol_type(token::LBRACKET, std::move(l)); }
#else
    static symbol_type make_LBRACKET(const location_type &l) { return symbol_type(token::LBRACKET, l); }
#endif
#if 201103L <= YY_CPLUSPLUS
    static symbol_type make_RBRACKET(location_type l) { return symbol_type(token::RBRACKET, std::move(l)); }
#else
    static symbol_type make_RBRACKET(const location_type &l) { return symbol_type(token::RBRACKET, l); }
#endif
#if 201103L <= YY_CPLUSPLUS
    static symbol_type make_COMMA(location_type l) { return symbol_type(token::COMMA, std::move(l)); }
#else
    static symbol_type make_COMMA(const location_type &l) { return symbol_type(token::COMMA, l); }
#endif
#if 201103L <= YY_CPLUSPLUS
    static symbol_type make_COLON(location_type l) { return symbol_type(token::COLON, std::move(l)); }
#else
    static symbol_type make_COLON(const location_type &l) { return symbol_type(token::COLON, l); }
#endif
#if 201103L <= YY_CPLUSPLUS
    static symbol_type make_EQUALS(location_type l) { return symbol_type(token::EQUALS, std::move(l)); }
#else
    static symbol_type make_EQUALS(const location_type &l) { return symbol_type(token::EQUALS, l); }
#endif
#if 201103L <= YY_CPLUSPLUS
    static symbol_type make_NEWLINES(location_type l) { return symbol_type(token::NEWLINES, std::move(l)); }
#else
    static symbol_type make_NEWLINES(const location_type &l) { return symbol_type(token::NEWLINES, l); }
#endif
#if 201103L <= YY_CPLUSPLUS
    static symbol_type make_AMP(location_type l) { return symbol_type(token::AMP, std::move(l)); }
#else
    static symbol_type make_AMP(const location_type &l) { return symbol_type(token::AMP, l); }
#endif

    class context {
      public:
        context(const parser &yyparser, const symbol_type &yyla);
        const symbol_type &lookahead() const YY_NOEXCEPT { return yyla_; }
        symbol_kind_type token() const YY_NOEXCEPT { return yyla_.kind(); }
        const location_type &location() const YY_NOEXCEPT { return yyla_.location; }

        /// Put in YYARG at most YYARGN of the expected tokens, and return the
        /// number of tokens stored in YYARG.  If YYARG is null, return the
        /// number of expected tokens (guaranteed to be less than YYNTOKENS).
        int expected_tokens(symbol_kind_type yyarg[], int yyargn) const;

      private:
        const parser &yyparser_;
        const symbol_type &yyla_;
    };

  private:
#if YY_CPLUSPLUS < 201103L
    /// Non copyable.
    parser(const parser &);
    /// Non copyable.
    parser &operator=(const parser &);
#endif

    /// Stored state numbers (used for stacks).
    typedef signed char state_type;

    /// The arguments of the error message.
    int yy_syntax_error_arguments_(const context &yyctx, symbol_kind_type yyarg[], int yyargn) const;

    /// Generate an error message.
    /// \param yyctx     the context in which the error occurred.
    virtual std::string yysyntax_error_(const context &yyctx) const;
    /// Compute post-reduction state.
    /// \param yystate   the current state
    /// \param yysym     the nonterminal to push on the stack
    static state_type yy_lr_goto_state_(state_type yystate, int yysym);

    /// Whether the given \c yypact_ value indicates a defaulted state.
    /// \param yyvalue   the value to check
    static bool yy_pact_value_is_default_(int yyvalue) YY_NOEXCEPT;

    /// Whether the given \c yytable_ value indicates a syntax error.
    /// \param yyvalue   the value to check
    static bool yy_table_value_is_error_(int yyvalue) YY_NOEXCEPT;

    static const signed char yypact_ninf_;
    static const signed char yytable_ninf_;

    /// Convert a scanner token kind \a t to a symbol kind.
    /// In theory \a t should be a token_kind_type, but character literals
    /// are valid, yet not members of the token_kind_type enum.
    static symbol_kind_type yytranslate_(int t) YY_NOEXCEPT;

    /// Convert the symbol name \a n to a form suitable for a diagnostic.
    static std::string yytnamerr_(const char *yystr);

    /// For a symbol, its name in clear.
    static const char *const yytname_[];

    // Tables.
    // YYPACT[STATE-NUM] -- Index in YYTABLE of the portion describing
    // STATE-NUM.
    static const signed char yypact_[];

    // YYDEFACT[STATE-NUM] -- Default reduction number in state STATE-NUM.
    // Performed when YYTABLE does not specify something else to do.  Zero
    // means the default is an error.
    static const signed char yydefact_[];

    // YYPGOTO[NTERM-NUM].
    static const signed char yypgoto_[];

    // YYDEFGOTO[NTERM-NUM].
    static const signed char yydefgoto_[];

    // YYTABLE[YYPACT[STATE-NUM]] -- What to do in state STATE-NUM.  If
    // positive, shift that token.  If negative, reduce the rule whose
    // number is the opposite.  If YYTABLE_NINF, syntax error.
    static const signed char yytable_[];

    static const signed char yycheck_[];

    // YYSTOS[STATE-NUM] -- The symbol kind of the accessing symbol of
    // state STATE-NUM.
    static const signed char yystos_[];

    // YYR1[RULE-NUM] -- Symbol kind of the left-hand side of rule RULE-NUM.
    static const signed char yyr1_[];

    // YYR2[RULE-NUM] -- Number of symbols on the right-hand side of rule RULE-NUM.
    static const signed char yyr2_[];

#if YYDEBUG
    // YYRLINE[YYN] -- Source line where rule number YYN was defined.
    static const unsigned char yyrline_[];
    /// Report on the debug stream that the rule \a r is going to be reduced.
    virtual void yy_reduce_print_(int r) const;
    /// Print the state stack on the debug stream.
    virtual void yy_stack_print_() const;

    /// Debugging level.
    int yydebug_;
    /// Debug stream.
    std::ostream *yycdebug_;

    /// \brief Display a symbol kind, value and location.
    /// \param yyo    The output stream.
    /// \param yysym  The symbol.
    template <typename Base> void yy_print_(std::ostream &yyo, const basic_symbol<Base> &yysym) const;
#endif

    /// \brief Reclaim the memory associated to a symbol.
    /// \param yymsg     Why this token is reclaimed.
    ///                  If null, print nothing.
    /// \param yysym     The symbol.
    template <typename Base> void yy_destroy_(const char *yymsg, basic_symbol<Base> &yysym) const;

  private:
    /// Type access provider for state based symbols.
    struct by_state {
        /// Default constructor.
        by_state() YY_NOEXCEPT;

        /// The symbol kind as needed by the constructor.
        typedef state_type kind_type;

        /// Constructor.
        by_state(kind_type s) YY_NOEXCEPT;

        /// Copy constructor.
        by_state(const by_state &that) YY_NOEXCEPT;

        /// Record that this symbol is empty.
        void clear() YY_NOEXCEPT;

        /// Steal the symbol kind from \a that.
        void move(by_state &that);

        /// The symbol kind (corresponding to \a state).
        /// \a symbol_kind::S_YYEMPTY when empty.
        symbol_kind_type kind() const YY_NOEXCEPT;

        /// The state number used to denote an empty symbol.
        /// We use the initial state, as it does not have a value.
        enum { empty_state = 0 };

        /// The state.
        /// \a empty when empty.
        state_type state;
    };

    /// "Internal" symbol: element of the stack.
    struct stack_symbol_type : basic_symbol<by_state> {
        /// Superclass.
        typedef basic_symbol<by_state> super_type;
        /// Construct an empty symbol.
        stack_symbol_type();
        /// Move or copy construction.
        stack_symbol_type(YY_RVREF(stack_symbol_type) that);
        /// Steal the contents from \a sym to build this.
        stack_symbol_type(state_type s, YY_MOVE_REF(symbol_type) sym);
#if YY_CPLUSPLUS < 201103L
        /// Assignment, needed by push_back by some old implementations.
        /// Moves the contents of that.
        stack_symbol_type &operator=(stack_symbol_type &that);

        /// Assignment, needed by push_back by other implementations.
        /// Needed by some other old implementations.
        stack_symbol_type &operator=(const stack_symbol_type &that);
#endif
    };

    /// A stack with random access from its top.
    template <typename T, typename S = std::vector<T>> class stack {
      public:
        // Hide our reversed order.
        typedef typename S::iterator iterator;
        typedef typename S::const_iterator const_iterator;
        typedef typename S::size_type size_type;
        typedef typename std::ptrdiff_t index_type;

        stack(size_type n = 200) YY_NOEXCEPT : seq_(n) {}

#if 201103L <= YY_CPLUSPLUS
        /// Non copyable.
        stack(const stack &) = delete;
        /// Non copyable.
        stack &operator=(const stack &) = delete;
#endif

        /// Random access.
        ///
        /// Index 0 returns the topmost element.
        const T &operator[](index_type i) const { return seq_[size_type(size() - 1 - i)]; }

        /// Random access.
        ///
        /// Index 0 returns the topmost element.
        T &operator[](index_type i) { return seq_[size_type(size() - 1 - i)]; }

        /// Steal the contents of \a t.
        ///
        /// Close to move-semantics.
        void push(YY_MOVE_REF(T) t) {
            seq_.push_back(T());
            operator[](0).move(t);
        }

        /// Pop elements from the stack.
        void pop(std::ptrdiff_t n = 1) YY_NOEXCEPT {
            for (; 0 < n; --n)
                seq_.pop_back();
        }

        /// Pop all elements from the stack.
        void clear() YY_NOEXCEPT { seq_.clear(); }

        /// Number of elements on the stack.
        index_type size() const YY_NOEXCEPT { return index_type(seq_.size()); }

        /// Iterator on top of the stack (going downwards).
        const_iterator begin() const YY_NOEXCEPT { return seq_.begin(); }

        /// Bottom of the stack.
        const_iterator end() const YY_NOEXCEPT { return seq_.end(); }

        /// Present a slice of the top of a stack.
        class slice {
          public:
            slice(const stack &stack, index_type range) YY_NOEXCEPT : stack_(stack), range_(range) {}

            const T &operator[](index_type i) const { return stack_[range_ - i]; }

          private:
            const stack &stack_;
            index_type range_;
        };

      private:
#if YY_CPLUSPLUS < 201103L
        /// Non copyable.
        stack(const stack &);
        /// Non copyable.
        stack &operator=(const stack &);
#endif
        /// The wrapped container.
        S seq_;
    };

    /// Stack type.
    typedef stack<stack_symbol_type> stack_type;

    /// The stack.
    stack_type yystack_;

    /// Push a new state on the stack.
    /// \param m    a debug message to display
    ///             if null, no trace is output.
    /// \param sym  the symbol
    /// \warning the contents of \a s.value is stolen.
    void yypush_(const char *m, YY_MOVE_REF(stack_symbol_type) sym);

    /// Push a new look ahead token on the state on the stack.
    /// \param m    a debug message to display
    ///             if null, no trace is output.
    /// \param s    the state
    /// \param sym  the symbol (for its value and location).
    /// \warning the contents of \a sym.value is stolen.
    void yypush_(const char *m, state_type s, YY_MOVE_REF(symbol_type) sym);

    /// Pop \a n symbols from the stack.
    void yypop_(int n = 1) YY_NOEXCEPT;

    /// Constants.
    enum {
        yylast_ = 50, ///< Last index in yytable_.
        yynnts_ = 13, ///< Number of nonterminal symbols.
        yyfinal_ = 5  ///< Termination state number.
    };

    // User arguments.
    token_buf &tbuf;
    parser_drv &driver;
    const std::string &filename;
};

#line 3 "assembler/parser/srte-asm.y"
} // namespace srte_parser
#line 1780 "assembler/parser/srte-asm-parser.hpp"

// "%code provides" blocks.
#line 21 "assembler/parser/srte-asm.y"

srte_parser::parser::token_type yylex(srte_parser::parser::value_type *value,
                                      srte_parser::parser::location_type *location, token_buf &tbuf);

#line 1790 "assembler/parser/srte-asm-parser.hpp"

#endif // !YY_YY_ASSEMBLER_PARSER_SRTE_ASM_PARSER_HPP_INCLUDED
