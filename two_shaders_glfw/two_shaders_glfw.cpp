// 
// Michael Shafae
// mshafae at fullerton.edu
// 
// A really simple GLFW demo that renders an two teapots
// with two different shader programs.
//
// $Id: two_shaders_glfw.cpp 4930 2014-04-16 21:04:19Z mshafae $
//

#include <cstdlib>
#include <cstdio>

#ifdef _WIN32
#include <Windows.h>
#pragma warning(disable : 4305)
#endif

#include <GL/glew.h>

#define GLFW_INCLUDE_GLU
#include <GLFW/glfw3.h>

#include "GLSLShader.h"
#include "transformations.h"
#include "glut_teapot.h"

/***
 * Global variables
 */
// Rotation delta in degrees
float rotationDelta;

float eyePosition[3];
float upVector[3];

GLSLProgram *shaderProgram_A;
GLSLProgram *shaderProgram_B;

// For the Blinn-Phong shader
float light0_position[] = {0,5,10,1};
float light1_position[] = {0,5,-10,1};
const float light0_specular[] = {0.6,0.3,0,1};
const float light1_specular[] = {0,0.3,0.6,1};
// specular on teapot
const float one[] = {1,1,1,1};
// diffuse on teapot
const float medium[] = {0.5,0.5,0.5,1};
// ambient on teapot
const float littleBit[] = {0.2,0.2,0.2,1};
// shininess of teapot
const float high[] = {100};

// For the other shader
float light2_position[] = {0,5,10,1};

float light0[4];
float light1[4];
float light2[4]; 

// Variables to set uniform params for lighting fragment shader 
// For the Blinn-Phong shader
unsigned int uIsLightOn; 
unsigned int uLight0_position;
unsigned int uLight0_color;
unsigned int uLight1_position;
unsigned int uLight1_color;
unsigned int uAmbient;
unsigned int uDiffuse;
unsigned int uSpecular;
unsigned int uShininess;
// For Gouraud shader
unsigned int uLight2_position;


void msglVersion(void){
  fprintf(stderr, "OpenGL Version Information:\n");
  fprintf(stderr, "\tVendor: %s\n", glGetString(GL_VENDOR));
  fprintf(stderr, "\tRenderer: %s\n", glGetString(GL_RENDERER));
  fprintf(stderr, "\tOpenGL Version: %s\n", glGetString(GL_VERSION));
  fprintf(stderr, "\tGLSL Version: %s\n",
          glGetString(GL_SHADING_LANGUAGE_VERSION));
}

static void errorCallback(int error, const char* description){
  fprintf(stderr, "GLFW Error: %s\n", description);
}

void printHelpMessage() {
  puts("Press 'h' to print this message again.");
  puts("Press '+' or '-' to increase/decrease the amount of rotation that occurs with each arrow press.");
  puts("Press 'g' to toggle between using glLookAt( ) or your own Look At.");
  puts("Press 'r' to reset the camera's transformation.");
  puts("Press ESC or 'q' to quit.");
}

void initEyePosition( ){
  eyePosition[0] = 0.0;
  eyePosition[1] = 0.0;
  eyePosition[2] = 5.0;  
}

void initUpVector( ){
  upVector[0] = 0.0;
  upVector[1] = 1.0;
  upVector[2] = 0.0;  
}

void initRotationDelta( ){
  rotationDelta = 5.0;
}

void initUniforms_A( ){
  uIsLightOn = glGetUniformLocation(shaderProgram_A->id( ),
                                    "isLightOn");
  uLight0_position = glGetUniformLocation(shaderProgram_A->id( ),
                                          "light0_position");
  uLight0_color = glGetUniformLocation(shaderProgram_A->id( ),
                                       "light0_color");
  uLight1_position = glGetUniformLocation(shaderProgram_A->id( ),
                                          "light1_position");
  uLight1_color = glGetUniformLocation(shaderProgram_A->id( ),
                                       "light1_color");
  uAmbient = glGetUniformLocation(shaderProgram_A->id( ), "ambient");
  uDiffuse = glGetUniformLocation(shaderProgram_A->id( ), "diffuse");
  uSpecular = glGetUniformLocation(shaderProgram_A->id( ), "specular");
  uShininess = glGetUniformLocation(shaderProgram_A->id( ), "shininess");
}

void activateUniforms_A( ){
  glUniform4fv(uLight0_position, 1, light0); 
  glUniform4fv(uLight0_color, 1, light0_specular); 
  glUniform4fv(uLight1_position, 1, light1); 
  glUniform4fv(uLight1_color, 1, light1_specular); 
  glUniform4fv(uAmbient, 1, littleBit); 
  glUniform4fv(uDiffuse, 1, medium); 
  glUniform4fv(uSpecular, 1, one); 
  glUniform1fv(uShininess, 1, high); 
  glUniform1i(uIsLightOn, true);
}

void initUniforms_B( ){
  uLight2_position = glGetUniformLocation(shaderProgram_B->id( ),
                                          "light2_position");
}

void activateUniforms_B( ){
  glUniform4fv(uLight2_position, 1, light2);
}

void init() {
  initEyePosition( );
  initUpVector( );
  initRotationDelta( );
  
  // Load the shader program
  // Blinn-Phong
  const char* vertexShaderSource_A = "blinn_phong.vert.glsl";
  const char* fragmentShaderSource_A = "blinn_phong.frag.glsl";
  FragmentShader fragmentShader_A(fragmentShaderSource_A);
  VertexShader vertexShader_A(vertexShaderSource_A);
  shaderProgram_A = new GLSLProgram( );
  shaderProgram_A->attach(vertexShader_A);
  shaderProgram_A->attach(fragmentShader_A);
  shaderProgram_A->link( );
  shaderProgram_A->activate( );
  printf("Shader program A built from %s and %s.\n",
         vertexShaderSource_A, fragmentShaderSource_A);
  shaderProgram_A->deactivate( );
  // Gouraud Shader
  const char* vertexShaderSource_B = "gouraud.vert";
  const char* fragmentShaderSource_B = "gouraud.frag";
  FragmentShader fragmentShader_B(fragmentShaderSource_B);
  VertexShader vertexShader_B(vertexShaderSource_B);
  shaderProgram_B = new GLSLProgram( );
  shaderProgram_B->attach(vertexShader_B);
  shaderProgram_B->attach(fragmentShader_B);
  shaderProgram_B->link( );
  shaderProgram_B->activate( );
  printf("Shader program B built from %s and %s.\n",
         vertexShaderSource_B, fragmentShaderSource_B);
  shaderProgram_B->deactivate( );

  // Set up uniform variables
  // For the Blinn-Phong shader
  initUniforms_A( );
  // For the Gouraud shader
  initUniforms_B( );
}

void vecCopy4f(float *dest, float *src){
  int i;
  for(i = 0; i < 4; i++){
    dest[i] = src[i];
  }
}

void matMultVec4f(float* vout, float* v, float* m){
  float c[4];
  vecCopy4f(c, v);
  vout[0] = m[0] * c[0] + m[4] * c[1] + m[8]  * c[2] + m[12] * c[3];
  vout[1] = m[1] * c[0] + m[5] * c[1] + m[9]  * c[2] + m[13] * c[3];
  vout[2] = m[2] * c[0] + m[6] * c[1] + m[10] * c[2] + m[14] * c[3];
  vout[3] = m[3] * c[0] + m[7] * c[1] + m[11] * c[2] + m[15] * c[3];
}

void transformVecByModelView(float outVec[4], float inVec[4]){
  float modelview[16];
  glGetFloatv( GL_MODELVIEW_MATRIX, modelview );
  matMultVec4f( outVec, inVec, modelview );
}

static void keyboardCallback(GLFWwindow* window, int key, int scancode,
int action, int mods){
  float centerPosition[] = {0.0, 0.0, 0.0};
  if( action == GLFW_PRESS || action == GLFW_REPEAT ){
    switch( key ){
      case GLFW_KEY_ESCAPE:
      case GLFW_KEY_Q:
        glfwSetWindowShouldClose(window, GL_TRUE);
        break;
      case GLFW_KEY_EQUAL:
        // In GLFW you have to catch the shift key's state XXX
        rotationDelta += 1.0;
        printf( "Rotation delta set to %g\n", rotationDelta );
        break;
      case GLFW_KEY_MINUS:
        rotationDelta -= 1.0;
        printf( "Rotation delta set to %g\n", rotationDelta );
        break;
      case GLFW_KEY_H:
        printHelpMessage( );
        break;
      case GLFW_KEY_R:
        initEyePosition( );
        initUpVector( );
        initRotationDelta( );
        printf("Eye position, up vector and rotation delta reset.\n");
      break;
      case GLFW_KEY_LEFT:
        rotateCameraLeft(-rotationDelta, eyePosition,
                         centerPosition, upVector);
        break;
      case GLFW_KEY_RIGHT:
        rotateCameraLeft(rotationDelta, eyePosition,
                         centerPosition, upVector);
        break;
      case GLFW_KEY_UP:
        rotateCameraUp(-rotationDelta, eyePosition,
                       centerPosition, upVector);
        break;
      case GLFW_KEY_DOWN:
        rotateCameraUp(rotationDelta, eyePosition,
                       centerPosition, upVector);
        break;
      default:
        fprintf( stderr, "You pushed '%c' (%d).\n", key, key );
        break;
    }
  }
}

void reshapeCallback( GLFWwindow* window, int width, int height ){
  if (height == 0){
    height = 1;
  }
  glViewport( 0, 0, (GLsizei)width, (GLsizei)height );
  double ratio = double(width) / double(height);
  glMatrixMode( GL_PROJECTION );
  glLoadIdentity( );
  gluPerspective(90.0, ratio, 1.0, 25.0); 
}

void display( ){
  const float centerPosition[] = {0.0, 0.0, 0.0};

  glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

  glMatrixMode(GL_MODELVIEW);
  glLoadIdentity( );

  gluLookAt(
    eyePosition[0], eyePosition[1], eyePosition[2],
    centerPosition[0], centerPosition[1], centerPosition[2],
    upVector[0], upVector[1], upVector[2]
  );

  // Set light & material properties for the teapot;
  // lights are transformed by current modelview matrix
  // such that they are positioned correctly in the scene.
  transformVecByModelView(light0, light0_position); 
  transformVecByModelView(light1, light1_position); 
  transformVecByModelView(light2, light2_position); 

  shaderProgram_A->activate( );
  activateUniforms_A( );
    
  glPushMatrix( );
  glTranslatef(2.0, 0.0, 0.0);
  _glutSolidTeapot(1.3);
  glPopMatrix( );
  
  shaderProgram_B->activate( );
  activateUniforms_B( );
    
  glPushMatrix( );
  glTranslatef(-2.0, 0.0, 0.0);
  _glutSolidTeapot(1.3);  
  glPopMatrix( );
}

int main( int argc, char* argv[] ){
  GLFWwindow* window;
  int width, height;
  glfwSetErrorCallback(errorCallback);
  if( !glfwInit( ) ){
    exit(1);
  }

  glfwWindowHint(GLFW_RESIZABLE, GL_FALSE);
  //glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);
  //glfwWindowHint(GLFW_OPENGL_DEBUG_CONTEXT, GL_TRUE);
  glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 2);
  glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 1);
  window = glfwCreateWindow(500, 500, "Two Shaders", 0, NULL);
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
  
  // Register callbacks with GLFW
  glfwSetKeyCallback(window, keyboardCallback);
  glfwSetFramebufferSizeCallback(window, reshapeCallback);
  
  // Set OpenGL State
  glfwSwapInterval( 1 );
  glfwGetFramebufferSize(window, &width, &height);
  reshapeCallback(window, width, height);
  glClearColor( 0.0f, 0.0f, 0.0f, 1.0f );
  glEnable( GL_DEPTH_TEST );
  glDepthFunc( GL_LESS );

  // Application specific initialization
  init( );
	msglError( );
  
  msglVersion( );
  
  puts("Press 'h' to see a help message at any time.");
  
  while( !glfwWindowShouldClose(window) ){

    display( );
    
    glfwSwapBuffers(window);
    glfwPollEvents( );
  }
  
  glfwDestroyWindow(window);
  glfwTerminate( );
  return(0);
}
