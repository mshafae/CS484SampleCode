
INCLUDES += -I/System/Library/Frameworks/OpenGL.framework/Versions/A/Headers/ -I/System/Library/Frameworks/GLUT.framework/Versions/A/Headers
LLDLIBS += -framework Appkit -framework GLUT -framework OpenGL
#
# Add or remove the -DNDEBUG to activate or deactivate your code
#
# ex. your code on:  CFLAGS += -g -DNDEBUG -Wall -pipe $(INCLUDES)
# or  your code off: CFLAGS += -g -Wall -pipe $(INCLUDES)
#
CFLAGS += -g -Wall -pipe -ansi $(INCLUDES)
LDFLAGS += -g -Wall -pipe

TARGET = psurfviewer.glsl
# C++ Files
CXXFILES = SurfaceGeometry.cpp getopt_long.cpp psurfviewer_main.cpp GLSLShader.cpp
# C Files
CFILES =
# Headers
HEADERS = SGFaceList.h SurfaceGeometry.h getopt.h GLSLShader.h

OBJECTS = $(CXXFILES:.cpp=.o) $(CFILES:.c=.o)

DEP = $(CXXFILES:.cpp=.d) $(CFILES:.c=.d)

default all: $(TARGET)

$(TARGET): $(OBJECTS)
	$(CXX) $(LDFLAGS) -o $(TARGET) $(OBJECTS) $(LLDLIBS)

-include $(DEP)

%.d: %.cpp
	set -e; $(CXX) -MM $(CFLAGS) $< \
	| sed 's/\($*\)\.o[ :]*/\1.o $@ : /g' > $@; \
	[ -s $@ ] || rm -f $@

%.d: %.c
	set -e; $(CXX) -MM $(CFLAGS) $< \
	| sed 's/\($*\)\.o[ :]*/\1.o $@ : /g' > $@; \
	[ -s $@ ] || rm -f $@

%.o: %.cpp
	$(CXX) $(CFLAGS) -c $<

%.o: %.c
	$(CXX) $(CFLAGS) -c $<

clean:
	-rm -f $(OBJECTS) core $(TARGET).core *~

spotless: clean
	-rm -f $(TARGET) $(DEP)

