GFXMath README

Michael Shafae
mshafae at fullerton.edu

1/25/2015

Summary

This is project is an exercise for the student to practice writing a small math library for use in CS 484. It is currently only partially complete but it a state that students can begin to work on it.

One file, GFXMath.h, defines a few handy utilities (read the source) and the classes that define random numbers, vectors, and matrices. This file will serve each of you as a header-only library for all of our math needs in this course and in future graphics and games courses.

The other file GFXMath_Test.cpp is a unit test of GFXMath.h. Currently, GFXMath.h has been crippled and regions have been marked with "// Fill me in!". Those regions need code in order to operate correctly and pass the unit test.

A student can have a high degree of confidence that the code is correct if the code passes a unit test.

Building

To compile the program, run `make' on OS X and Linux or `gmake' on FreeBSD. The Makefile is compatible with GNU Make and not BSD Make. The list of make targets are:
 . all         build all (default)
 . clean       remove intermediate files, core files, backup files
 . spotless    clean + remove all dependency files

The build depends on the PThreads library and the Google Test library. Pthreads is typically included with your development environment and the Google Test libraries are included in the Titan OpenGL Kit.

**TLA VM Users: Release 20150119 is missing the Google Test libraries but
includes the header files and source code. TLA VM release 20150125 has the library correctly installed.**
