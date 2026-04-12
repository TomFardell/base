#include "arena.h"

#include <stdarg.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define arena_abort(message, ...) _arena_abort(message, __FILE__, __LINE__, __VA_ARGS__)
static void _arena_abort(const char *message, const char *file, int line, ...) {
  va_list args;
  va_start(args, line);

  printf("----| Arena error |----\n");
  printf("> Error in %s on line %d\n", file, line);
  printf("> ");
  vfprintf(stderr, message, args);
  printf("Terminating program\n");

  va_end(args);

  exit(EXIT_FAILURE);
}

Arena arena_init(U64 size) {
  Arena a = {
      .base_pos = malloc(size),
      .offset = 0,
      .capacity = size,
  };

  if (!a.base_pos) {
    arena_abort("Error allocating arena of size %zu bytes\n", size);
  }

  return a;
}

U8 *arena_alloc(Arena *a, U64 size, U8 align) {
  // Align the first byte to the specified alignment
  if (a->offset % align) {
    a->offset += align - (a->offset % align);
  }

  U8 *start_pos = a->base_pos + a->offset;

  a->offset += size;

  if (a->offset > a->capacity) {
    return NULL;  // Return a null pointer if not enough memory allocated
  }

  return start_pos;
}

void arena_reset(Arena *a) {
  a->offset = 0;
}

void arena_zero(Arena *a) {
  memset(a->base_pos, 0, a->capacity);
  arena_reset(a);
}

void arena_free(Arena *a) {
  free(a->base_pos);
  a->base_pos = NULL;
}
