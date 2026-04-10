#ifndef STRING_H
#define STRING_H

#include "definitions.h"

typedef struct string {
  u8 *str;
  u64 length;
} string;

#endif  // STRING_H

// vim: filetype=c :
