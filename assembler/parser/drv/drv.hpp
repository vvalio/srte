// Parser driver implementation, mostly for carrying context in the parsing process.
#pragma once
#include "ast.hpp"
#include "parser/location.hh"
#include <memory>
#include <string>
#include <vector>

struct parse_error {
    const std::string message;
    const srte_parser::location &location;

    parse_error(const std::string &msg, const srte_parser::location &loc) : message(msg), location(loc) {}
};

class parser_drv {
  private:
    std::vector<parse_error> _errors;
    std::shared_ptr<assembly_unit> _result;

  public:
    void add_error(const parse_error &err);
    std::vector<parse_error> get_errors() const;
    void set_result(std::shared_ptr<assembly_unit> unit);
    std::shared_ptr<assembly_unit> get_result() const;
};
