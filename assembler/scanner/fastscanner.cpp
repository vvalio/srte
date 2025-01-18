#include "fastscanner.hpp"
#include "parser/srte-asm-parser.hpp"
#include <cctype>
#include <cstdlib>
#include <cstring>
#include <sstream>
#include <string>
#include <unordered_map>
#include <vector>

// Do not use with c having side effects
#define isidletter(c) (std::isalpha(c) || c == '_')
#define isidcontinue(c) (std::isalnum(c) || c == '_')

std::string fast_scanner::error::to_string() {
    std::stringstream sr;
    switch (level) {
        case error_level::Error: sr << "Error: "; break;
        case error_level::Warning: sr << "Warning"; break;
        case error_level::Fatal: sr << "FATAL: "; break;
    }

    sr << err_loc.begin.line << ":" << err_loc.begin.column << ": " << err_msg;
    return sr.str();
}

// Combines tok_type and location + value_type into one
struct token {
  public:
    tok_type type;
    loc_type loc;
    val_type val;

    static token *create(tok_type t, loc_type l, const char *lexeme) { return new token(t, l, lexeme); }

    ~token() {
        // delete loc.begin.filename; // allocated with new in push_token since bison for some reason wants pointers
    }

  private:
    token(tok_type t, loc_type l, std::string lexeme) : type(t), loc(l) { val.as<std::string>() = lexeme; }
};

token_buf::token_buf() { tokens = std::vector<token *>(); }

token_buf::~token_buf() {
    for (auto t : tokens) {
        t->val.destroy<std::string>();
        delete t;
    }
}

void token_buf::add(token *t) { tokens.push_back(t); }

std::string token_buf::to_string() const {
    std::stringstream sr;
    sr << "[";

    for (size_t i = 0; i < tokens.size(); i++) {
        sr << srte_parser::parser::symbol_name(srte_parser::parser::by_kind(tokens[i]->type).type_get()) << ":"
           << tokens[i]->val.as<std::string>() << ", ";
    }

    auto result = sr.str();
    return result.substr(0, result.length() - 2) + "]";
}

tok_type yylex(srte_parser::parser::value_type *value, srte_parser::parser::location_type *location, token_buf &tbuf) {
    if (tbuf.index >= (int)tbuf.tokens.size()) {
        if (!tbuf.tokens.empty()) {
            *location = tbuf.tokens.back()->loc;
        }

        return tok_type::YYEOF;
    }

    value->as<std::string>() = tbuf.tokens[tbuf.index]->val.as<std::string>();
    *location = tbuf.tokens[tbuf.index]->loc;
    return tbuf.tokens[tbuf.index++]->type;
}

// Scanner code
fast_scanner::fast_scanner(const std::string &src, const std::string &fname) {
    this->_source = src;
    this->_filename = fname;
    this->_line = 1;
    this->_column = 1;
    this->_index = 0;
    this->_buf = new token_buf();
}

fast_scanner::~fast_scanner() { /* token_buf used in the parser */ }

void fast_scanner::push_token(tok_type t, std::string lit) {
    _buf->add(token::create(t, loc_type(nullptr, _line, _column), lit.c_str()));
}

void fast_scanner::add_error(loc_type l, const std::string &msg) {
    _errors.push_back(error(l, msg, error_level::Error));
}

void fast_scanner::add_error_here(const std::string &msg) {
    add_error(loc_type(new std::string(_filename), _line, _column), msg);
}

void fast_scanner::scan_start_of_decl_kw() {
    if (match("global")) {
        push_token(tok_type::DECL_KW_GLOBAL, ".global");
    } else if (match("version")) {
        push_token(tok_type::DECL_KW_VERSION, ".version");
    } else if (match("func")) {
        push_token(tok_type::DECL_KW_FUNC, ".func");
    } else if (match("end")) {
        push_token(tok_type::DECL_KW_END, ".end");
    } else {
        add_error_here("Unexpected '.': following token is not a declaration keyword");
    }
}

void fast_scanner::eat_newlines() {
    while (peek() == '\n') {
        next();
    }
}

void fast_scanner::scan_str() {
    if (!match('"')) {
        add_error_here("Expected start of string");
    } else {
        std::stringstream sr;
        while (!at_end() && peek() != '"') {
            sr << next();
        }

        if (at_end()) {
            add_error_here("Expected end of string");
            return;
        } else {
            next(); // eat the final "
        }

        push_token(tok_type::V_STR, sr.str());
    }
}

void fast_scanner::scan_hex_number() {
    // move to beginning of numeric data
    next();
    const char x = next(); // 'X' or 'x'

    std::stringstream sr; // why can't i do sr("0") here????
    sr << "0" << x;

    while (std::isxdigit(peek())) {
        sr << next();
    }

    push_token(tok_type::V_HEX, sr.str());
}

void fast_scanner::scan_bin_number() {
    // move to beginning of numeric data
    next();
    const char b = next(); // 'B' or 'b'

    std::stringstream sr;
    sr << "0" << b;

    while (peek() == '0' || peek() == '1') {
        sr << next();
    }

    push_token(tok_type::V_BIN, sr.str());
}

void fast_scanner::scan_number() {
    if (peek() == '0') {
        if (peek(1) == 'x' || peek(1) == 'X') {
            scan_hex_number();
            return;
        } else if (peek(1) == 'b' || peek(1) == 'B') {
            scan_bin_number();
            return;
        }
    }

    std::stringstream sr;
    while (std::isdigit(peek()) || peek() == '_') {
        const char c = next();
        if (c != '_') {
            sr << c;
        }
    }

    push_token(tok_type::V_DEC, sr.str()); // todo hex, bin
}

static const std::unordered_map<std::string, tok_type> keywords = {
    {"const", tok_type::KW_CONST}, {"static", tok_type::KW_STATIC}, {"i8", tok_type::TYPE_I8},
    {"u8", tok_type::TYPE_U8},     {"i16", tok_type::TYPE_I16},     {"u16", tok_type::TYPE_U16},
    {"i32", tok_type::TYPE_I32},   {"u32", tok_type::TYPE_U32},     {"i64", tok_type::TYPE_I64},
    {"u64", tok_type::TYPE_U64},   {"i128", tok_type::TYPE_I128},   {"u128", tok_type::TYPE_U128},
    {"bool", tok_type::TYPE_BOOL}, {"void", tok_type::TYPE_VOID},   {"str", tok_type::TYPE_STR},
    {"func", tok_type::KW_FUNC},   {"_", tok_type::UNDERSCORE},     {"utf8", tok_type::KW_UTF8},
    {"utf16", tok_type::KW_UTF16}, {"utf32", tok_type::KW_UTF32},   {"export", tok_type::KW_EXPORT},
    {"pure", tok_type::KW_PURE},
};

void fast_scanner::scan_id_or_kw(bool allow_string_id) {
    if (allow_string_id) {
        if (peek() == '"') {
            scan_str();
        } else {
            scan_id_or_kw(false);
        }
    } else {
        std::stringstream sr;
        sr << next();

        // Called upon isalpha, so next can be alnum
        while (isidcontinue(peek())) {
            sr << next();
        }

        if (keywords.find(sr.str()) != keywords.end()) {
            push_token(keywords.at(sr.str()), sr.str());
        } else {
            push_token(tok_type::NAME, sr.str());
        }
    }
}

void fast_scanner::step() {
    const char c = peek();
    switch (c) {
        case '&':
            next();
            push_token(tok_type::AMP, "&");
            break;
        case '.':
            next();
            scan_start_of_decl_kw();
            break;
        case ',':
            next();
            push_token(tok_type::COMMA, ",");
            break;
        case '\n':
            eat_newlines();
            push_token(tok_type::NEWLINES, "\n");
            break;
        case ':':
            next();
            push_token(tok_type::COLON, ":");
            break;
        case '=':
            next();
            push_token(tok_type::EQUALS, "=");
            break;
        case '[':
            next();
            push_token(tok_type::LBRACKET, "[");
            break;
        case ']':
            next();
            push_token(tok_type::RBRACKET, "]");
            break;
        case '-':
            if (match("->")) {
                push_token(tok_type::RET_ARROW, "->");
            } else {
                goto fail;
            }

            break;

        case ' ':
        case '\t':
        case '\r': next(); break;

        case '"': scan_str(); break;

        default: {
            if (isidletter(c)) {
                scan_id_or_kw();
            } else if (std::isdigit(c)) {
                scan_number();
            } else {
            fail:
                add_error_here(std::string("Unexpected token: ") + c);
                next();
            }

            break;
        }
    }
}

std::variant<token_buf *, std::vector<fast_scanner::error>> fast_scanner::run() {
    while (!at_end()) {
        step();
    }

    if (_errors.empty()) {
        return _buf;
    } else {
        delete _buf;
        return _errors;
    }
}
