// Assembly unit transformation utilities.
#pragma once
#include <llvm/IR/Constant.h>
#include <llvm/IR/IRBuilder.h>
#include <llvm/IR/LLVMContext.h>
#include <llvm/IR/Module.h>
#include <llvm/Support/MemoryBuffer.h>
#include <string>
#include <unordered_map>

using llvm::Constant;
using llvm::IRBuilder;
using llvm::LLVMContext;
using llvm::MemoryBuffer;
using llvm::Module;

// Abstracts away llvm::Module for further processing.
class unit final {
  private:
    LLVMContext &m_llctx;
    Module *m_mod;
    std::unordered_map<std::string, Constant *> m_strPool;
    IRBuilder<> m_builder;

  public:
    unit(LLVMContext &ctx);

    // Returns the underlying Module object.
    Module *get_module() const { return m_mod; }

    // Returns the llvm context.
    const LLVMContext &get_context() const { return m_llctx; }

    // Interns the given string and returns a Constant* representing it.
    // Note that this does not create a SRTE string, but an appropiate C pointer type
    Constant *intern_string(const std::string &s);

    // Compiles the unit to LLVM IR.
    std::string compile_ir();

    // Compiles the unit to LLVM bitcode.
    std::unique_ptr<MemoryBuffer> compile_bc();
};
