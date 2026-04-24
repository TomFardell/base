#include "definitions.h"

#include <float.h>
#include <stdint.h>

const I8 I8MIN = INT8_MIN;
const I8 I8MAX = INT8_MAX;
const I16 I16MIN = INT16_MIN;
const I16 I16MAX = INT16_MAX;
const I32 I32MIN = INT32_MIN;
const I32 I32MAX = INT32_MAX;
const I64 I64MIN = INT64_MIN;
const I64 I64MAX = INT64_MAX;

const U8 U8MIN = 0;
const U8 U8MAX = UINT8_MAX;
const U16 U16MIN = 0;
const U16 U16MAX = UINT16_MAX;
const U32 U32MIN = 0;
const U32 U32MAX = UINT32_MAX;
const U64 U64MIN = 0;
const U64 U64MAX = UINT64_MAX;

// -- Consistent values to represent null/error cases when returning an integer. Hopefully these values are visible
// when debugging and don't collide with any real return values, but obviously this cannot be guaranteed, so be
// careful when using these --
const I32 I32NULL = 0x8DEFDEFD;
const I64 I64NULL = 0x8DEFDEFDEFDEFDEF;
const U32 U32NULL = 0xFDEFDEFD;
const U64 U64NULL = 0xFDEFDEFDEFDEFDEF;

const F32 F32MIN = FLT_MIN;
const F32 F32MAX = FLT_MAX;
const F32 F32EPS = FLT_EPSILON;
const F64 F64MIN = DBL_MIN;
const F64 F64MAX = DBL_MAX;
const F64 F64EPS = DBL_EPSILON;

const F32 PI32 = 3.141593f;
const F64 PI64 = 3.141592653589793;
