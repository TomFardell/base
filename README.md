# Base layer

This is a C base layer for use in my other projects. Currently contains:
- Consistent number types
- Arena allocator
- Length-based strings
- Doubly linked lists
- Lots of helper functions, macros and other data structures

For more detailed information on what this code does, see the documentation in each header file, as well as comments around the methods.

## How to use

I am expecting to use this by including this repository as a submodule. I can then reference the included Makefile from my parent project's Makefile to build the archive library `libbase.a` and statically link this to my program.

