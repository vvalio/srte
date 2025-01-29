// Memory ownership routines.
#pragma once
#include <stddef.h>

// Allocates a new pointer, copies the data of the passed pointer to it and frees the result.
// type is type of *ptr
#define TAKE(type, ptr) TAKE_N(type, 1, ptr)
#define TAKE_N(type, count, ptr) ((type *)_take(ptr, sizeof(type) * count))

// Copies data from pointer of size size to the destination pointer, and frees the passed pointer.
void *_take(void *pointer, size_t size);
