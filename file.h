/*------*/
/* File */
/*---------------------------------------------------------------------------------------------------------------*/
// This module contains simplified methods for reading and writing to files. All methods handle opening/closing of
// any files, and error if anything unexpected happens (such as being unable to open the file, or an error when
// reading/writing).
/*---------------------------------------------------------------------------------------------------------------*/
#ifndef FILE_H
#define FILE_H

#include "linked_list.h"
#include "memory.h"
#include "string.h"

// Create a file at the given path, erroring if the file already exists
void file_create(const char *path);

// Get the length of a given file (not including a null-terminator)
U64 file_get_length(const char *path);
// Read a file into a string, storing the result on the given arena
String file_read(Arena *a, const char *path);
// Read a file into a linked list of lines
LinkNode *file_read_lines(Arena *a, const char *path);

// Append a string to a file with a newline
void file_write(const char *path, String text);
// Append a string to a file without a newline
void file_write_raw(const char *path, String text);
// Append a linked list of strings to a file, all ending with a newline
void file_write_lines(const char *path, LinkNode *lines);

// Clear a file and write a string with a newline
void file_overwrite(const char *path, String text);
// Clear a file and write a string without a newline
void file_overwrite_raw(const char *path, String text);
// Clear a file and write a linked list of strings, all ending with a newline
void file_overwrite_lines(const char *path, const LinkNode *lines);

// Delete the file at the given path
void file_delete(const char *path);

#endif  // FILE_H

// vim: filetype=c :
