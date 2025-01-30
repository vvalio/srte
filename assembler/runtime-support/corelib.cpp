#include "corelib.hpp"
#include <llvm/IR/DerivedTypes.h>
#include <llvm/IR/Function.h>
#include <llvm/IR/GlobalValue.h>
#include <llvm/IR/LLVMContext.h>

const std::string UTF8_STR_INIT_NAME = "_SrCreateUtf8Str_";
const std::string UTF16_STR_INIT_NAME = "_SrCreateUtf16Str_";
const std::string UTF32_STR_INIT_NAME = "_SrCreateUtf32Str_";

// Holds core library data.
struct corelib_data {
    llvm::StructType *str_type;
    llvm::Function *utf8_str_init;
    llvm::Function *utf16_str_init;
    llvm::Function *utf32_str_init;
};

corelib::corelib(llvm::LLVMContext &llctx) : _llctx(llctx) { this->_coredata = new corelib_data(); }

corelib::~corelib() { delete this->_coredata; }

llvm::StructType *corelib::get_srte_str() {
    if (_coredata->str_type == nullptr) {
        _coredata->str_type = llvm::StructType::create(_llctx, {
                                                                   llvm::IntegerType::get(_llctx, 32),
                                                                   llvm::PointerType::get(_llctx, 0),
                                                               });
    }

    return _coredata->str_type;
}

llvm::Function *corelib::get_utf8_str_init() {
    if (_coredata->utf8_str_init == nullptr) {
        auto ft = llvm::FunctionType::get(get_srte_str(),
                                          {
                                              llvm::IntegerType::get(_llctx, 32),
                                              llvm::PointerType::get(_llctx, 0),
                                          },
                                          false);
        _coredata->utf8_str_init =
            llvm::Function::Create(ft, llvm::GlobalValue::AvailableExternallyLinkage, UTF8_STR_INIT_NAME);
    }

    return _coredata->utf8_str_init;
}

llvm::Function *corelib::get_utf16_str_init() {
    if (_coredata->utf16_str_init == nullptr) {
        auto ft = llvm::FunctionType::get(get_srte_str(),
                                          {
                                              llvm::IntegerType::get(_llctx, 32),
                                              llvm::PointerType::get(_llctx, 0),
                                          },
                                          false);
        _coredata->utf16_str_init =
            llvm::Function::Create(ft, llvm::GlobalValue::AvailableExternallyLinkage, UTF16_STR_INIT_NAME);
    }

    return _coredata->utf8_str_init;
}

llvm::Function *corelib::get_utf32_str_init() {
    if (_coredata->utf32_str_init == nullptr) {
        auto ft = llvm::FunctionType::get(get_srte_str(),
                                          {
                                              llvm::IntegerType::get(_llctx, 32),
                                              llvm::PointerType::get(_llctx, 0),
                                          },
                                          false);
        _coredata->utf32_str_init =
            llvm::Function::Create(ft, llvm::GlobalValue::AvailableExternallyLinkage, UTF32_STR_INIT_NAME);
    }

    return _coredata->utf8_str_init;
}
