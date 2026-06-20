#include "string.h"

#include <stdalign.h>
#include <stdarg.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <stdnoreturn.h>
#include <string.h>

#include "compound_types.h"
#include "data.h"
#include "definitions.h"
#include "memory.h"

// Takes same args as printf
#define string_abort(...) statement(_string_abort(__FILE__, __LINE__, __func__, __VA_ARGS__))

static noreturn void _string_abort(const char *file, int line, const char *func, ...) {
  va_list args;
  va_start(args, func);

  const char *message = va_arg(args, const char *);

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

String string_init(const char *str, U64 len) {
  return (String){str, len};
}

String string_init_range(const char *start, const char *end) {
  return string_init(start, end - start);
}

String string_init_cstring(const char *cstr) {
  return string_init(cstr, strlen(cstr));
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

char *string_get_cstring(Arena *a, String str) {
  char *cstr = arena_alloc_array(a, char, str.len + 1);
  memcpy(cstr, str.str, str.len);
  cstr[str.len] = '\0';

  return cstr;
}

bool string_equals(String s1, String s2) {
  if (s1.len != s2.len) {
    return false;
  }

  return mem_equals(s1.str, s2.str, s1.len);
}

bool string_like(String s1, String s2) {
  if (s1.len != s2.len) {
    return false;
  }

  Arena a = arena_init((s1.len + s2.len) * sizeof(*s1.str));

  String s1_low = string_lower(&a, s1);
  String s2_low = string_lower(&a, s2);

  bool result = mem_equals(s1_low.str, s2_low.str, s1_low.len);

  arena_free(&a);

  return result;
}

String string_copy(Arena *a, String str) {
  char *result_str = arena_alloc_array(a, char, str.len);
  memcpy(result_str, str.str, str.len);

  return string_init(result_str, str.len);
}

String string_append(Arena *a, String str, String suffix) {
  char *result_str = arena_alloc_array(a, char, str.len + suffix.len);

  memcpy(result_str, str.str, str.len);
  memcpy(result_str + str.len, suffix.str, suffix.len);

  return string_init(result_str, str.len + suffix.len);
}

String string_prepend(Arena *a, String str, String prefix) {
  return string_append(a, prefix, str);
}

String string_concat(Arena *a, U64 count, ...) {
  va_list args;
  va_start(args, count);

  Arena strings_arena = arena_init(count * sizeof(String));
  String *strings = arena_alloc_array(&strings_arena, String, count);

  for (U64 i = 0; i < count; ++i) {
    strings[i] = va_arg(args, String);
  }

  va_end(args);

  String result = string_concat_arr(a, (StringArray){strings, count});

  arena_free(&strings_arena);

  return result;
}

String string_concat_arr(Arena *a, StringArray str_arr) {
  U64 result_len = 0;

  for (U64 i = 0; i < str_arr.count; ++i) {
    result_len += str_arr.data[i].len;
  }

  char *result_str = arena_alloc_array(a, char, result_len);

  for (U64 i = 0, pos = 0; i < str_arr.count; pos += str_arr.data[i].len, ++i) {
    memcpy(result_str + pos, str_arr.data[i].str, str_arr.data[i].len);
  }

  return string_init(result_str, result_len);
}

String string_join(Arena *a, String delimeter, U64 count, ...) {
  va_list args;
  va_start(args, count);

  Arena strings_arena = arena_init(count * sizeof(String));
  String *strings = arena_alloc_array(&strings_arena, String, count);

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

  U64 result_len = delimeter.len * (str_arr.count - 1);

  for (U64 i = 0; i < str_arr.count; ++i) {
    result_len += str_arr.data[i].len;
  }

  char *result_str = arena_alloc_array(a, char, result_len);

  U64 pos = 0;
  for (U64 i = 0; i < str_arr.count - 1; ++i) {
    memcpy(result_str + pos, str_arr.data[i].str, str_arr.data[i].len);
    pos += str_arr.data[i].len;

    memcpy(result_str + pos, delimeter.str, delimeter.len);
    pos += delimeter.len;
  }

  memcpy(result_str + pos, str_arr.data[str_arr.count - 1].str, str_arr.data[str_arr.count - 1].len);

  return string_init(result_str, result_len);
}

String string_upper(Arena *a, String str) {
  char *result_str = arena_alloc_array(a, char, str.len);

  for (U64 i = 0; i < str.len; ++i) {
    result_str[i] = str.str[i];

    if ('a' <= result_str[i] && result_str[i] <= 'z') {
      result_str[i] += 'A' - 'a';
    }
  }

  return string_init(result_str, str.len);
}

String string_lower(Arena *a, String str) {
  char *result_str = arena_alloc_array(a, char, str.len);

  for (U64 i = 0; i < str.len; ++i) {
    result_str[i] = str.str[i];

    if ('A' <= str.str[i] && str.str[i] <= 'Z') {
      result_str[i] = str.str[i] + 'a' - 'A';
    }
  }

  return string_init(result_str, str.len);
}

String string_reverse(Arena *a, String str) {
  char *result_str = arena_alloc_array(a, char, str.len);

  for (U64 i = 0; i < str.len; ++i) {
    result_str[i] = str.str[str.len - i - 1];
  }

  return string_init(result_str, str.len);
}

String string_format(Arena *a, const char *format, ...) {
  va_list args;
  va_start(args, format);

  // First determine the buffer size required before allocating anything
  U64 result_len = vsnprintf(NULL, 0, format, args);

  va_start(args, format);  // Need to call this again in order to reuse the args

  char *result_str = arena_alloc_array(a, char, result_len + 1);  // Allocate an extra byte for the null terminator
  vsnprintf(result_str, result_len + 1, format, args);

  va_end(args);

  return string_init(result_str, result_len);
}

String string_remove(Arena *a, String str, String rem) {
  if ((rem.len > str.len) || (rem.len == 0)) {
    return str;
  }
  char *result_str = arena_alloc_array(a, char, str.len);  // Max length would be if nothing is removed

  U64 str_i = 0, res_i = 0;
  while (str_i < str.len) {
    if ((str_i + rem.len - 1 < str.len) && mem_equals(str.str + str_i, rem.str, rem.len)) {
      str_i += rem.len;
      continue;
    }

    result_str[res_i] = str.str[str_i];
    ++str_i;
    ++res_i;
  }

  return string_init(result_str, res_i);
}

bool string_contains(String str, String substr) {
  return (string_find_first(str, substr) != U64NULL);
}

U64 string_find_first(String str, String substr) {
  if ((substr.len == 0) || (str.len < substr.len)) {
    return U64NULL;
  }

  for (U64 i = 0; i < str.len - substr.len + 1; ++i) {
    if (string_equals(string_init(str.str + i, substr.len), string_init(substr.str, substr.len))) {
      return i;
    }
  }

  return U64NULL;
}

LinkNode *string_find_all(Arena *a, String str, String substr) {
  LinkNode *head = arena_alloc_single(a, LinkNode);
  linked_list_init(head);

  // When we find a substring, don't skip past it. I.e. ababa contains two overlapping instances of aba
  for (U64 i = 0; i < str.len; ++i) {
    U64 next_index = string_find_first(string_init(str.str + i, str.len - i), substr);
    if (next_index == U64NULL) {
      break;
    }

    i += next_index;

    U64Node *node = arena_alloc_single(a, U64Node);
    node->data = i;

    linked_list_push_back(head, &(node->node));
  }

  return head;
}

LinkNode *string_split(Arena *a, String str, String delimeter) {
  LinkNode *head = arena_alloc_single(a, LinkNode);
  linked_list_init(head);

  if (delimeter.len == 0) {
    StringNode *node = arena_alloc_single(a, StringNode);
    node->data = string_copy(a, str);

    linked_list_push_back(head, &(node->node));

    return head;
  }

  for (U64 i = 0, curr_str_len = 0; i <= str.len; ++i) {
    if ((i == str.len) || string_equals(string_init(str.str + i, delimeter.len), delimeter)) {
      if (curr_str_len > 0) {
        StringNode *node = arena_alloc_single(a, StringNode);
        node->data = string_init_substring(str, i - curr_str_len, i);

        linked_list_push_back(head, &(node->node));
      }

      curr_str_len = 0;
      i += delimeter.len - 1;

      continue;
    }

    ++curr_str_len;
  }

  return head;
}

void string_builder_add_string(Arena *a, LinkNode *sb_head, String str) {
  StringNode *string_node = arena_alloc_single(a, StringNode);
  string_node->data = str;
  linked_list_push_back(sb_head, &(string_node->node));
}

String string_builder_pop(LinkNode *sb_head) {
  StringNode *last_string_node = linked_list_get_container_node_at_index(sb_head, -1, StringNode, node);
  linked_list_remove_at_index(sb_head, -1);
  return last_string_node->data;
}

String string_builder_get_string(Arena *a, const LinkNode *sb_head) {
  return string_init_cstring(string_builder_get_cstring(a, sb_head));
}

char *string_builder_get_cstring(Arena *a, const LinkNode *sb_head) {
  U64 result_len = 0;

  for (LinkNode *curr = sb_head->next; curr != sb_head; curr = curr->next) {
    result_len += link_node_get_container_node(curr, StringNode, node)->data.len;
  }

  char *result_str = arena_alloc_array(a, char, result_len + 1);

  U64 pos = 0;
  for (LinkNode *curr = sb_head->next; curr != sb_head; curr = curr->next) {
    String curr_string = link_node_get_container_node(curr, StringNode, node)->data;
    memcpy(result_str + pos, curr_string.str, curr_string.len);

    pos += curr_string.len;
  }

  result_str[result_len] = '\0';

  return result_str;
}
