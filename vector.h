#ifndef VECTOR_H
#define VECTOR_H

#include "definitions.h"

typedef struct I32Vec2 {
  I32 x;
  I32 y;
} I32Vec2;

typedef struct I32Vec3 {
  I32 x;
  I32 y;
  I32 z;
} I32Vec3;

typedef struct I32Vec4 {
  I32 x;
  I32 y;
  I32 z;
  I32 w;
} I32Vec4;

typedef struct I64Vec2 {
  I64 x;
  I64 y;
} I64Vec2;

typedef struct I64Vec3 {
  I64 x;
  I64 y;
  I64 z;
} I64Vec3;

typedef struct I64Vec4 {
  I64 x;
  I64 y;
  I64 z;
  I64 w;
} I64Vec4;

typedef struct U32Vec2 {
  U32 x;
  U32 y;
} U32Vec2;

typedef struct U32Vec3 {
  U32 x;
  U32 y;
  U32 z;
} U32Vec3;

typedef struct U32Vec4 {
  U32 x;
  U32 y;
  U32 z;
  U32 w;
} U32Vec4;

typedef struct U64Vec2 {
  U64 x;
  U64 y;
} U64Vec2;

typedef struct U64Vec3 {
  U64 x;
  U64 y;
  U64 z;
} U64Vec3;

typedef struct U64Vec4 {
  U64 x;
  U64 y;
  U64 z;
  U64 w;
} U64Vec4;

typedef struct F32Vec2 {
  F32 x;
  F32 y;
} F32Vec2;

typedef struct F32Vec3 {
  F32 x;
  F32 y;
  F32 z;
} F32Vec3;

typedef struct F32Vec4 {
  F32 x;
  F32 y;
  F32 z;
  F32 w;
} F32Vec4;

typedef struct F64Vec2 {
  F64 x;
  F64 y;
} F64Vec2;

typedef struct F64Vec3 {
  F64 x;
  F64 y;
  F64 z;
} F64Vec3;

typedef struct F64Vec4 {
  F64 x;
  F64 y;
  F64 z;
  F64 w;
} F64Vec4;

#endif  // VECTOR_H

// vim: filetype=c :
