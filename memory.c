#include "memory.h"

#include <stdarg.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define memory_abort(message, ...)                                     \
  do {                                                                 \
    _memory_abort(message, __FILE__, __LINE__, __func__, __VA_ARGS__); \
  } while (0)

static void _memory_abort(const char *message, const char *file, int line, const char *func, ...) {
  va_list args;
  va_start(args, func);

  fprintf(stderr, "\n");
  fprintf(stderr, "> ---| Memory error |---\n");
  fprintf(stderr, "> Error in %s->%s (line %d)\n", file, func, line);
  fprintf(stderr, "> ");
  vfprintf(stderr, message, args);
  fprintf(stderr, "\n");
  fprintf(stderr, "Terminating program\n");

  va_end(args);

  exit(EXIT_FAILURE);
}

void mem_swap(void **mem1, void **mem2) {
  void *temp = *mem1;
  *mem1 = *mem2;
  *mem2 = temp;
}

Arena arena_init(U64 size) {
  Arena a = {
      .base_pos = malloc(size),
      .offset = 0,
      .capacity = size,
  };

  if (!a.base_pos) {
    memory_abort("Error allocating arena of size %" U64f " bytes\n", size);
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
    memory_abort("Attempting to allocate %" U64f " bytes in arena of capacity %" U64f "\n", a->offset,
                 a->capacity);
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

void arena_pop(Arena *a, U64 size) {
  U64 to_pop = clamp_above(size, a->offset);  // Pop at most the offset
  a->offset -= to_pop;
}

void arena_free(Arena *a) {
  free(a->base_pos);
  a->base_pos = NULL;
}
