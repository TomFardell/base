/*--------*/
/* String */
/*---------------------------------------------------------------------------------------------------------------*/
// This module contains a number of methods around strings. In particular, I am using a length-based approach for
// storing strings, rather than null-terminating them.
//
// Strings should be thought of as immutable for the most part. Their underlying data will typically be stored
// either on the heap in an arena, or as string literals. In general, methods taking an arena will allocate their
// result on that arena.
//
// To print these strings, there is a method to convert back to a null-terminated C-style strings.
//
// String builders are just linked lists containing a sequence of strings. This allows for more memory efficient
// construction of a string built from concatenating a lot of other strings. Doing this using concats would
// allocate the resulting string after each concatenation, so using a string builder should be preferred when the
// alternative would be numerous calls of concat/append.
/*---------------------------------------------------------------------------------------------------------------*/
#ifndef STRING_H
#define STRING_H

#include <stdarg.h>
#include <stdbool.h>

#include "compound_types.h"
#include "data.h"
#include "definitions.h"
#include "memory.h"

typedef struct String {
  U8 *str;
  U64 len;
} String;

typedef struct StringArray {
  String *data;
  U64 count;
} StringArray;

typedef struct StringNode {
  String data;
  LinkNode node;
} StringNode;

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

// Get the null-terminated equivalent of a string for printing
char *string_get_cstring(Arena *a, String str);

// Check whether two strings are equal
bool string_equals(String s1, String s2);
// Check whether two strings are equal up to differences in case
bool string_like(String s1, String s2);

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
// Get the index of the start of the first occurrence of a substring in a string
U64 string_find_first(String str, String substr);
// Get the indices of the start of all occurrence of a substring in a string
LinkNode *string_find_all(Arena *a, String str, String substr);

// Split a string into a linked list of tokens on a given delimeter
LinkNode *string_split(Arena *a, String str, String delimeter);

// Add a string to the end of a string builder
void string_builder_add_string(Arena *a, LinkNode *sb_head, String str);
// Remove the last string from a string builder
String string_builder_pop(LinkNode *sb_head);
// Flatten a string builder into a single string
String string_builder_get_string(Arena *a, const LinkNode *sb_head);

#endif  // STRING_H

// vim: filetype=c :
