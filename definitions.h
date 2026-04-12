#ifndef DEFINITIONS_H
#define DEFINITIONS_H
#include <stdint.h>

typedef int8_t I8;
typedef int16_t I16;
typedef int32_t I32;
typedef int64_t I64;

typedef uint8_t U8;
typedef uint16_t U16;
typedef uint32_t U32;
typedef uint64_t U64;

typedef float F32;
typedef float F64;

#define KB(n) ((1 << 10) * (n))
#define MB(n) ((1 << 20) * (n))
#define GB(n) ((1 << 30) * (n))

#define min(x, y) (((x) < (y)) ? (x) : (y))
#define max(x, y) (((x) > (y)) ? (x) : (y))
#define clamp(low, x, high) (((x) < (low)) ? (low) : (((x) > (high)) ? (high) : (x)))
#define clamp_above(x, high) min(x, high)
#define clamp_below(x, low) max(x, low)

#endif  // ifndef DEFINITIONS_H

// vim: filetype=c :
