#include "codegencontext.hpp"
#include <llvm/IR/IRBuilder.h>
#include <llvm/IR/LLVMContext.h>

codegen_ctx::codegen_ctx(ErrorHandler err_handler) : builder(llctx), llctx() {
    this->err_handler = err_handler;
    this->clib = std::make_unique<corelib>(llctx);
}
