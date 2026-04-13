#include "string.h"

#include <stdarg.h>
#include <stdbool.h>
#include <stdio.h>
#include <string.h>

String string_init(U8 *str, U64 len) {
  return (String){str, len};
}

String string_init_range(U8 *start, U8 *end) {
  return string_init(start, end - start);
}

String string_init_cstring(char *cstr) {
  return string_init((U8 *)cstr, strlen(cstr));
}

char *string_get_cstring(Arena *a, String str) {
  char *cstr = (char *)arena_alloc(a, str.len + 1, 1);
  memcpy(cstr, str.str, str.len);
  cstr[str.len] = '\0';

  return cstr;
}

bool string_equals(String s1, String s2) {
  if (s1.len != s2.len) {
    return false;
  }

  return (memcmp(s1.str, s2.str, s1.len) == 0);
}

String string_append(Arena *a, String str, String suffix) {
  String result;
  result.len = str.len + suffix.len;
  result.str = arena_alloc(a, result.len, 1);

  memcpy(result.str, str.str, str.len);
  memcpy(result.str + str.len, suffix.str, suffix.len);

  return result;
}

String string_prepend(Arena *a, String str, String prefix) {
  return string_append(a, prefix, str);
}

String string_concat(Arena *a, U64 count, ...) {
  va_list args;
  va_start(args, count);

  U64 strings_size = count * sizeof(String);
  Arena string_arena = arena_init(strings_size);
  String *strings = (String *)arena_alloc(&string_arena, strings_size, 8);

  for (U64 i = 0; i < count; ++i) {
    strings[i] = va_arg(args, String);
  }

  va_end(args);

  String result = string_concat_arr(a, count, strings);

  arena_free(&string_arena);

  return result;
}

String string_concat_arr(Arena *a, U64 count, String *strings) {
  String result = {0};

  for (U64 i = 0; i < count; ++i) {
    result.len += strings[i].len;
  }

  result.str = arena_alloc(a, result.len, 1);

  for (U64 i = 0, pos = 0; i < count; pos += strings[i].len, ++i) {
    memcpy(result.str + pos, strings[i].str, strings[i].len);
  }

  return result;
}
