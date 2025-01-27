// Routines to turn SRTE types into LLVM types.
#pragma once
#include "codegencontext.hpp"
#include "type.hpp"
#include <llvm/IR/Type.h>
#include <memory>
#include <string>

// String struct name
const std::string STRING_TYP = "srte.str";

// Returns the matching LLVM type for the given type.
llvm::Type *get_llvm_type(std::shared_ptr<codegen_ctx> ctx, const rt_type_base &typ);
llvm::Type *get_llvm_type(std::shared_ptr<codegen_ctx> ctx, std::shared_ptr<rt_type_base> typ);
