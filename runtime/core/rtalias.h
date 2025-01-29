// Alias helper macros.
#pragma once

#define SR_STRONG_ALIAS(type, aliasname, target, ...) type aliasname(__VA_ARGS__) __attribute__((alias(#target)))
