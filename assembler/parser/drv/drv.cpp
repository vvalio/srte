#include "drv.hpp"
#include "ast.hpp"
#include <memory>

void parser_drv::add_error(const parse_error &err) { _errors.push_back(err); }

std::vector<parse_error> parser_drv::get_errors() const { return _errors; }

void parser_drv::set_result(std::shared_ptr<assembly_unit> unit) {
    if (_result == nullptr) {
        _result = unit;
    }
}

std::shared_ptr<assembly_unit> parser_drv::get_result() const { return _result; }
