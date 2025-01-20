// Opcode definitions for instructions.
#pragma once
#include <string>

enum class opcode {
    addi,
    ret,

    INVALID,
};

bool opcode_returns_value(const opcode op);
std::string opcode_to_string(const opcode op);
opcode opcode_lookup(const std::string &d);
