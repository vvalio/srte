#include "opcode.hpp"
#include <string>
#include <unordered_map>

bool opcode_returns_value(const opcode op) {
    switch (op) {
        case opcode::addi: return true;
        case opcode::ret: return false;
        default: return false;
    }
}

std::string opcode_to_string(const opcode op) {
    switch (op) {
        case opcode::addi: return "addi";
        case opcode::ret: return "ret";
        default: return "<invalid>";
    }
}

static std::unordered_map<std::string, opcode> _opcodes_lookup = {
    {"addi", opcode::addi},
    {"ret", opcode::ret},
};

opcode opcode_lookup(const std::string &d) {
    if (_opcodes_lookup.find(d) == _opcodes_lookup.end()) {
        return opcode::INVALID;
    }

    return _opcodes_lookup[d];
}
