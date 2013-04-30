/*
 * Copyright (c) 2005-2008 Michael Shafae.
 * All rights reserved.
 *
 * This program is distributed in the hope that it will be useful, but
 * WITHOUT ANY WARRANTY, to the extent permitted by law; without even the
 * implied warranty of MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.
 *
 * $Id: GLSLShader.h 3372 2012-01-10 21:30:21Z mshafae $
 *
 * Utility functions for loading a shader
 *
 */

#ifdef __APPLE__
/* Apple's weird location of their OpenGL & GLUT implementation */
#include <OpenGL/OpenGL.h>
#include <OpenGL/gl.h>
#include <OpenGL/glu.h>
#else
#include <GL/glew.h>
#include <GL/gl.h>
#include <GL/glu.h>
#endif

#include <cstdio>
#include <cstdlib>
#include <cstring>
#include <cassert>
#include <vector>

#define myglError( ) _myglError( stderr, __FILE__, __LINE__ )

bool _myglError( FILE *out, const char *filename, int line );

char* file2strings( const char *filename );


class Shader{
public:
  GLuint _object;
  
  Shader( ){ };

  ~Shader( );

  bool compileShader( const char *src );
  
  char* getInfoLog( );
};

class VertexShader : public Shader{

public:
  VertexShader( const char *srcFileName );

  GLuint object( );

};


class FragmentShader : public Shader{

public:
  FragmentShader( const char *srcFileName );

    GLuint object( );
};


class GLSLProgram{

public:
  GLuint _object;

  GLSLProgram( );

  ~GLSLProgram( );
  
  bool attach( FragmentShader &fs );

  bool attach( VertexShader &vs );

  bool detachAll( );

  bool detach( GLuint shaderName );

  bool detach( FragmentShader &fs );

  bool detach( VertexShader &vs );

  bool link( );
  
  char* getInfoLog( );
  
  bool activate( );

  bool deactivate( );
  
  bool isHardwareAccelerated( );
};