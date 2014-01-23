#
# GNU Makefile for the hello_glut project
#
# Michael Shafae
# mshafae at fullerton.edu
#
# $Id: Makefile 4758 2014-01-23 07:42:39Z mshafae $
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


TARGET = hello_glfw
# C++ Files
CXXFILES =   hello_glfw.cpp
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
