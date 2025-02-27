#include "ast.hpp"
#include "parser/srte-asm-parser.hpp"
#include "type.hpp"
#include <iterator>
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

    return std::make_shared<rt_type_function>(_return_type->get_rt_type(), param_types);
}

std::vector<std::shared_ptr<ast_base>> function_def::get_children() { return {}; }

std::vector<std::shared_ptr<ast_base>> instruction_arg::get_children() {
    // Ugh...
    std::shared_ptr<ast_base> dest;
    switch (_data.index()) {
        case 0: dest = std::get<std::shared_ptr<register_reference>>(_data); break;
        case 1: dest = std::get<std::shared_ptr<literal_base>>(_data); break;
        case 2: dest = std::get<std::shared_ptr<argument_reference>>(_data); break;
    }

    return {_qualtype, dest};
}

std::vector<std::shared_ptr<ast_base>> instruction_invocation::get_children() {
    std::vector<std::shared_ptr<ast_base>> result(_args.size());
    for (auto &arg : _args) {
        const auto &arg_children = arg->get_children();
        for (auto &arg_child : arg_children) {
            result.push_back(arg_child);
        }
    }

    return result;
}

std::vector<std::shared_ptr<ast_base>> assembly_unit::get_children() {
    std::vector<std::shared_ptr<ast_base>> result(_globals.size());
    for (auto c : _globals) {
        result.push_back(c);
    }

    return result;
}

void assembly_unit::add_globals(std::vector<std::shared_ptr<global_var>> globals) {
    std::copy(globals.begin(), globals.end(), std::back_inserter(_globals));
}

void assembly_unit::add_functions(std::vector<std::shared_ptr<function_def>> funcs) {
    std::copy(funcs.begin(), funcs.end(), std::back_inserter(_funcs));
}

void assembly_unit::set_version(std::shared_ptr<version_decl> vd) { _version = vd; }
