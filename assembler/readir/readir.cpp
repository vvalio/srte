#include "readir.hpp"
#include "resources/core_ir_data.hpp"
#include <llvm/IRReader/IRReader.h>

// Global variables, since these ore once loaded.
static bool loaded = false;

static llvm::Type *str_type;

void read_ir::load_core_ir_data() {
    if (loaded) {
        return;
    }

    auto mod = llvm::parseIR(strdefs_ir, diag, sf);
}
