// 
// Michael Shafae
// mshafae at fullerton.edu
// 
// A really simple GLUT demo that renders an animated and
// colored tetrahedron which the edges outlined in black.
//
// $Id: camera_control_glut.cpp 4915 2014-04-10 07:05:10Z mshafae $
//

#include <cstdlib>
#include <cstdio>
//#include <sys/time.h>

#ifdef _WIN32
#include <Windows.h>
#pragma warning(disable : 4305)
#endif

#include <GL/glew.h>

#ifdef __APPLE__
#include <GLUT/glut.h>
#else
#include <GL/glut.h>
#endif

#ifdef FREEGLUT
#include <GL/freeglut_ext.h>
#endif

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

// When true, use glLookAt. When false, use user defined lookAt.
bool useGLLookAt;

GLSLProgram *shaderProgram;

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

float light0[4];
float light1[4]; 

// Variables to set uniform params for lighting fragment shader 
unsigned int uIsLightOn; 
unsigned int uLight0_position;
unsigned int uLight0_color;
unsigned int uLight1_position;
unsigned int uLight1_color;
unsigned int uAmbient;
unsigned int uDiffuse;
unsigned int uSpecular;
unsigned int uShininess;

void msglVersion(void){
  fprintf(stderr, "OpenGL Version Information:\n");
  fprintf(stderr, "\tVendor: %s\n", glGetString(GL_VENDOR));
  fprintf(stderr, "\tRenderer: %s\n", glGetString(GL_RENDERER));
  fprintf(stderr, "\tOpenGL Version: %s\n", glGetString(GL_VERSION));
  fprintf(stderr, "\tGLSL Version: %s\n",
          glGetString(GL_SHADING_LANGUAGE_VERSION));
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

void initUseGLLookAt( ){
  useGLLookAt = true;
}

void init() {
  initEyePosition( );
  initUpVector( );
  initRotationDelta( );
  initUseGLLookAt( );

  // Load the shader program
  const char* vertexShaderSource = "blinn_phong.vert.glsl";
  const char* fragmentShaderSource = "blinn_phong.frag.glsl";
  FragmentShader fragmentShader(fragmentShaderSource);
  VertexShader vertexShader(vertexShaderSource);
  shaderProgram = new GLSLProgram( );
  shaderProgram->attach(vertexShader);
  shaderProgram->attach(fragmentShader);
  shaderProgram->link( );
  shaderProgram->activate( );
  printf("Shader program built from %s and %s.\n",
         vertexShaderSource, fragmentShaderSource);
  if( shaderProgram->isActive( ) ){
    printf("Shader program is loaded and active with id %d.\n",
           shaderProgram->id( ) );
  }else{
    printf("Shader program did not load and activate correctly. Exiting.");
    exit(1);
  }

  // Set up uniform variables
  uIsLightOn = glGetUniformLocation(shaderProgram->id( ),
                                    "isLightOn");
  uLight0_position = glGetUniformLocation(shaderProgram->id( ),
                                          "light0_position");
  uLight0_color = glGetUniformLocation(shaderProgram->id( ),
                                       "light0_color");
  uLight1_position = glGetUniformLocation(shaderProgram->id( ),
                                          "light1_position");
  uLight1_color = glGetUniformLocation(shaderProgram->id( ),
                                       "light1_color");
  uAmbient = glGetUniformLocation(shaderProgram->id( ), "ambient");
  uDiffuse = glGetUniformLocation(shaderProgram->id( ), "diffuse");
  uSpecular = glGetUniformLocation(shaderProgram->id( ), "specular");
  uShininess = glGetUniformLocation(shaderProgram->id( ), "shininess");
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

void keyboardCallback( unsigned char key, int x, int y ){
  switch( key ){
    case 27: // The 'esc' key
    case 'q':
#ifdef FREEGLUT
      glutLeaveMainLoop( );
#else
      exit( 0 );
#endif
      break;
    case '+':
      rotationDelta += 1.0;
      printf( "Rotation delta set to %g\n", rotationDelta );
      break;
    case '-':
      rotationDelta -= 1.0;
      printf( "Rotation delta set to %g\n", rotationDelta );
      break;
    case 'g':
      useGLLookAt = !useGLLookAt;
      printf("Using OpenGL's gluLookAt? %s\n", (useGLLookAt ? "Yes" : "No"));
      break;
    case 'h':
      printHelpMessage( );
      break;
    case 'r':
      initEyePosition( );
      initUpVector( );
      initRotationDelta( );
      printf("Eye position, up vector and rotation delta reset.\n");
      break;
    default:
      fprintf( stderr, "You pushed '%c' (%d).\n", key, key );
      break;
  }
  glutPostRedisplay( );
}

void specialCallback( int key,int x,int y ){
  float centerPosition[] = {0.0, 0.0, 0.0};
  switch( key ){
    case GLUT_KEY_LEFT:
      rotateCameraLeft(rotationDelta, eyePosition,
                       centerPosition, upVector);
      break;
    case GLUT_KEY_RIGHT:
      rotateCameraLeft(-rotationDelta, eyePosition,
                       centerPosition, upVector);
      break;
    case GLUT_KEY_UP:
      rotateCameraUp(rotationDelta, eyePosition,
                     centerPosition, upVector);
      break;
    case GLUT_KEY_DOWN:
      rotateCameraUp(-rotationDelta, eyePosition,
                     centerPosition, upVector);
      break;
  }
  glutPostRedisplay( );
}

void reshapeCallback( int width, int height ){
  if (height == 0){
    height = 1;
  }
  glViewport( 0, 0, (GLsizei)width, (GLsizei)height );
  double ratio = double(width) / double(height);
  glMatrixMode( GL_PROJECTION );
  glLoadIdentity( );
  gluPerspective(90.0, ratio, 1.0, 25.0); 
}

void displayCallback( ){
  const float centerPosition[] = {0.0, 0.0, 0.0};
  // Your transformation is stored in myModelView.
  // You my change it's type if you so desire.
  float myModelView[16];

  glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

  glMatrixMode(GL_MODELVIEW);
  glLoadIdentity( );

  if( useGLLookAt ){
    // see `man gluLookAt( )` or 
    // <http://www.opengl.org/sdk/docs/man2/xhtml/gluLookAt.xml>
    // or browse <http://www.opengl.org/sdk/docs/man2/>
    gluLookAt(
      eyePosition[0], eyePosition[1], eyePosition[2],
      centerPosition[0], centerPosition[1], centerPosition[2],
      upVector[0], upVector[1], upVector[2]
    );
  }else{
    //mv = Transform::lookAt(eye,up);
    myLookAt(myModelView,
      eyePosition[0], eyePosition[1], eyePosition[2],
      centerPosition[0], centerPosition[1], centerPosition[2],
      upVector[0], upVector[1], upVector[2]
    );
    glMultMatrixf(myModelView); 
  }

  // Set light & material properties for the teapot;
  // lights are transformed by current modelview matrix
  // such that they are positioned correctly in the scene.
  transformVecByModelView(light0, light0_position); 
  transformVecByModelView(light1, light1_position); 

  glUniform4fv(uLight0_position, 1, light0); 
  glUniform4fv(uLight0_color, 1, light0_specular); 
  glUniform4fv(uLight1_position, 1, light1); 
  glUniform4fv(uLight1_color, 1, light1_specular); 

  glUniform4fv(uAmbient, 1, littleBit); 
  glUniform4fv(uDiffuse, 1, medium); 
  glUniform4fv(uSpecular, 1, one); 
  glUniform1fv(uShininess, 1, high); 
  glUniform1i(uIsLightOn, true);

  _glutSolidTeapot(2);
  glutSwapBuffers();
}

int main( int argc, char* argv[] ){
  // Init. GLUT
  glutInit( &argc, argv );
  glutInitDisplayMode( GLUT_RGBA | GLUT_DOUBLE | GLUT_DEPTH );
  glutInitWindowSize( 500, 500);
  glutCreateWindow( "Camera Control" );
  
  // Init. GLEW
  glewExperimental = true;
  if( glewInit( ) != GLEW_OK ){
    fprintf(stderr, "GLEW init failed.\n");
    exit(1);
  }
  
  // Set OpenGL State
  glClearColor( 0.0f, 0.0f, 0.0f, 1.0f );
  glEnable( GL_DEPTH_TEST );
  glDepthFunc(GL_LESS);

  // Application specific initialization
  init( );

  // Register callbacks with GLUT
  glutKeyboardFunc( keyboardCallback );
  glutSpecialFunc( specialCallback );
  glutDisplayFunc( displayCallback );
  glutReshapeFunc( reshapeCallback );
  
  msglVersion( );
  
  puts("Press 'h' to see a help message at any time.");
  
  glutMainLoop( );
  return(0);
}
