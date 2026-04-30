/*----------------*/
/* Compound Types */
/*---------------------------------------------------------------------------------------------------------------*/
// This module contains the repetititve definitions of a bunch of useful structs, as outlined below.
//
// Array with pointer to first element and element count:
// +----------------------+
// | <Type>Array my_array |
// +----------------------+
// | <Type> *data         |
// | U64 count            |
// +----------------------+
//
// Node containing data and a link node:
// +--------------------+
// | <Type>Node my_node |
// +--------------------+
// | <Type> data        |
// | LinkNode node      |
// +--------------------+
//
// Vector containing (2-4) elements with (x,y,z,w) indexing:
// +-------------------+     +-------------------+     +-------------------+
// | <Type>Vec2 my_vec |     | <Type>Vec3 my_vec |     | <Type>Vec4 my_vec |
// +-------------------+     +-------------------+     +-------------------+
// | <Type> x          |     | <Type> x          |     | <Type> x          |
// | <Type> y          |     | <Type> y          |     | <Type> y          |
// +-------------------+     | <Type> z          |     | <Type> z          |
//                           +-------------------+     | <Type> w          |
//                                                     +-------------------+
//
/*---------------------------------------------------------------------------------------------------------------*/

#ifndef COMPOUND_TYPES_H
#define COMPOUND_TYPES_H

#include "data.h"
#include "definitions.h"

typedef struct I8Array {
  I8 *data;
  U64 count;
} I8Array;
typedef struct I16Array {
  I16 *data;
  U64 count;
} I16Array;
typedef struct I32Array {
  I32 *data;
  U64 count;
} I32Array;
typedef struct I64Array {
  I64 *data;
  U64 count;
} I64Array;

typedef struct U8Array {
  U8 *data;
  U64 count;
} U8Array;
typedef struct U16Array {
  U16 *data;
  U64 count;
} U16Array;
typedef struct U32Array {
  U32 *data;
  U64 count;
} U32Array;
typedef struct U64Array {
  U64 *data;
  U64 count;
} U64Array;

typedef struct F32Array {
  F32 *data;
  U64 count;
} F32Array;
typedef struct F64Array {
  F64 *data;
  U64 count;
} F64Array;

typedef struct I8Node {
  I8 data;
  LinkNode node;
} I8Node;
typedef struct I16Node {
  I16 data;
  LinkNode node;
} I16Node;
typedef struct I32Node {
  I32 data;
  LinkNode node;
} I32Node;
typedef struct I64Node {
  I64 data;
  LinkNode node;
} I64Node;

typedef struct U8Node {
  U8 data;
  LinkNode node;
} U8Node;
typedef struct U16Node {
  U16 data;
  LinkNode node;
} U16Node;
typedef struct U32Node {
  U32 data;
  LinkNode node;
} U32Node;
typedef struct U64Node {
  U64 data;
  LinkNode node;
} U64Node;

typedef struct F32Node {
  F32 data;
  LinkNode node;
} F32Node;
typedef struct F64Node {
  F64 data;
  LinkNode node;
} F64Node;

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

#endif  // COMPOUND_TYPES_H

// vim: filetype=c :
