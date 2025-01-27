#include "llvmtype.hpp"
#include "codegen/codegencontext.hpp"
#include "type.hpp"
#include <cstdlib>
#include <llvm/IR/DerivedTypes.h>
#include <memory>

static llvm::Type *get_basic_type(std::shared_ptr<codegen_ctx> ctx, const rt_type_basic &typ) {
    switch (typ.get_kind()) {
        case rt_type_kind::I8:
        case rt_type_kind::U8: return llvm::IntegerType::get(ctx->llctx, 8);
        case rt_type_kind::I16:
        case rt_type_kind::U16: return llvm::IntegerType::get(ctx->llctx, 16);
        case rt_type_kind::I32:
        case rt_type_kind::U32: return llvm::IntegerType::get(ctx->llctx, 32);
        case rt_type_kind::I64:
        case rt_type_kind::U64: return llvm::IntegerType::get(ctx->llctx, 64);
        case rt_type_kind::I128:
        case rt_type_kind::U128: return llvm::IntegerType::get(ctx->llctx, 128);
        case rt_type_kind::Bool: return llvm::IntegerType::get(ctx->llctx, 1);
        case rt_type_kind::Void: return llvm::Type::getVoidTy(ctx->llctx);
        case rt_type_kind::String: {
            if (auto str_typ = llvm::StructType::getTypeByName(ctx->llctx, STRING_TYP); str_typ != nullptr) {
                return str_typ;
            }

            return llvm::StructType::create(ctx->llctx,
                                            {
                                                llvm::IntegerType::get(ctx->llctx, 32),
                                                llvm::IntegerType::get(ctx->llctx, 8)->getPointerTo(),
                                            },
                                            STRING_TYP, false);
        }

        default: break;
    }

    std::cerr << "Not a basic type: " << typ.to_string() << "\n";
    std::abort();
}

llvm::Type *get_llvm_type(std::shared_ptr<codegen_ctx> ctx, std::shared_ptr<rt_type_base> typ) {
    return get_llvm_type(ctx, *typ);
}

llvm::Type *get_llvm_type(std::shared_ptr<codegen_ctx> ctx, const rt_type_base &typ) {
    if (typ.is_basic()) {
        return get_basic_type(ctx, static_cast<const rt_type_basic &>(typ));
    }

    return nullptr;
}
