/*-------*/
/* Stack */
/*---------------------------------------------------------------------------------------------------------------*/
// This module contains macros to define and declare stacks.
//
// A stack is a first-in-last-out data structure, storing the index of the next unused element and the capacity.
// The below implementation relies on macros to define the stack struct itself, as well as all of the methods,
// given a type name. The type name prefixes the struct name, e.g. I32Stack, and suffixes the method names, e.g.
// stack_pop_I32.
//
// There are two ways to define a stack and its methods. Firstly, we can use declare_stack in a header file, and
// define_stack in the corresponding implementation file. Alternatively, we could use just declare_stack_static in
// an implementation file if we require the stack and its methods to stay within a translation unit.
//
// There are some macros prefixed with underscores. These are not intended to be used outside this file.
/*---------------------------------------------------------------------------------------------------------------*/
#ifndef BASE_STACK_H
#define BASE_STACK_H

#include <stdarg.h>
#include <stdio.h>  // IWYU pragma: keep
#include <stdlib.h>

#include "definitions.h"
#include "memory.h"

/*----------------*/
/* Private macros */
/*---------------------------------------------------------------------------------------------------------------*/
#define _define_stack_type(type)                          \
  /* Stack with size and top */                           \
  typedef struct type##Stack {                            \
    type *data;   /* Underlying stack data */             \
    U64 top;      /* Index of the first unused element */ \
    U64 capacity; /* Maximum number of elements */        \
  } type##Stack

#define _declare_stack_methods(type)                                                          \
  /* Initialise a stack given pointer to a container and its capacity (number of elements) */ \
  type##Stack stack_init_##type(type *data, U64 capacity);                                    \
  /* Initialise a stack of a given capacity (number of elements) on the passed arena */       \
  type##Stack stack_init_arena_##type(Arena *a, U64 capacity);                                \
                                                                                              \
  /* Determine whether the given stack is at capacity */                                      \
  bool stack_is_full_##type(const type##Stack *stack);                                        \
  /* Determine whether the given stack is empty */                                            \
  bool stack_is_empty_##type(const type##Stack *stack);                                       \
                                                                                              \
  /* Remove and return the top element of a stack */                                          \
  type stack_pop_##type(type##Stack *stack);                                                  \
  /* Get the top element of a stack without removing it */                                    \
  type stack_peek_##type(const type##Stack *stack);                                           \
  /* Push a value to the top of the stack */                                                  \
  void stack_push_##type(type##Stack *stack, type value)

#define _define_stack_methods_with_attributes(type, attributes)                                          \
  /* Abort used in stack methods. Should not be used outside of these */                                 \
  [[noreturn]] static void _stack_abort##type(const char *file, int line, const char *func, ...) {       \
    va_list args;                                                                                        \
    va_start(args, func);                                                                                \
                                                                                                         \
    const char *message = va_arg(args, const char *);                                                    \
                                                                                                         \
    fprintf(stderr, "\n");                                                                               \
    fprintf(stderr, "> ---| Stack error |---\n");                                                        \
    fprintf(stderr, "> Error in %s->%s (line %d)\n", file, func, line);                                  \
    fprintf(stderr, "> ");                                                                               \
    vfprintf(stderr, message, args);                                                                     \
    fprintf(stderr, "\n");                                                                               \
    fprintf(stderr, "Terminating program\n");                                                            \
                                                                                                         \
    va_end(args);                                                                                        \
                                                                                                         \
    exit(EXIT_FAILURE);                                                                                  \
  }                                                                                                      \
                                                                                                         \
  /* Initialise a stack given pointer to a container and its capacity (number of elements) */            \
  attributes type##Stack stack_init_##type(type *data, U64 capacity) {                                   \
    return (type##Stack){data, 0, capacity};                                                             \
  }                                                                                                      \
                                                                                                         \
  /* Initialise a stack of a given capacity (number of elements) on the passed arena */                  \
  attributes type##Stack stack_init_arena_##type(Arena *a, U64 capacity) {                               \
    return stack_init_##type(arena_alloc_array(a, type, capacity), capacity);                            \
  }                                                                                                      \
                                                                                                         \
  /* Determine whether the given stack is at capacity */                                                 \
  attributes bool stack_is_full_##type(const type##Stack *stack) {                                       \
    return (stack->top == stack->capacity);                                                              \
  }                                                                                                      \
                                                                                                         \
  /* Determine whether the given stack is empty */                                                       \
  attributes bool stack_is_empty_##type(const type##Stack *stack) {                                      \
    return (stack->top == 0);                                                                            \
  }                                                                                                      \
                                                                                                         \
  /* Remove and return the top element of a stack */                                                     \
  attributes type stack_pop_##type(type##Stack *stack) {                                                 \
    if (stack_is_empty_##type(stack)) {                                                                  \
      _stack_abort##type(__FILE__, __LINE__, __func__,                                                   \
                         "Attempting to pop from empty stack (of capacity %" U64f ")", stack->capacity); \
    }                                                                                                    \
                                                                                                         \
    return stack->data[--stack->top];                                                                    \
  }                                                                                                      \
                                                                                                         \
  /* Get the top element of a stack without removing it */                                               \
  attributes type stack_peek_##type(const type##Stack *stack) {                                          \
    if (stack_is_empty_##type(stack)) {                                                                  \
      _stack_abort##type(__FILE__, __LINE__, __func__,                                                   \
                         "Attempting to peek at empty stack (of capacity %" U64f ")", stack->capacity);  \
    }                                                                                                    \
                                                                                                         \
    return stack->data[stack->top - 1];                                                                  \
  }                                                                                                      \
                                                                                                         \
  /* Push a value to the top of the stack */                                                             \
  attributes void stack_push_##type(type##Stack *stack, type value) {                                    \
    if (stack_is_full_##type(stack)) {                                                                   \
      _stack_abort##type(__FILE__, __LINE__, __func__,                                                   \
                         "Attempting to push to full stack (of capacity %" U64f ")", stack->capacity);   \
    }                                                                                                    \
    stack->data[stack->top++] = value;                                                                   \
  }                                                                                                      \
                                                                                                         \
  eat_semicolon()
/*---------------------------------------------------------------------------------------------------------------*/

/*------------------*/
/* External linkage */
/*---------------------------------------------------------------------------------------------------------------*/
#define declare_stack(type) \
  _define_stack_type(type); \
  _declare_stack_methods(type)

#define define_stack(type) _define_stack_methods_with_attributes(type, )
/*---------------------------------------------------------------------------------------------------------------*/

/*------------------*/
/* Internal linkage */
/*---------------------------------------------------------------------------------------------------------------*/
#define define_stack_static(type) \
  _define_stack_type(type);       \
  _define_stack_methods_with_attributes(type, [[maybe_unused]] static)
/*---------------------------------------------------------------------------------------------------------------*/

#endif  // BASE_STACK_H

// vim: filetype=c :
