// Codegen context data; error reporting, etc
#pragma once
#include "ast.hpp"
#include "runtime-support/corelib.hpp"
#include <llvm/IR/IRBuilder.h>
#include <llvm/IR/LLVMContext.h>
#include <memory>

// Function called upon error
using ErrorHandler = void (*)(std::shared_ptr<ast_location>, std::string);

// Context object that carries data structures and context related to code generation.
struct codegen_ctx final {
    llvm::IRBuilder<> builder;
    llvm::LLVMContext llctx;
    ErrorHandler err_handler;
    std::unique_ptr<corelib> clib;

    codegen_ctx(ErrorHandler err_handler);
};
