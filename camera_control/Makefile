#
# GNU Makefile for the hello_glut project
#
# Michael Shafae
# mshafae at fullerton.edu
#
# $Id: Makefile 5618 2015-03-25 08:48:16Z mshafae $
#
# It depends on the config.guess program that is in the config directory
# to guess what configuration to use for the build.
#

SHELL = /bin/sh
SYSTEM ?= $(shell config/config.guess | cut -d - -f 3 | sed -e 's/[0-9\.]//g;')
SYSTEM.SUPPORTED = $(shell test -f config/Makefile.$(SYSTEM) && echo 1)

ifeq ($(SYSTEM.SUPPORTED), 1)
include config/Makefile.$(SYSTEM)
else
$(error "Platform '$(SYSTEM)' not supported")
endif


TARGET = camera_control
# C++ Files
CXXFILES =   camera_control_glfw.cpp glut_teapot.cpp transformations.cpp
CFILES =  
# Headers
HEADERS =  

OBJECTS = $(CXXFILES:.cpp=.o) $(CFILES:.c=.o)

DEP = $(CXXFILES:.cpp=.d) $(CFILES:.c=.d)

default all: $(TARGET)

$(TARGET): $(OBJECTS)
	$(CXX) $(LDFLAGS) -o $(TARGET) $(OBJECTS) $(LLDLIBS)

-include $(DEP)

%.d: %.cpp
	set -e; $(CXX) -MM $(CFLAGS) $< \
	| sed 's/($*).o[ :]*/.o $@ : /g' > $@; \
	[ -s $@ ] || rm -f $@

%.d: %.c
	set -e; $(CXX) -MM $(CFLAGS) $< \
	| sed 's/($*).o[ :]*/.o $@ : /g' > $@; \
	[ -s $@ ] || rm -f $@

%.o: %.cpp
	$(CXX) $(CFLAGS) -c $<

%.o: %.c
	$(CXX) $(CFLAGS) -c $<

clean:
	-rm -f $(OBJECTS) core $(TARGET).core *~

spotless: clean
	-rm -f $(TARGET) $(DEP)
