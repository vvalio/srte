#include "codegen.hpp"
#include "ast.hpp"
#include "codegen/mangle.hpp"
#include "codegencontext.hpp"
#include "llvmtype.hpp"
#include <llvm-18/llvm/IR/GlobalValue.h>
#include <llvm/ADT/APInt.h>
#include <llvm/IR/Constant.h>
#include <llvm/IR/Constants.h>
#include <llvm/IR/DerivedTypes.h>
#include <llvm/IR/GlobalVariable.h>
#include <llvm/IR/IRBuilder.h>
#include <llvm/IR/LLVMContext.h>
#include <llvm/IR/Module.h>
#include <llvm/IR/Type.h>
#include <llvm/IR/Value.h>
#include <memory>

// I'm lazy
#define CONTEXT this->m_ctx->llctx
#define BUILDER this->m_ctx->builder

codegen::codegen(std::shared_ptr<assembly_unit> asUnit) {
    m_asUnit = asUnit;
    m_ctx = std::make_shared<codegen_ctx>([](std::shared_ptr<ast_location> loc, std::string err) {
        std::cerr << "At: " << loc->to_string() << ": " << err;
        std::exit(1);
    });
    m_mod = new llvm::Module(asUnit->get_filename(), m_ctx->llctx);
}

bool codegen::compile() {
    traverse();
    m_mod->dump();
    return true;
}

void codegen::traverse() {
    for (auto &glb : m_asUnit->get_globals()) {
        enter_global(glb);
    }
}

void codegen::enter_global(std::shared_ptr<global_var> global) {
    const auto &exp_type = global->get_exported_type();
    auto lltype = get_llvm_type(m_ctx, exp_type);
    if (lltype == nullptr) {
        m_ctx->err_handler(global->get_location(), "Unable to map LLVM type for " + exp_type->to_string());
        return;
    }

    llvm::Constant *init_val = nullptr;
    if (auto init = global->get_value(); init != nullptr) {
        init_val = create_constant(lltype, init);
    }

    const bool is_const = global->get_flags() & global_var::MOD_CONST;
    const auto linkage = (global->get_flags() & global_var::MOD_STATIC) ? llvm::GlobalValue::PrivateLinkage
                                                                        : llvm::GlobalValue::CommonLinkage;
    const auto mangled_name = mangle(global->get_exported_symbol(), global->get_exported_type(), global->get_flags());
    auto gvar = new llvm::GlobalVariable(*m_mod, lltype, is_const, linkage, init_val, mangled_name);
}

llvm::Constant *codegen::create_constant(llvm::Type *typ, std::shared_ptr<literal_base> initializer) {
    // First, create the value corresponding to the initializer
    if (initializer->get_kind() == literal_base::kind::Int) {
        if (!typ->isIntegerTy()) {
            m_ctx->err_handler(initializer->get_location(), "Initializer value not assignable to type");
            return nullptr;
        }

        const auto bw = typ->getIntegerBitWidth();
        return llvm::ConstantInt::get(static_cast<llvm::IntegerType *>(typ), initializer->get_vstr(), 10);
    } else {
        // It's a string!
        const auto str_typ = llvm::StructType::getTypeByName(CONTEXT, STRING_TYP);
        if (!typ->isStructTy() || !static_cast<llvm::StructType *>(typ)->isLayoutIdentical(str_typ)) {
            m_ctx->err_handler(initializer->get_location(), "String type conflict");
            return nullptr;
        }

        // First create the i8*
        auto str_pointer = BUILDER.CreateGlobalStringPtr(initializer->get_vstr(), "", 0, m_mod);

        // Then the struct value
        auto str_val = llvm::ConstantStruct::get(
            static_cast<llvm::StructType *>(typ),
            {
                llvm::ConstantInt::get(llvm::IntegerType::getInt32Ty(CONTEXT), initializer->get_vstr().size()),
                str_pointer,
            });

        return str_val;
    }
}
