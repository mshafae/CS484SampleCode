hello_glut README

Michael Shafae
mshafae at fullerton.edu

$Id: README.txt 4758 2014-01-23 07:42:39Z mshafae $

Summary

`hello_glfw' is a demonstration program that renders a colored tetrahedron that rotates around the X, Y, and Z axis to make it appear as though it is wobbling. It is drawn twice. First it is drawn as a colored triangle strip and then drawn as a collection of black lines.

Building

To compile the program, run `make' on OS X or `gmake' on FreeBSD. The Makefile is compatible with GNU Make and not BSD Make. The list of make targets are:
 . all         build all (default)
 . clean       remove intermediate files, core files, backup files
 . spotless    clean + remove all dependency files

It has been tested to build on
 . FreeBSD 9.2 64 bit with GCC 4.2.1
 . OS X 10.8.5 with Xcode 5.0.2 (like LLVM 3.3)

To configure the build, edit config/Makefile.*. Ensure that the variable OPENGL_KIT_HOME has the correct root path to where the header files and libraries can be found for the project's dependencies listed below.

The project requires has the following dependencies:
 . GLFW3 (glfw)
 . OpenGL (GL)
 . OpenGL Utility (GLU)
 . OpenGL Extension Wrangler Library (GLEW)

Execution

To run the program, run `hello_glfw'. It does not require any command line options.

The program has the following user interface:
 . esc: quit
It does not respond to any other keyboard or mouse events.
