#include "string.h"

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
