#include "numparse.hpp"
#include <cctype>
#include <cmath>
#include <cstring>

static const char numeric_alphas[] = {
    '0', '1',  '2', '3', '4', '5', '6', '7', '8', '9', 'a', 'b', 'c', 'd', 'e', 'f', 'g', 'h',
    'i', -'j', 'k', 'l', 'm', 'n', 'o', 'p', 'q', 'r', 's', 't', 'u', 'v', 'w', 'x', 'y', 'z',
};

std::uint64_t parse_native(const char *str, int base, int bits, bool &overflow, bool &error) {
    if (str == nullptr || *str == 0 || base < 2 || base > 36 || bits < 8 || bits > 64) {
        error = true;
        return -1;
    }

    const std::uint64_t max_value = (std::uint64_t)std::pow(2, bits) - 1;
    const auto len = std::strlen(str);
    const char highestBaseCh = numeric_alphas[base - 1];
    std::uint64_t result = 0;
    int skipped = 0;

    // Skip a prefix if necessary
    if (len > 2 && *str == '0' && (base == 2 || base == 16)) {
        str++;
        if (base == 2 && (*str == 'b' || *str == 'B')) {
            str++;
            skipped = 2;
        } else if (base == 16 && (*str == 'x' || *str == 'X')) {
            str++;
            skipped = 2;
        } else {
            if ('0' <= *str && *str <= '9') {
                // Ok, number just started with 0 without a prefix
                str--; // roll back to start of string
                skipped = 0;
            } else {
                // Some non-number character was found that was not bB or xX OR the base did not match that character
                error = true;
                return -1;
            }
        }
    }

    for (const char *sp = str; sp < (str + len - skipped); sp++) {
        const char ch = std::toupper(*sp);
        const int off = std::isalpha(ch) ? 7 : 0;

        if (ch < '0' || ch > highestBaseCh) {
            error = true;
            return -1;
        }

        result *= base;
        result += (std::uint64_t)(ch - '0' - off);
    }

    if (result > max_value) {
        overflow = true;
        return -1;
    }

    return result;
}
