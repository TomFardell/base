#ifndef ARENA_H
#define ARENA_H

#include <stdlib.h>

#include "definitions.h"

typedef struct Arena {
  u8 *base_pos;
  size_t offset;
  size_t capacity;
} Arena;

// Initialise an arena of a given size
Arena arena_init(size_t size);
// Allocate a block of memory inside an arena, aligning the start of the block with a given alignement
u8 *arena_alloc(Arena *a, size_t size, size_t align);

// Reset a given arena without zeroing its contents
void arena_reset(Arena *a);
// Zero and reset a given arena
void arena_zero(Arena *a);

// Free a given arena
void arena_free(Arena *a);

#endif  // ARENA_H

// vim: filetype=c :
