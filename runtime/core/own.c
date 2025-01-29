#include "own.h"
#include <stdlib.h>
#include <string.h>

void *_take(void *ptr, size_t size) {
    void *newptr = malloc(size);
    memcpy(newptr, ptr, size);

    return newptr;
}
