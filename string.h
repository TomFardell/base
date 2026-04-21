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

typedef struct StringArray {
  String *strings;
  U64 count;
} StringArray;

#define string_literal(cstr_lit) (String){(U8 *)cstr_lit, (sizeof cstr_lit) - 1}

// Get a string given a memory location and length
String string_init(U8 *str, U64 len);
// Get the string between a start location (inclusive) and an end location (exclusive)
String string_init_range(U8 *start, U8 *end);
// Get the string equivalent of a given cstring
String string_init_cstring(char *cstr);
// Get the substring of a given string between a start index (inclusive) and an end index (exclusive)
String string_init_substring(String str, U64 start, U64 end);
// Allocate a new string on a given arena
String string_alloc(Arena *a, U64 len);

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
String string_concat_arr(Arena *a, StringArray str_arr);
// Join an array of strings with a given delimeter
String string_join(Arena *a, String delimeter, U64 count, ...);
// Join strings passed as variadic args with a given delimeter
String string_join_arr(Arena *a, String delimeter, StringArray str_arr);
// Get the uppercase of a string
String string_upper(Arena *a, String str);
// Get the lowercase of a string
String string_lower(Arena *a, String str);
// Get the reverse of a string
String string_reverse(Arena *a, String str);
// Format a string using printf format rules
String string_format(Arena *a, const char *format, ...);
// Remove all instances of a substring from a string
String string_remove(Arena *a, String str, String rem);

// Determine whether a substring exists in the given string
bool string_contains(String str, String substr);
// Get the index of the start of the first occurrence of a substring in a string. Return string length if not found
U64 string_find_first(String str, String substr);

// Split a string into an array on a given delimeter. The resulting array is allocated on the passed arena
StringArray string_split(Arena *a, String str, String delimeter);

#endif  // STRING_H

// vim: filetype=c :
