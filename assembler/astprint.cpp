#include "ast.hpp"
#include <bitset>
#include <iterator>

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

void int_value::print(int indentC, std::ostream &ost) {
    std::string fmt_str = "<invalid>";
    switch (_fmt) {
        case format::Hex: fmt_str = "Hexadecimal"; break;
        case format::Dec: fmt_str = "Decimal"; break;
        case format::Bin: fmt_str = "Binary"; break;
    }

    auto indent = std::string(indentC, ' ');
    indent = std::string(indentC += 4, ' ');
    ost << indent << "Integer value: " << _val << "\n";
    ost << indent << "Format: " << fmt_str << "\n";
}

void str_value::print(int indentC, std::ostream &ost) {
    std::string fmt_str = "<invalid>";
    switch (_fmt) {
        case format::Utf8: fmt_str = "UTF-8"; break;
        case format::Utf16: fmt_str = "UTF-16"; break;
        case format::Utf32: fmt_str = "UTF-32"; break;
    }

    auto indent = std::string(indentC, ' ');
    ost << indent << "String value:\n";

    indent = std::string(indentC += 4, ' ');
    ost << indent << "Value: ";
    std::copy(_data.begin(), _data.end() - 1, std::ostream_iterator<unsigned char>(ost, ", "));
    ost << _data.back() << "\n";

    ost << indent << "Format: " << fmt_str << "\n";
}

void global_var::print(int indentC, std::ostream &ost) {
    auto indent = std::string(indentC, ' ');
    ost << indent << "Global variable declaration:\n";

    indent = std::string(indentC += 4, ' ');
    ost << indent << "Name: " << _name << "\n";
    ost << indent << "Flags: " << std::bitset<32>(_flags) << "\n";
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

    ost << indent << "Global variables(" << _consts.size() << "):\n";
    for (auto &c : _consts) {
        c->print(indentC + 4, ost);
    }
}

void function_param::print(int indentC, std::ostream &ost) {
    auto indent = std::string(indentC, ' ');
    ost << indent << "Function parameter:\n";

    indent = std::string(indentC += 4, ' ');
    ost << indent << "Index: " << _param_index << "\n";
    ost << indent << "Flags: " << std::bitset<32>(_flags);
    ost << indent << "Type:\n";
    _type->print(indentC + 4, ost);
}

void function_def::print(int indentC, std::ostream &ost) {
    auto indent = std::string(indentC, ' ');
    ost << indent << "Function definition:\n";

    indent = std::string(indentC += 4, ' ');
    ost << indent << "Name: " << _name << "\n";
    ost << indent << "Flags: " << std::bitset<32>(_flags) << "\n";
    ost << indent << "Parameters:\n";
    for (auto &p : _params) {
        p->print(indentC, ost);
    }

    ost << indent << "Return type:\n";
    _return_type->print(indentC, ost);
}
