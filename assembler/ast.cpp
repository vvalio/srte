#include "ast.hpp"
#include "parser/srte-asm-parser.hpp"
#include <bitset>
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

std::vector<std::shared_ptr<ast_base>> assembly_unit::get_children() {
    std::vector<std::shared_ptr<ast_base>> result(_consts.size());
    for (auto c : _consts) {
        result.push_back(c);
    }

    return result;
}

void assembly_unit::push_constant(std::shared_ptr<global_var> cdef) { _consts.push_back(cdef); }

void assembly_unit::set_version(std::shared_ptr<version_decl> vd) { _version = vd; }
