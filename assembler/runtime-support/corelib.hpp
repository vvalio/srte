// Core runtime type and function definitions
#pragma once
#include <llvm-19/llvm/IR/DerivedTypes.h>
#include <llvm/IR/Function.h>
#include <llvm/IR/LLVMContext.h>
#include <llvm/IR/Type.h>

// Holds types and functions
struct corelib_data;

// Helper functions for getting basic types for the runtime
class corelib final {
  private:
    llvm::LLVMContext &_llctx;
    corelib_data *_coredata;

  public:
    corelib(llvm::LLVMContext &llctx);
    ~corelib();

    // Returns the string type.
    llvm::StructType *get_srte_str();

    // Returns the function to create a UTF-8 string.
    llvm::Function *get_utf8_str_init();
    // Returns the function to create a UTF-16 string.
    llvm::Function *get_utf16_str_init();
    // Returns the function to create a UTF-32 string.
    llvm::Function *get_utf32_str_init();
};
