#ifndef STRING_H
#define STRING_H

#include <stdarg.h>
#include <stdbool.h>

#include "arena.h"
#include "definitions.h"

typedef struct String {
  U8 *str;
  U64 len;
} String;

#define string_literal(cstr_lit) (String){(U8 *)cstr_lit, (sizeof cstr_lit) - 1}

// Get a string given a memory location and length
String string_init(U8 *str, U64 len);
// Get the string between a start location (inclusive) and an end location (exclusive)
String string_init_range(U8 *start, U8 *end);
// Get the string equivalent of a given cstring
String string_init_cstring(char *cstr);

// Get the null-terminated equiavalent of a String, alllocating the result on the given arena
char *string_get_cstring(Arena *a, String str);

// Check whether two strings are equal
bool string_equals(String s1, String s2);
// Check whether two strings are equal up to differences in case
bool string_like(String s1, String s2);

// -- These methods allocate the resulting string on the arena passed to them --

// Copy a string
String string_copy(Arena *a, String str);
// Get the result of prepending a given prefix to a string
String string_prepend(Arena *a, String str, String prefix);
// Get the result of appending a given suffix to a string
String string_append(Arena *a, String str, String suffix);
// Concatenate strings passed as variadic args
String string_concat(Arena *a, U64 count, ...);
// Concatenate an array of strings
String string_concat_arr(Arena *a, U64 count, String *strings);
// Get the uppercase of a string
String string_upper(Arena *a, String str);
// Get the lowercase of a string
String string_lower(Arena *a, String str);

#endif  // STRING_H

// vim: filetype=c :
