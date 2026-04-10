#ifndef DEFINITIONS_H
#define DEFINITIONS_H
#include <stdint.h>

typedef int8_t i8;
typedef int16_t i16;
typedef int32_t i32;
typedef int64_t i64;

typedef uint8_t u8;
typedef uint16_t u16;
typedef uint32_t u32;
typedef uint64_t u64;

typedef float f32;
typedef float f64;

#define min(x, y) (((x) < (y)) ? (x) : (y))
#define max(x, y) (((x) > (y)) ? (x) : (y))
#define clamp(low, x, high) (((x) < (low)) ? (low) : (((x) > (high)) ? (high) : (x)))
#define clamp_above(x, high) min(x, high)
#define clamp_below(x, low) max(x, low)

#endif  // ifndef DEFINITIONS_H

// vim: filetype=c :
