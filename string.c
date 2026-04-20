#include "string.h"

#include <stdalign.h>
#include <stdarg.h>
#include <stdbool.h>
#include <stdio.h>
#include <string.h>

#define string_abort(message, ...)                                     \
  do {                                                                 \
    _string_abort(message, __FILE__, __LINE__, __func__, __VA_ARGS__); \
  } while (0)

static void _string_abort(const char *message, const char *file, int line, const char *func, ...) {
  va_list args;
  va_start(args, func);

  fprintf(stderr, "\n");
  fprintf(stderr, "> ---| String error |---\n");
  fprintf(stderr, "> Error in %s->%s (line %d)\n", file, func, line);
  fprintf(stderr, "> ");
  vfprintf(stderr, message, args);
  fprintf(stderr, "\n");
  fprintf(stderr, "Terminating program\n");

  va_end(args);

  exit(EXIT_FAILURE);
}

String string_init(U8 *str, U64 len) {
  return (String){str, len};
}

String string_init_range(U8 *start, U8 *end) {
  return string_init(start, end - start);
}

String string_init_cstring(char *cstr) {
  return string_init((U8 *)cstr, strlen(cstr));
}

String string_init_substring(String str, U64 start, U64 end) {
  if (start > end) {
    string_abort("Substring start index after end index (%" U64f " > %" U64f ")\n", start, end);
  }

  if (end > str.len) {
    string_abort("Substring end index greater than string length (%" U64f " > %" U64f ")\n", end, str.len);
  }

  return string_init_range(str.str + start, str.str + end);
}

String string_alloc(Arena *a, U64 len) {
  String result = {arena_alloc(a, len * sizeof(*result.str), alignof(*result.str)), len};

  return result;
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

  Arena a = arena_init((s1.len + s2.len) * sizeof(*s1.str));

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

  String result = string_concat_arr(a, (StringArray){strings, count});

  arena_free(&strings_arena);

  return result;
}

String string_concat_arr(Arena *a, StringArray str_arr) {
  String result = {0};

  for (U64 i = 0; i < str_arr.count; ++i) {
    result.len += str_arr.strings[i].len;
  }

  result.str = arena_alloc(a, result.len, alignof(*result.str));

  for (U64 i = 0, pos = 0; i < str_arr.count; pos += str_arr.strings[i].len, ++i) {
    memcpy(result.str + pos, str_arr.strings[i].str, str_arr.strings[i].len);
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

  String result = string_join_arr(a, delimeter, (StringArray){strings, count});

  arena_free(&strings_arena);

  return result;
}

String string_join_arr(Arena *a, String delimeter, StringArray str_arr) {
  if (str_arr.count == 0) {
    return string_literal("");
  }

  String result = {.len = delimeter.len * (str_arr.count - 1)};

  for (U64 i = 0; i < str_arr.count; ++i) {
    result.len += str_arr.strings[i].len;
  }

  result.str = arena_alloc(a, result.len, alignof(result.str));

  U64 pos = 0;
  for (U64 i = 0; i < str_arr.count - 1; ++i) {
    memcpy(result.str + pos, str_arr.strings[i].str, str_arr.strings[i].len);
    pos += str_arr.strings[i].len;

    memcpy(result.str + pos, delimeter.str, delimeter.len);
    pos += delimeter.len;
  }

  memcpy(result.str + pos, str_arr.strings[str_arr.count - 1].str, str_arr.strings[str_arr.count - 1].len);

  return result;
}

String string_upper(Arena *a, String str) {
  String result = string_alloc(a, str.len);

  for (U64 i = 0; i < result.len; ++i) {
    result.str[i] = str.str[i];

    if ('a' <= result.str[i] && result.str[i] <= 'z') {
      result.str[i] += 'A' - 'a';
    }
  }

  return result;
}

String string_lower(Arena *a, String str) {
  String result = string_alloc(a, str.len);

  for (U64 i = 0; i < result.len; ++i) {
    result.str[i] = str.str[i];

    if ('A' <= str.str[i] && str.str[i] <= 'Z') {
      result.str[i] = str.str[i] + 'a' - 'A';
    }
  }

  return result;
}

String string_reverse(Arena *a, String str) {
  String result = string_alloc(a, str.len);

  for (U64 i = 0; i < str.len; ++i) {
    result.str[i] = str.str[str.len - i - 1];
  }

  return result;
}

// Would almost always be calling this with a literal format, so makes sense to have it as a cstring
String string_format(Arena *a, const char *format, ...) {
  va_list args;
  va_start(args, format);

  // First determine the buffer size required before allocating anything
  U64 size_required = vsnprintf(NULL, 0, format, args);

  va_start(args, format);  // Need to call this again in order to reuse the args

  String result = string_alloc(a, size_required + 1);  // Allocate an extra byte for the null terminator
  vsnprintf((char *)result.str, result.len, format, args);
  arena_pop(a, 1);  // Pop the null terminator, since this is unused
  result.len--;

  va_end(args);

  return result;
}

String string_remove(Arena *a, String str, String rem) {
  if ((rem.len > str.len) || (rem.len == 0)) {
    // TODO: Think about whether this should be a copy
    return str;
  }
  String result = string_alloc(a, str.len);  // Max length would be if nothing is removed

  U64 str_i = 0, res_i = 0;
  while (str_i < str.len) {
    // TODO: memcmp macro
    if ((str_i + rem.len - 1 < str.len) && memcmp(str.str + str_i, rem.str, rem.len) == 0) {
      str_i += rem.len;
      continue;
    }

    result.str[res_i] = str.str[str_i];
    ++str_i;
    ++res_i;
  }

  arena_pop(a, str_i - res_i);  // Pop the unused bytes of the result
  result.len = res_i;
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
        result.strings[result.count++] = string_init_substring(str, i - curr_str_len, i);
      }

      curr_str_len = 0;
      i += delimeter.len - 1;

      continue;
    }

    ++curr_str_len;
  }

  return result;
}
