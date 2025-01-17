#include "ast.hpp"
#include "parser/srte-asm-parser.hpp"
#include "type.hpp"
#include <memory>
#include <string>

std::string ast_location::to_string() {
    std::stringstream sr;
    sr << "[at " << line << ":" << col << ", " << file_name << "]";
    return sr.str();
}

/* static */ std::shared_ptr<ast_location> ast_location::from_bison_location(srte_parser::parser::location_type loc,
                                                                             const std::string &filename) {
    return std::shared_ptr<ast_location>(new ast_location(filename, loc.begin.line, loc.begin.column));
}

ast_base::ast_base(const ast_base &c) { _location = c._location; }

std::shared_ptr<rt_type_base> function_def::get_exported_type() {
    std::vector<std::shared_ptr<rt_type_base>> param_types;
    for (auto &p : _params) {
        param_types.push_back(p->get_param_type()->get_rt_type());
    }

    return std::make_shared<rt_type_function>(_return_type, param_types);
}

std::vector<std::shared_ptr<ast_base>> function_def::get_children() { return {}; }

std::vector<std::shared_ptr<ast_base>> assembly_unit::get_children() {
    std::vector<std::shared_ptr<ast_base>> result(_consts.size());
    for (auto c : _consts) {
        result.push_back(c);
    }

    return result;
}

void assembly_unit::push_constant(std::shared_ptr<global_var> cdef) { _consts.push_back(cdef); }

void assembly_unit::set_version(std::shared_ptr<version_decl> vd) { _version = vd; }
