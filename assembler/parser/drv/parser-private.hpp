// Private data members for the parser
#pragma once
#include <cstdint>

struct parser_private {
    std::uint32_t mods; // currently parsed modifier flags

    parser_private() : mods(0) {}
};
