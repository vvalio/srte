// Number parsing routines for different bases.
#pragma once
#include <cstdint>

// Uses native/emulated 64-bit math, relying on uint64_t.
// str is NULL-terminated.
// If bits is 2 or 16, a prefix `0[bB]` or `0[xX]` is parsed if present, respectively.
// Bits represents the max bit size of the returned value, and `overflow = true` is set if an overflow occurs.
// If parsing str as a valid `base` number of `bits` size fails, `error = true` is set.
// Overflow is also set to true in case of any parameter error:
// - base must be between 2 and 36
// - bits must be between 8 and 64
// - str must be non-null and non-empty
std::uint64_t parse_native(const char *str, int base, int bits, bool &overflow, bool &error);
