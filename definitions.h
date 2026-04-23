#ifndef DEFINITIONS_H
#define DEFINITIONS_H

#include <float.h>
#include <inttypes.h>
#include <stdint.h>
#include <string.h>

typedef int8_t I8;
typedef int16_t I16;
typedef int32_t I32;
typedef int64_t I64;

typedef uint8_t U8;
typedef uint16_t U16;
typedef uint32_t U32;
typedef uint64_t U64;

typedef float F32;
typedef double F64;

typedef struct U64Array {
  U64 *data;
  U64 count;
} U64Array;

#define I8MIN INT8_MIN
#define I8MAX INT8_MAX
#define I16MIN INT16_MIN
#define I16MAX INT16_MAX
#define I32MIN INT32_MIN
#define I32MAX INT32_MAX
#define I64MIN INT64_MIN
#define I64MAX INT64_MAX

#define U8MIN 0
#define U8MAX UINT8_MAX
#define U16MIN 0
#define U16MAX UINT16_MAX
#define U32MIN 0
#define U32MAX UINT32_MAX
#define U64MIN 0
#define U64MAX UINT64_MAX

// -- Consistent values to represent null/error cases when returning an integer. Hopefully these values are visible
// when debugging and don't collide with any real return values, but obviously this cannot be guaranteed, so be
// careful when using these --
#define I32NULL 0x8DEFDEFD
#define I64NULL 0x8DEFDEFDEFDEFDEF
#define U32NULL 0xFDEFDEFD
#define U64NULL 0xFDEFDEFDEFDEFDEF

#define F32MIN FLT_MIN
#define F32MAX FLT_MAX
#define F32EPS FLT_EPSILON
#define F64MIN DBL_MIN
#define F64MAX DBL_MAX
#define F64EPS DBL_EPSILON

#define PI32 3.141593
#define PI64 3.141592653589793

#define I8f PRIi8
#define I16f PRIi16
#define I32f PRIi32
#define I64f PRIi64

#define U8f PRIu8
#define U16f PRIu16
#define U32f PRIu32
#define U64f PRIu64

#define F32f "%f"
#define F64f "%lf"

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
