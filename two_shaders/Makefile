#
# GNU Makefile for the two_shaders_glfw project
#
# Michael Shafae
# mshafae at fullerton.edu
#
# $Id: Makefile 5721 2015-04-15 22:19:46Z mshafae $
#
# It depends on the config.guess program that is in the config directory
# to guess what configuration to use for the build.
#

SHELL = /bin/sh
SYSTEM ?= $(shell config/config.guess | cut -d - -f 3 | sed -e 's/[0-9\.]//g;')
SYSTEM.SUPPORTED = $(shell test -f config/Makefile.$(SYSTEM) && echo 1)

CFLAGS += -DNOTEXTURE

ifeq ($(SYSTEM.SUPPORTED), 1)
include config/Makefile.$(SYSTEM)
else
$(error "Platform '$(SYSTEM)' not supported")
endif


TARGET = twoshaders
# C++ Files
CXXFILES =   two_shaders_glfw.cpp transformations.cpp glut_teapot.cpp
CFILES =  
# Headers
HEADERS =  GFXMath.h GLFWApp.h GLSLShader.h glut_teapot.h transformations.h

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
