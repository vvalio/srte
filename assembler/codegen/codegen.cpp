#include "codegen.hpp"
#include "ast.hpp"
#include "codegen/mangle.hpp"
#include "codegencontext.hpp"
#include "llvmtype.hpp"
#include <llvm-19/llvm/IR/BasicBlock.h>
#include <llvm-19/llvm/IR/Function.h>
#include <llvm/ADT/APInt.h>
#include <llvm/IR/Constant.h>
#include <llvm/IR/Constants.h>
#include <llvm/IR/DerivedTypes.h>
#include <llvm/IR/GlobalValue.h>
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

#define ITY(w) BUILDER.getIntNTy(w)
#define I(w, v) BUILDER.getIntN(w, v)

static const std::string MAIN_FN = "main";
static const std::string INIT_FN = "__SrModuleInit";

codegen::codegen(std::shared_ptr<assembly_unit> asUnit) : m_asUnit(asUnit), m_initFunc(nullptr) {
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

    // Create the main function
    auto main_fn_type = llvm::FunctionType::get(ITY(32), false);
    auto main_fn = llvm::Function::Create(main_fn_type, llvm::GlobalValue::CommonLinkage, MAIN_FN, m_mod);
    if (m_initFunc != nullptr) {
        auto init_blk = llvm::BasicBlock::Create(CONTEXT);

        // Make sure the function returns first
        auto ret_blk = llvm::BasicBlock::Create(CONTEXT);
        BUILDER.SetInsertPoint(ret_blk->begin());
        BUILDER.CreateRetVoid();
        m_initFunc->insert(m_initFunc->end(), ret_blk);

        // Call the init func
        BUILDER.SetInsertPoint(init_blk->end());
        BUILDER.CreateCall(m_initFunc->getFunctionType(), m_initFunc);

        main_fn->insert(main_fn->begin(), init_blk);
    }

    // Return with a 0 value
    auto end_blk = llvm::BasicBlock::Create(CONTEXT);
    BUILDER.SetInsertPoint(end_blk->begin());
    BUILDER.CreateRet(I(32, 0));

    main_fn->insert(main_fn->end(), end_blk);
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

void codegen::add_init(llvm::BasicBlock *bblk) {
    if (m_initFunc == nullptr) {
        auto init_func_type = llvm::FunctionType::get(BUILDER.getVoidTy(), false);
        m_initFunc = llvm::Function::Create(init_func_type, llvm::GlobalValue::PrivateLinkage, INIT_FN, m_mod);
    }

    m_initFunc->insert(m_initFunc->end(), bblk);
}

void codegen::add_string_init(uint32_t length, llvm::Constant *vptr, str_literal::encoding encoding) {
    llvm::Function *str_init_func;
    switch (encoding) {
        case str_literal::encoding::Utf8: str_init_func = m_ctx->clib->get_utf8_str_init(); break;
        case str_literal::encoding::Utf16: str_init_func = m_ctx->clib->get_utf16_str_init(); break;
        case str_literal::encoding::Utf32: str_init_func = m_ctx->clib->get_utf32_str_init(); break;
    }

    auto bblk = llvm::BasicBlock::Create(CONTEXT);
    BUILDER.SetInsertPoint(bblk->begin());
    BUILDER.CreateCall(str_init_func->getFunctionType(), str_init_func, {I(32, length), vptr});

    add_init(bblk);
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
        const auto str_typ = m_ctx->clib->get_srte_str();
        const auto init = static_cast<const str_literal &>(*initializer);
        if (!typ->isStructTy() || !static_cast<llvm::StructType *>(typ)->isLayoutIdentical(str_typ)) {
            m_ctx->err_handler(initializer->get_location(), "String type conflict");
            return nullptr;
        }

        // First create the i8*
        auto str_pointer = BUILDER.CreateGlobalStringPtr(init.get_vstr(), "", 0, m_mod);

        // Then the struct value
        auto str_val = llvm::ConstantStruct::get(
            static_cast<llvm::StructType *>(typ),
            {
                llvm::ConstantInt::get(llvm::IntegerType::getInt32Ty(CONTEXT), init.get_vstr().size()),
                str_pointer,
            });

        add_string_init(init.get_vstr().length(), str_pointer, init.get_encoding());
        return str_val;
    }
}
