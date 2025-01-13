#include "ast.hpp"
#include "parser/srte-asm-parser.hpp"
#include <bitset>
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

void version_decl::print(int indentC, std::ostream &ost) {
    auto indent = std::string(indentC, ' ');
    ost << indent << "Version declaration:\n";

    // indent one more
    indent = std::string(indentC += 4, ' ');
    ost << indent << "Major version: " << std::hex << (int)_maj << "\n";
    ost << indent << "Minor version: " << (int)_min << "\n";
    ost << indent << "Patch version: " << (int)_patch << "\n";
    ost << std::dec; // reset back from std::hex
}

void type_id::print(int indentC, std::ostream &ost) {
    auto indent = std::string(indentC, ' ');
    ost << indent << "Type ID:\n";

    indent = std::string(indentC += 4, ' ');
    std::cout << indent << _type->to_string() << "\n";
}

void global_var::print(int indentC, std::ostream &ost) {
    auto indent = std::string(indentC, ' ');
    const std::bitset<32> bs_flags(_flags);
    ost << indent << "Global variable declaration:\n";

    indent = std::string(indentC += 4, ' ');
    ost << indent << "Name: " << _name << "\n";
    ost << indent << "Flags: " << bs_flags << "\n";
    ost << indent << "Type:\n";
    _type->print(indentC, ost);

    ost << indent << "Value:\n";
    if (_value != nullptr) {
        _value->print(indentC, ost);
    }
}

void assembly_unit::print(int indentC, std::ostream &ost) {
    auto indent = std::string(indentC, ' ');
    ost << indent << "Assembly unit:\n";

    indent = std::string(indentC += 4, ' ');
    ost << indent << "Declared in: " << _filename << "\n";
    ost << indent << "Version:\n";
    if (_version != nullptr) {
        _version->print(indentC + 4, ost);
    }

    ost << indent << "Global variables:\n";
    for (auto &c : _consts) {
        c->print(indentC, ost);
    }
}

std::vector<std::shared_ptr<ast_base>> assembly_unit::get_children() {
    std::vector<std::shared_ptr<ast_base>> result(_consts.size());
    for (auto c : _consts) {
        result.push_back(c);
    }

    return result;
}

void assembly_unit::push_constant(std::shared_ptr<global_var> cdef) { _consts.push_back(cdef); }

void assembly_unit::set_version(std::shared_ptr<version_decl> vd) { _version = vd; }
