#include "ast.hpp"
#include "opcode.hpp"
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

void int_literal::print(int indentC, std::ostream &ost) {
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

void str_literal::print(int indentC, std::ostream &ost) {
    std::string enc_str = "<invalid>";
    switch (_fmt) {
        case encoding::Utf8: enc_str = "UTF-8"; break;
        case encoding::Utf16: enc_str = "UTF-16"; break;
        case encoding::Utf32: enc_str = "UTF-32"; break;
    }

    auto indent = std::string(indentC, ' ');
    ost << indent << "String value:\n";

    indent = std::string(indentC += 4, ' ');
    ost << indent << "Value: ";
    std::copy(_data.begin(), _data.end() - 1, std::ostream_iterator<unsigned char>(ost, ", "));
    ost << _data.back() << "\n";

    ost << indent << "Format: " << enc_str << "\n";
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

    ost << indent << "Global variables(" << _globals.size() << "):\n";
    for (auto &c : _globals) {
        c->print(indentC + 4, ost);
    }

    ost << indent << "Functions(" << _funcs.size() << "):\n";
    for (auto &f : _funcs) {
        f->print(indentC + 4, ost);
    }
}

void function_param::print(int indentC, std::ostream &ost) {
    auto indent = std::string(indentC, ' ');
    ost << indent << "Function parameter:\n";

    indent = std::string(indentC += 4, ' ');
    ost << indent << "Index: " << _param_index << "\n";
    ost << indent << "Flags: " << std::bitset<32>(_flags) << "\n";
    _type->print(indentC, ost);
}

void function_def::print(int indentC, std::ostream &ost) {
    auto indent = std::string(indentC, ' ');
    ost << indent << "Function definition:\n";

    indent = std::string(indentC += 4, ' ');
    ost << indent << "Name: " << _name << "\n";
    ost << indent << "Flags: " << std::bitset<32>(_flags) << "\n";
    ost << indent << "Signature: " << get_exported_type()->to_string() << "\n";
    ost << indent << "Parameters:\n";
    for (auto &p : _params) {
        p->print(indentC, ost);
    }

    ost << indent << "Return type:\n";
    _return_type->print(indentC, ost);

    ost << indent << "Body:\n";
    for (const auto &ins : _instructions) {
        ins->print(indentC + 4, ost);
    }
}

void assign_instruction_invocation::print(int indentC, std::ostream &ost) {
    auto indent = std::string(indentC, ' ');
    ost << indent << "Instruction invocation:\n";

    indent = std::string(indentC += 4, ' ');
    ost << indent << "Opcode: " << opcode_to_string(_op) << "\n";
    ost << indent << "Arguments:\n";
    for (auto &arg : get_args()) {
        arg->print(indentC + 4, ost);
    }

    ost << indent << "Target register:\n";
    _target_reg->print(indentC + 4, ost);
}

void void_instruction_invocation::print(int indentC, std::ostream &ost) {
    auto indent = std::string(indentC, ' ');
    ost << indent << "Instruction invocation:\n";

    indent = std::string(indentC += 4, ' ');
    ost << indent << "Opcode: " << opcode_to_string(_op) << "\n";
    ost << indent << "Has result value suppression: " << _has_suppression << "\n";
    ost << indent << "Arguments:\n";
    for (const auto &arg : _args) {
        arg->print(indentC + 4, ost);
    }
}

void register_reference::print(int indentC, std::ostream &ost) {
    const auto indent = std::string(indentC, ' ');
    ost << indent << "Register reference: " << _reg_idx << "\n";
}

void argument_reference::print(int indentC, std::ostream &ost) {
    const auto indent = std::string(indentC, ' ');
    ost << indent << "Argument reference: " << _arg_idx << "\n";
}

void instruction_arg::print(int indentC, std::ostream &ost) {
    auto indent = std::string(indentC, ' ');
    ost << indent << "Instruction argument:\n";

    indent = std::string(indentC += 4, ' ');
    _qualtype->print(indentC, ost);

    ost << indent << "Value:\n";
    // Second child is the argument data
    get_children()[1]->print(indentC + 4, ost);
}

// So we can have a vtable
void argument_reference::prevent_error() {}
