// Fast scanner for the ASM.
#pragma once
#include "parser/srte-asm-parser.hpp"
#include <string>
#include <variant>

// Shorten some names
using tok_type = srte_parser::parser::token_type;
using loc_type = srte_parser::parser::location_type;
using val_type = srte_parser::parser::value_type;

struct token;

class token_buf {
  public:
    std::vector<token *> tokens;
    int index = 0;

    void add(token *t);
    std::string to_string() const;
    token_buf();
    ~token_buf();
};

// Scanner that generates token buffer for parser.
// This is implemented in a separate step so that yylex returns already scanned tokens to the parser,
// which allows us to check the source for scanner errors before moving on to parsing.
class fast_scanner final {
  public:
    enum class error_level {
        Fatal,
        Error,
        Warning,
    };

    struct error {
        loc_type err_loc;
        std::string err_msg;
        error_level level;

        error(loc_type el, std::string em, error_level l) : err_loc(el), err_msg(em), level(l) {}

        std::string to_string();
    };

  private:
    std::string _source, _filename;
    int _index, _line, _column;
    token_buf *_buf;
    std::vector<error> _errors;

    inline char peek(int n = 0) { return _source[_index + n]; }
    inline char next() {
        const char c = peek();
        if (c == '\n') {
            _line++;
            _column = 1;
        } else {
            _column++;
        }

        _index++;
        return c;
    }

    inline bool match(char what) {
        if (peek() == what) {
            next();
            return true;
        }

        return false;
    }

    inline bool match(const std::string &what) {
        const int bLine = _line;
        const int bCol = _column;
        const int bIdx = _index;

        for (const char c : what) {
            if (!match(c)) {
                _line = bLine;
                _column = bCol;
                _index = bIdx;
                return false;
            }
        }

        return true;
    }

    inline bool at_end() { return (int)_source.length() <= _index; }

    void scan_number();
    void scan_hex_number();
    void scan_bin_number();
    void scan_id_or_kw(bool allow_string_id = true);
    void scan_start_of_decl_kw();
    void eat_newlines();
    void eat_until_newline();
    void scan_str();

    void push_token(tok_type t, std::string lit);

    void add_error(loc_type l, const std::string &msg);
    void add_error_here(const std::string &msg);

    void step();

  public:
    fast_scanner(const std::string &source, const std::string &fname);
    ~fast_scanner();

    std::variant<token_buf *, std::vector<error>> run();
};
