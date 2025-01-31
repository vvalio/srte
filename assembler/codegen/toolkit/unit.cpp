#include "unit.hpp"
#include <llvm/Bitcode/BitcodeWriter.h>
#include <llvm/IR/GlobalValue.h>
#include <llvm/IR/GlobalVariable.h>
#include <llvm/Support/raw_os_ostream.h>
#include <memory>
#include <sstream>

using llvm::BitcodeWriter;
using llvm::GlobalVariable;

unit::unit(LLVMContext &ctx) : m_llctx(ctx), m_builder(ctx) { m_mod = new Module("<module>", ctx); }

Constant *unit::intern_string(const std::string &s) {
    if (m_strPool.find(s) != m_strPool.end()) {
        return m_strPool[s];
    }

    auto var_name = "__INTERNED_" + std::to_string(m_strPool.size());
    auto s_ptr = m_builder.CreateGlobalStringPtr(s, /* anonymous name */ "", 0, nullptr, false);
    auto len_const = m_builder.getIntN(32, s.size());

    // Global variable for len_const
    auto len_var = new GlobalVariable(len_const->getIntegerType(), true, llvm::GlobalValue::PrivateLinkage, len_const,
                                      var_name + "_LEN");
    // and for s_ptr
    auto s_var = new GlobalVariable(s_ptr->getType(), true, llvm::GlobalValue::PrivateLinkage, s_ptr, var_name);

    // Add both to module
    m_strPool[s] = s_var;
    m_mod->insertGlobalVariable(s_var);
    m_mod->insertGlobalVariable(len_var);

    return s_var;
}

std::string unit::compile_ir() {
    std::stringstream buf;
    buf << m_mod;
    return buf.str();
}

std::unique_ptr<MemoryBuffer> unit::compile_bc() {
    std::stringstream os_buf;
    // Get the llvm stream
    auto bc_buf = llvm::raw_os_ostream(os_buf);
    auto bw = BitcodeWriter(bc_buf);

    // Write the module
    bw.writeModule(*m_mod);
    return MemoryBuffer::getMemBuffer(os_buf.str());
}
