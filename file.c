#include "file.h"

#include <stdarg.h>
#include <stdio.h>
#include <stdlib.h>

#include "definitions.h"
#include "memory.h"
#include "string.h"

// Takes same args as printf
#define file_abort(...) statement(_file_abort(__FILE__, __LINE__, __func__, __VA_ARGS__))

[[noreturn]] static void _file_abort(const char *file, int line, const char *func, ...) {
  va_list args;
  va_start(args, func);

  const char *message = va_arg(args, const char *);

  fprintf(stderr, "\n");
  fprintf(stderr, "> ---| File error |---\n");
  fprintf(stderr, "> Error in %s->%s (line %d)\n", file, func, line);
  fprintf(stderr, "> ");
  vfprintf(stderr, message, args);
  fprintf(stderr, "\n");
  fprintf(stderr, "Terminating program\n");

  va_end(args);

  exit(EXIT_FAILURE);
}

void file_create(const char *path) {
  FILE *fp = fopen(path, "wx");
  if (fp == nullptr) {
    file_abort("Unable to create file '%s'", path);
  }

  fclose(fp);
}

U64 file_get_length(const char *path) {
  FILE *fp = fopen(path, "r");
  if (fp == nullptr) {
    file_abort("Unable to open file '%s'", path);
  }

  fseek(fp, 0, SEEK_END);
  U64 result = ftell(fp);
  fclose(fp);

  return result;
}

String file_read(Arena *a, const char *path) {
  U64 file_length = file_get_length(path);
  char *result_str = arena_alloc_array(a, char, file_length);

  FILE *fp = fopen(path, "r");
  if (fp == nullptr) {
    file_abort("Unable to open file '%s'", path);
  }

  U64 bytes_read = fread(result_str, sizeof(char), file_length, fp);
  fclose(fp);

  if (bytes_read != file_length) {
    file_abort("Error reading file '%s' (read %" U64f "/%" U64f " bytes)", path, bytes_read, file_length);
  }

  return (String){result_str, file_length};
}

LinkNode *file_read_lines(Arena *a, const char *path) {
  return string_split(a, file_read(a, path), string_literal("\n"));
}

static void file_write_with_mode(const char *path, String text, const char *mode) {
  FILE *fp = fopen(path, mode);
  if (fp == nullptr) {
    file_abort("Unable to open file '%s'", path);
  }

  U64 bytes_written = fwrite(text.str, sizeof(*text.str), text.len, fp);
  bytes_written += fwrite("\n", 1, 1, fp);
  fclose(fp);

  if (bytes_written != text.len + 1) {
    file_abort("Error writing to file '%s'", path);
  }
}

static void file_write_raw_with_mode(const char *path, String text, const char *mode) {
  FILE *fp = fopen(path, mode);
  if (fp == nullptr) {
    file_abort("Unable to open file '%s'", path);
  }

  U64 bytes_written = fwrite(text.str, sizeof(*text.str), text.len, fp);
  fclose(fp);

  if (bytes_written != text.len) {
    file_abort("Error writing to file '%s'", path);
  }
}

static void file_write_lines_with_mode(const char *path, const LinkNode *lines, const char *mode) {
  FILE *fp = fopen(path, mode);
  if (fp == nullptr) {
    file_abort("Unable to open file '%s'", path);
  }

  foreach (line_node, lines) {
    String line = link_node_get_data(line_node, String);

    U64 bytes_written = fwrite(line.str, sizeof(*line.str), line.len, fp);
    bytes_written += fwrite("\n", 1, 1, fp);

    if (bytes_written != line.len + 1) {
      fclose(fp);
      file_abort("Error writing to file '%s'", path);
    }
  }

  fclose(fp);
}

void file_write(const char *path, String text) {
  file_write_with_mode(path, text, "a");
}

void file_write_raw(const char *path, String text) {
  file_write_raw_with_mode(path, text, "a");
}
void file_write_lines(const char *path, LinkNode *lines) {
  file_write_lines_with_mode(path, lines, "a");
}

void file_overwrite(const char *path, String text) {
  file_write_with_mode(path, text, "w");
}

void file_overwrite_raw(const char *path, String text) {
  file_write_raw_with_mode(path, text, "w");
}

void file_overwrite_lines(const char *path, const LinkNode *lines) {
  file_write_lines_with_mode(path, lines, "w");
}

void file_delete(const char *path) {
  if (remove(path)) {
    file_abort("Unable to remove file '%s'", path);
  }
}
