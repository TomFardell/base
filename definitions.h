#ifndef DEFINITIONS_H
#define DEFINITIONS_H

#include <inttypes.h>

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

const extern I8 I8MIN;
const extern I8 I8MAX;
const extern I16 I16MIN;
const extern I16 I16MAX;
const extern I32 I32MIN;
const extern I32 I32MAX;
const extern I64 I64MIN;
const extern I64 I64MAX;

const extern U8 U8MIN;
const extern U8 U8MAX;
const extern U16 U16MIN;
const extern U16 U16MAX;
const extern U32 U32MIN;
const extern U32 U32MAX;
const extern U64 U64MIN;
const extern U64 U64MAX;

const extern I32 I32NULL;
const extern I64 I64NULL;
const extern U32 U32NULL;
const extern U64 U64NULL;

const extern F32 F32MIN;
const extern F32 F32MAX;
const extern F32 F32EPS;
const extern F64 F64MIN;
const extern F64 F64MAX;
const extern F64 F64EPS;

const extern F32 PI32;
const extern F64 PI64;

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
