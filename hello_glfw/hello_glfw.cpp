// 
// Michael Shafae
// mshafae at fullerton.edu
// 
// A really simple GLFW3 demo that renders an animated and
// colored tetrahedron which the edges outlined in black.
//
// $Id: hello_glfw.cpp 4758 2014-01-23 07:42:39Z mshafae $
//

#include <cstdlib>
#include <cstdio>
#include <cassert>

#include <GL/glew.h>
#define GLFW_INCLUDE_GLU
#include <GLFW/glfw3.h>

#define msglError( ) _msglError( stderr, __FILE__, __LINE__ )

bool _msglError( FILE *out, const char *filename, int line ){
  bool ret = false;
  GLenum err = glGetError( );
  while( err != GL_NO_ERROR ) {
    ret = true;
    fprintf( out, "GL ERROR:%s:%d: %s\n", filename, line, (char*)gluErrorString( err ) );
      err = glGetError( );
  }
  return( ret );
}

void msglVersion(void){  
  fprintf(stderr, "Vendor: %s\n", glGetString(GL_VENDOR));
  fprintf(stderr, "Renderer: %s\n", glGetString(GL_RENDERER));
  fprintf(stderr, "OpenGL Version: %s\n", glGetString(GL_VERSION));
  fprintf(stderr, "GLSL Version: %s\n", glGetString(GL_SHADING_LANGUAGE_VERSION));
}

static void errorCallback(int error, const char* description){
  fprintf(stderr, "GLFW Error: %s\n", description);
}

static void keyCallback(GLFWwindow* window, int key, int scancode, int action, int mods){
  if( action == GLFW_PRESS ){
    switch( key ){
      case GLFW_KEY_ESCAPE:
        glfwSetWindowShouldClose(window, GL_TRUE);
      break;
      default:
        fprintf(stderr, "Key pressed: %c:%d\n", key, key);
      break;
    }
  }
}

void drawTriangle(void){
  glBegin(GL_TRIANGLES);
  glColor3f(1.0f, 0.0f, 0.0f);
  glVertex3f(-0.6f, -0.4f, 0.0f);
  glColor3f(0.0f, 1.0f, 0.0f);
  glVertex3f(0.6f, -0.4f, 0.0f);
  glColor3f(0.0f, 0.0f, 1.0f);
  glVertex3f(0.0f, 0.6f, 0.0f);
  glEnd( );
}

void drawTetrahedron(void){
  glBegin(GL_TRIANGLE_STRIP);
  glColor3f(1.0f, 1.0f, 1.0f);
  glVertex3f(0.0f, 1.0f, 0.0f); // a
  glColor3f(1.0f, 0.0f, 0.0f);
  glVertex3f(-1.0f, 0.0f, 1.0f); // b
  glColor3f(0.0f, 1.0f, 0.0f);
  glVertex3f(1.0f, 0.0f, 1.0f); // c
  glColor3f(0.0f, 0.0f, 1.0f);
  glVertex3f(0.0f, 0.0f, -1.0f); // d
  glColor3f(1.0f, 1.0f, 1.0f);
  glVertex3f(0.0f, 1.0f, 0.0f); // a
  glColor3f(1.0f, 0.0f, 0.0f);
  glVertex3f(-1.0f, 0.0f, 1.0f); // b
  glEnd();
  
  glBegin(GL_LINES);
  glColor3f(0.0f, 0.0f, 0.0f);
  
  //a b
  glVertex3f(0.0f, 1.0f, 0.0f);
  glVertex3f(-1.0f, 0.0f, 1.0f);
  //a c
  glVertex3f(0.0f, 1.0f, 0.0f);
  glVertex3f(1.0f, 0.0f, 1.0f);

  //b c
  glVertex3f(-1.0f, 0.0f, 1.0f);
  glVertex3f(1.0f, 0.0f, 1.0f);

  //a d
  glVertex3f(0.0f, 1.0f, 0.0f);
  glVertex3f(0.0f, 0.0f, -1.0f);
  //b d
  glVertex3f(-1.0f, 0.0f, 1.0f);
  glVertex3f(0.0f, 0.0f, -1.0f);
  //c d
  glVertex3f(1.0f, 0.0f, 1.0f);
  glVertex3f(0.0f, 0.0f, -1.0f);
  
  glEnd( );
}

int main(void){
  GLFWwindow* window;
  glfwSetErrorCallback(errorCallback);
  if( !glfwInit( ) ){
    exit(1);
  }

  glfwWindowHint(GLFW_RESIZABLE, GL_FALSE);
  //glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
  //glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 2);
  //glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
  //glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);
  //glfwWindowHint(GLFW_OPENGL_DEBUG_CONTEXT, GL_TRUE);
  window = glfwCreateWindow(500, 500, "Hello OpenGL and GLFW", 0, NULL);
  if( !window ){
    glfwTerminate( );
    exit(1);
  }
  glfwMakeContextCurrent(window);
  
  glewExperimental = true;
  GLenum err = glewInit( );
  if( err != GLEW_OK ){
    fprintf(stderr, "GLEW: init failed: %s\n", glewGetErrorString(err));
    exit(1);
  }
    
  glfwSetKeyCallback(window, keyCallback);

  glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
  glEnable(GL_DEPTH_TEST);
  glDepthFunc(GL_LESS);

  msglVersion( );

  while( !glfwWindowShouldClose(window) ){
    float ratio;
    int width, height;
    glfwGetFramebufferSize(window, &width, &height);
    ratio = width / float(height);
    glViewport(0, 0, width, height);

    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    glMatrixMode(GL_PROJECTION);
    glLoadIdentity( );
    glFrustum(-ratio, ratio, -ratio, ratio, 1.0f, 40.0f);
  
    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity( );
    gluLookAt(0.0f, 0.0f, -2.5f, 0.0f, 0.0f, 0.0f, 0.0f, 1.0f, 0.0f);
    glRotatef(float(glfwGetTime( )) * 50.0f, 0.0f, 0.0f, 1.0f);
    glRotatef(float(glfwGetTime( )) * 30.0f, 0.0f, 1.0f, 0.0f);
    glRotatef(float(glfwGetTime( )) * 15.0f, 1.0f, 0.0f, 0.0f);
  
    drawTetrahedron( );
  
    glfwSwapBuffers(window);
    glfwPollEvents( );
  }
  
  glfwDestroyWindow(window);
  glfwTerminate( );
  return 0;
}
