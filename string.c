#include "string.h"

#include <stdalign.h>
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
  char *cstr = (char *)arena_alloc(a, str.len + 1, alignof(*cstr));
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

bool string_like(String s1, String s2) {
  if (s1.len != s2.len) {
    return false;
  }

  Arena a = arena_init(s1.len + s2.len);

  String s1_low = string_lower(&a, s1);
  String s2_low = string_lower(&a, s2);

  bool result = (memcmp(s1_low.str, s2_low.str, s1_low.len) == 0);

  arena_free(&a);

  return result;
}

String string_copy(Arena *a, String str) {
  String result = string_init(arena_alloc(a, str.len, alignof(*result.str)), str.len);

  memcpy(result.str, str.str, str.len);

  return result;
}

String string_append(Arena *a, String str, String suffix) {
  String result = string_init(arena_alloc(a, str.len + suffix.len, alignof(*result.str)), str.len + suffix.len);

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
  Arena strings_arena = arena_init(strings_size);
  String *strings = (String *)arena_alloc(&strings_arena, strings_size, alignof(*strings));

  for (U64 i = 0; i < count; ++i) {
    strings[i] = va_arg(args, String);
  }

  va_end(args);

  String result = string_concat_arr(a, count, strings);

  arena_free(&strings_arena);

  return result;
}

// TODO: Consider changing to StringArray
String string_concat_arr(Arena *a, U64 count, String *strings) {
  String result = {0};

  for (U64 i = 0; i < count; ++i) {
    result.len += strings[i].len;
  }

  result.str = arena_alloc(a, result.len, alignof(*result.str));

  for (U64 i = 0, pos = 0; i < count; pos += strings[i].len, ++i) {
    memcpy(result.str + pos, strings[i].str, strings[i].len);
  }

  return result;
}

String string_join(Arena *a, String delimeter, U64 count, ...) {
  va_list args;
  va_start(args, count);

  U64 strings_size = count * sizeof(String);
  Arena strings_arena = arena_init(strings_size);
  String *strings = (String *)arena_alloc(&strings_arena, strings_size, alignof(*strings));

  for (U64 i = 0; i < count; ++i) {
    strings[i] = va_arg(args, String);
  }

  va_end(args);

  String result = string_join_arr(a, delimeter, count, strings);

  arena_free(&strings_arena);

  return result;
}

String string_join_arr(Arena *a, String delimeter, U64 count, String *strings) {
  if (count == 0) {
    return string_literal("");
  }

  String result = {.len = delimeter.len * (count - 1)};

  for (U64 i = 0; i < count; ++i) {
    result.len += strings[i].len;
  }

  result.str = arena_alloc(a, result.len, alignof(result.str));

  U64 pos = 0;
  for (U64 i = 0; i < count - 1; ++i) {
    memcpy(result.str + pos, strings[i].str, strings[i].len);
    pos += strings[i].len;

    memcpy(result.str + pos, delimeter.str, delimeter.len);
    pos += delimeter.len;
  }

  memcpy(result.str + pos, strings[count - 1].str, strings[count - 1].len);

  return result;
}

String string_upper(Arena *a, String str) {
  String result = string_copy(a, str);

  for (U64 i = 0; i < result.len; ++i) {
    if ('a' <= result.str[i] && result.str[i] <= 'z') {
      result.str[i] += 'A' - 'a';
    }
  }

  return result;
}

String string_lower(Arena *a, String str) {
  String result = string_copy(a, str);

  for (U64 i = 0; i < result.len; ++i) {
    if ('A' <= result.str[i] && result.str[i] <= 'Z') {
      result.str[i] += 'a' - 'A';
    }
  }

  return result;
}

StringArray string_split(Arena *a, String str, String delimeter) {
  if (delimeter.len == 0) {
    StringArray result = {(String *)arena_alloc(a, sizeof(*result.strings), alignof(*result.strings)), 1};
    result.strings[0] = string_copy(a, str);

    return result;
  }

  // Get the pointer to where the strings will be allocated without actually making an allocation
  StringArray result = {(String *)arena_alloc(a, 0, alignof(*result.strings)), 0};

  for (U64 i = 0, curr_str_len = 0; i <= str.len; ++i) {
    if ((i == str.len) || string_equals(string_init(str.str + i, delimeter.len), delimeter)) {
      if (curr_str_len > 0) {
        // Since we don't use the arena for anything else, we can assume the strings will be allocated in a block
        arena_alloc(a, sizeof(*result.strings), alignof(*result.strings));
        // TODO: Write substring method
        result.strings[result.count++] = string_init(str.str + i - curr_str_len, curr_str_len);
      }

      curr_str_len = 0;
      i += delimeter.len - 1;

      continue;
    }

    ++curr_str_len;
  }

  return result;
}
