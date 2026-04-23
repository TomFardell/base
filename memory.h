#ifndef MEMORY_H
#define MEMORY_H

#include <stdlib.h>

#include "definitions.h"

typedef struct Arena {
  U8 *base_pos;
  U64 offset;
  U64 capacity;
} Arena;

#define mem_equals(m1, m2, size) (memcmp(m1, m2, size) == 0)

// Swap two pointers
void mem_swap(void **mem1, void **mem2);

// -- Arena methods --

// Initialise an arena of a given size
Arena arena_init(U64 size);
// Allocate a block of memory inside an arena, aligning the start of the block with a given alignment
U8 *arena_alloc(Arena *a, U64 size, U8 align);

// Reset a given arena without zeroing its contents
void arena_reset(Arena *a);
// Zero and reset a given arena
void arena_zero(Arena *a);
// Move the offset location back a given number of bytes
void arena_pop(Arena *a, U64 size);

// Free a given arena
void arena_free(Arena *a);

#endif  // MEMORY_H

// vim: filetype=c :
