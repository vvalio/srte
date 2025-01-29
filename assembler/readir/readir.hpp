// Reads LLVM IR types from a string stream and supports fetching types, constants, etc from that IR.
#pragma once
#include <llvm/IR/Function.h>
#include <llvm/IR/Type.h>

// Helper functions for parsing IR
namespace read_ir {

// Loads core IR definitions for access.
void load_core_ir_data();

// Returns the string type.
llvm::Type *get_srte_str();

// Returns the function to create a UTF-8 string.
llvm::Function *get_utf8_str_init();
// Returns the function to create a UTF-16 string.
llvm::Function *get_utf16_str_init();
// Returns the function to create a UTF-32 string.
llvm::Function *get_utf32_str_init();

}; // namespace read_ir
