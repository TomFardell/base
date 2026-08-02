/*----------------*/
/* Compound Types */
/*---------------------------------------------------------------------------------------------------------------*/
// This module contains the repetititve definitions of a bunch of useful structs, as outlined below. These structs
// are defined using macros. See definitions.h and data.h for the definitions of the define_array and define_node
// macros respectively.
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
// Vector containing (2-4) elements with (x,y,z,w) indexing, or numbered indexing (using union magic):
// +-------------------+     +-------------------+     +-------------------+
// | <Type>Vec2 my_vec |     | <Type>Vec3 my_vec |     | <Type>Vec4 my_vec |
// +-------------------+     +-------------------+     +-------------------+
// | <Type> x          |     | <Type> x          |     | <Type> x          |
// | <Type> y          |     | <Type> y          |     | <Type> y          |
// | OR                |     | <Type> z          |     | <Type> z          |
// | <Type> data[2]    |     | OR                |     | <Type> w          |
// +-------------------+     | <Type> data[3]    |     | OR                |
//                           +-------------------+     | <Type> data[4]    |
//                                                     +-------------------+
//
/*---------------------------------------------------------------------------------------------------------------*/

#ifndef COMPOUND_TYPES_H
#define COMPOUND_TYPES_H

#include "data.h"
#include "definitions.h"

#define define_vec2(type)     \
  typedef struct type##Vec2 { \
    union {                   \
      struct {                \
        type x;               \
        type y;               \
      };                      \
      type data[2];           \
    };                        \
  } type##Vec2

#define define_vec3(type)     \
  typedef struct type##Vec3 { \
    union {                   \
      struct {                \
        type x;               \
        type y;               \
        type z;               \
      };                      \
      type data[3];           \
    };                        \
  } type##Vec3

#define define_vec4(type)     \
  typedef struct type##Vec4 { \
    union {                   \
      struct {                \
        type x;               \
        type y;               \
        type z;               \
        type w;               \
      };                      \
      type data[4];           \
    };                        \
  } type##Vec4

define_array(I8);
define_array(I16);
define_array(I32);
define_array(I64);
define_array(U8);
define_array(U16);
define_array(U32);
define_array(U64);
define_array(F32);
define_array(F64);

define_node(I8);
define_node(I16);
define_node(I32);
define_node(I64);
define_node(U8);
define_node(U16);
define_node(U32);
define_node(U64);
define_node(F32);
define_node(F64);

define_vec2(I8);
define_vec2(I16);
define_vec2(I32);
define_vec2(I64);
define_vec2(U8);
define_vec2(U16);
define_vec2(U32);
define_vec2(U64);
define_vec2(F32);
define_vec2(F64);

define_vec3(I8);
define_vec3(I16);
define_vec3(I32);
define_vec3(I64);
define_vec3(U8);
define_vec3(U16);
define_vec3(U32);
define_vec3(U64);
define_vec3(F32);
define_vec3(F64);

define_vec4(I8);
define_vec4(I16);
define_vec4(I32);
define_vec4(I64);
define_vec4(U8);
define_vec4(U16);
define_vec4(U32);
define_vec4(U64);
define_vec4(F32);
define_vec4(F64);

#endif  // COMPOUND_TYPES_H

// vim: filetype=c :
