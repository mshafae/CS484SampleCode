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
#include "GLSLShader.h"

bool _myglError( FILE *out, const char *filename, int line ){
  bool ret = false;
  GLenum err = glGetError( );
  while( err != GL_NO_ERROR ) {
    ret = true;
    fprintf( out, "GL ERROR:%s:%d: %s\n", filename, line, (char*)gluErrorString( err ) );
      err = glGetError( );
  }
  return( ret );
}

char* file2strings( const char *filename ){
  long fileLength, numberOfCharsRead;
  char *strings;
  FILE *fhandle = fopen( filename, "r" );
  if( !fhandle ){
    fprintf( stderr, "%s: Can't open file %s for reading\n", __FUNCTION__, filename );
    return NULL;
  }
  fseek( fhandle, 0, SEEK_END );
  fileLength = ftell( fhandle );

  fseek( fhandle, 0, SEEK_SET );

  if( !(strings = (char*)calloc( (fileLength+1), sizeof(char) )) ){
    fprintf( stderr, "%s: Can't malloc space for string buffer %s\n", __FUNCTION__, filename );
    return NULL;
  }

  numberOfCharsRead = fread( strings, sizeof(char), fileLength, fhandle );

  strings[numberOfCharsRead] = '\0';

  fclose( fhandle );

  return( strings );
}

Shader::~Shader( ){
  glDeleteShader( _object );
  myglError( );
}

bool Shader::compileShader( const char *src ){
  GLint compiled_ok;
  char *msg;
  GLint length = (GLint)strlen(src);
  glShaderSource( _object, 1, &src, &length );
  glCompileShader( _object );
  myglError( );
  glGetShaderiv( _object, GL_COMPILE_STATUS, &compiled_ok );
  myglError( );
  if( !compiled_ok ){
    fprintf( stderr, "Compilation failed for vertex shader\n" );
    msg = getInfoLog( );
    fprintf( stderr, "Info Log:\n%s\n", msg );
    free( msg );
  }
  return( (bool)compiled_ok );
}
  
char* Shader::getInfoLog( ){
  GLint info_log_length;
  glGetShaderiv( _object, GL_INFO_LOG_LENGTH, &info_log_length );
  char *info_log = (char*)malloc( info_log_length );
  glGetShaderInfoLog( _object, info_log_length, NULL, info_log);
  return( info_log );
}

VertexShader::VertexShader( const char *srcFileName ){
  char *src;
  if( (src = file2strings( srcFileName )) != NULL ){
    if( (Shader::_object = glCreateShader( GL_VERTEX_SHADER )) == 0 ){
      fprintf( stderr, "Can't generate vertex shader name\n" );
    }
    myglError( );
    compileShader( src );
    myglError( );
    free( src );
  }else{
    fprintf( stderr, "There was a problem opening the vertex shader file. Exiting.\n");
    exit(1);
  }
}

GLuint VertexShader::object( ){
  return Shader::_object;
}

FragmentShader::FragmentShader( const char *srcFileName ){
  char *src;
  if( (src = file2strings( srcFileName )) != NULL ){
    if( (Shader::_object = glCreateShader( GL_FRAGMENT_SHADER )) == 0 ){
      fprintf( stderr, "Can't generate fragment shader name\n" );
      exit(1);
    }
    compileShader( src );
    free( src );
  }else{
    fprintf( stderr, "There was a problem opening the fragment shader file. Exiting.\n");
    exit(1);
      
  }
}

GLuint FragmentShader::object( ){
  return Shader::_object;
}



GLSLProgram::GLSLProgram( ){
  if( (_object = glCreateProgram( )) == 0 ){
    fprintf( stderr, "Can't generate program name\n" );
    exit(1);
  }
}

GLSLProgram::~GLSLProgram( ){
  detachAll( );
  glDeleteProgram( _object );
}

bool GLSLProgram::attach( FragmentShader &fs ){
  glAttachShader( _object, fs.object( ) );
  return( !myglError( ) );
}

bool GLSLProgram::attach( VertexShader &vs ){
  glAttachShader( _object, vs.object( ) );
  return( !myglError( ) );
}

bool GLSLProgram::detachAll( ){
  bool ret = false;
  GLsizei const maxCount = 32;
  GLsizei count;
  GLuint shaders[32];
  glGetAttachedShaders( _object, maxCount, &count, shaders );
  for(int i = 0; i < count; i++ ){
    if( !(detach( shaders[i] )) ){
      ret = true;
    }
  }
  return( ret );
}

bool GLSLProgram::detach( GLuint shaderName ){
  glDetachShader( _object, shaderName );
  return( !myglError( ) );
}

bool GLSLProgram::detach( FragmentShader &fs ){
  glDetachShader( _object, fs.object( ) );
  return( !myglError( ) );
}

bool GLSLProgram::detach( VertexShader &vs ){
  glDetachShader( _object, vs.object( ) );
  return( !myglError( ) );
}

bool GLSLProgram::link( ){
  GLint linked_ok;
  char *msg;
  bool ret = true;
  
  glLinkProgram( _object );

  glGetProgramiv( _object, GL_LINK_STATUS, &linked_ok );
  if( !linked_ok ){
    ret = false;
    fprintf( stderr, "Linking failed.\n" );
    msg = getInfoLog( );
    fprintf( stderr, "%s\n", msg );
    free(msg );
  }
  return ret;
}
  
char* GLSLProgram::getInfoLog( ){
  GLint info_log_length;
  glGetProgramiv( _object, GL_INFO_LOG_LENGTH, &info_log_length );
  char *info_log = (char*)malloc( info_log_length );
  glGetProgramInfoLog( _object, info_log_length, NULL, info_log);
  return( info_log );
}
  
bool GLSLProgram::activate( ){
  glUseProgram( _object );
  return( !myglError( ) );
}

bool GLSLProgram::deactivate( ){
  glUseProgram( (GLuint)NULL );
  return( !myglError( ) );
}

bool GLSLProgram::isHardwareAccelerated( ){
  bool ret = true;
#if defined(__APPLE__)
  /*
  * This checks to make sure that the shaders are going to
  * be hardware accelerated.
  * If they aren't, a message is printed.
  *
  * Something similar can be done on Unix as well as MS Windows but
  * it is left up to the student to look up the neccessary API calls.
  */
  GLint hardwareAccelerated;

  CGLGetParameter( CGLGetCurrentContext( ), kCGLCPGPUVertexProcessing, &hardwareAccelerated );
  if( !hardwareAccelerated ){
    ret = false;
    fprintf( stderr,
    "Warning: Vertex shader is NOT being hardware-accelerated\n" );
  }
  CGLGetParameter( CGLGetCurrentContext( ), kCGLCPGPUFragmentProcessing, &hardwareAccelerated );
  if( !hardwareAccelerated ){
    ret = false;
    fprintf( stderr,
    "Warning: Fragment shader is NOT being hardware-accelerated\n" );
  }
#endif
  return ret;
}
