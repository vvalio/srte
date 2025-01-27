// Main code generator interface.
#pragma once
#include "ast.hpp"
#include "codegencontext.hpp"
#include <llvm/IR/IRBuilder.h>
#include <llvm/IR/LLVMContext.h>
#include <llvm/IR/Module.h>
#include <memory>

// Takes assembly units and turns them into LLVM IR.
class codegen final {
  private:
    // The assembly unit being processed.
    std::shared_ptr<assembly_unit> m_asUnit;
    // LLVM module being generated
    llvm::Module *m_mod;
    std::shared_ptr<codegen_ctx> m_ctx;

  public:
    // Creates a new codegen for the specified assembly unit.
    codegen(std::shared_ptr<assembly_unit> asUnit);

    // Compiles the selected assembly unit, returning whether compilation succeeded or not
    bool compile();

  private:
    void traverse();
    void enter_version(std::shared_ptr<version_decl> ver);
    void enter_global(std::shared_ptr<global_var> global);
    void enter_function(std::shared_ptr<function_def> func);

    llvm::Constant *create_constant(llvm::Type *typ, std::shared_ptr<literal_base> initializer);
};
