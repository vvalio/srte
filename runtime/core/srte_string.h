// String type and function defintions.
#pragma once
#include <stdint.h>

typedef struct _SrString {
    uint32_t len;
    uint8_t *bytes;
} SrStr;
