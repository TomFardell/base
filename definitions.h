/*-------------*/
/* Definitions */
/*---------------------------------------------------------------------------------------------------------------*/
// This module contains a number of simple types and macros, as well as some useful contants.
/*---------------------------------------------------------------------------------------------------------------*/
#ifndef DEFINITIONS_H
#define DEFINITIONS_H

#include <float.h>
#include <inttypes.h>
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
typedef double F64;

static constexpr I8 I8MIN = INT8_MIN;
static constexpr I8 I8MAX = INT8_MAX;
static constexpr I16 I16MIN = INT16_MIN;
static constexpr I16 I16MAX = INT16_MAX;
static constexpr I32 I32MIN = INT32_MIN;
static constexpr I32 I32MAX = INT32_MAX;
static constexpr I64 I64MIN = INT64_MIN;
static constexpr I64 I64MAX = INT64_MAX;

static constexpr U8 U8MIN = 0;
static constexpr U8 U8MAX = UINT8_MAX;
static constexpr U16 U16MIN = 0;
static constexpr U16 U16MAX = UINT16_MAX;
static constexpr U32 U32MIN = 0;
static constexpr U32 U32MAX = UINT32_MAX;
static constexpr U64 U64MIN = 0;
static constexpr U64 U64MAX = UINT64_MAX;

// Consistent values to represent null/error cases when returning an integer. Hopefully these values are visible
// when debugging and don't collide with any real return values, but obviously this cannot be guaranteed, so be
// careful when using these
static constexpr I32 I32NULL = 0x7DEFDEFD;
static constexpr I64 I64NULL = 0x7DEFDEFDEFDEFDEF;
static constexpr U32 U32NULL = 0xFDEFDEFD;
static constexpr U64 U64NULL = 0xFDEFDEFDEFDEFDEF;

static constexpr F32 F32MIN = FLT_MIN;
static constexpr F32 F32MAX = FLT_MAX;
static constexpr F32 F32EPS = FLT_EPSILON;
static constexpr F64 F64MIN = DBL_MIN;
static constexpr F64 F64MAX = DBL_MAX;
static constexpr F64 F64EPS = DBL_EPSILON;

static constexpr F32 PI32 = 3.1415927f;
static constexpr F64 PI64 = 3.141592653589793;
static constexpr F32 E32 = 2.718282f;
static constexpr F64 E64 = 2.718281828459045;

#define I8f PRIi8
#define I16f PRIi16
#define I32f PRIi32
#define I64f PRIi64

#define U8f PRIu8
#define U16f PRIu16
#define U32f PRIu32
#define U64f PRIu64

#define F32f "f"
#define F64f "lf"

#define statement(s) \
  do {               \
    s;               \
  } while (0)

#define array_len(array) (sizeof(array) / sizeof(*array))

#define define_array(type)     \
  typedef struct type##Array { \
    type *data;                \
    U64 count;                 \
  } type##Array

#define KB(n) ((1 << 10) * (n))
#define MB(n) ((1 << 20) * (n))
#define GB(n) ((1 << 30) * (n))

#define min(x, y) (((x) < (y)) ? (x) : (y))
#define max(x, y) (((x) > (y)) ? (x) : (y))
#define clamp(low, x, high) (((x) < (low)) ? (low) : (((x) > (high)) ? (high) : (x)))
#define clamp_above(x, high) min(x, high)
#define clamp_below(x, low) max(x, low)

#define norm(x) (((x) > 0) ? (x) : (0 - (x)))
#define norm_dist(x, y) norm((x) - (y))

#define mod(x, y) (((x) % (y)) >= 0 ? ((x) % (y)) : ((y) + ((x) % (y))))

#define F32_eq(x, y) (norm_dist(x, y) < F32EPS)
#define F32_lt(x, y) ((x) < (y))
#define F32_leq(x, y) (F32_lt(x, y) || F32_eq(x, y))
#define F32_gt(x, y) ((x) > (y))
#define F32_geq(x, y) (F32_gt(x, y) || F32_eq(x, y))
#define F32_neq(x, y) (!F32_eq(x, y))

#define F64_eq(x, y) (norm_dist(x, y) < F64EPS)
#define F64_lt(x, y) ((x) < (y))
#define F64_leq(x, y) (F64_lt(x, y) || F64_eq(x, y))
#define F64_gt(x, y) ((x) > (y))
#define F64_geq(x, y) (F64_gt(x, y) || F64_eq(x, y))
#define F64_neq(x, y) (!F64_eq(x, y))

#endif  // DEFINITIONS_H

// vim: filetype=c :
