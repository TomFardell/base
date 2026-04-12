#ifndef STRING_H
#define STRING_H

#include "arena.h"
#include "definitions.h"

typedef struct String {
  U8 *str;
  U64 len;
} String;

// Get a string given a memory location and length
String string_init(U8 *str, U64 len);
// Get the string starting at a start location (inclusive) and ending at an end locatin (exclusive)
String string_init_range(U8 *start, U8 *end);
// Get the string equivalent of a given cstring
String string_init_cstring(char *cstr);

#define string_literal(cstr) (String){(U8 *)cstr, (sizeof cstr) - 1}

// Get a pointer to the null-terminated equiavalent of a String
char *string_get_cstring(Arena *a, String str);

#endif  // STRING_H

// vim: filetype=c :
