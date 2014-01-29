// 
// Michael Shafae
// mshafae at fullerton.edu
// 
// A really simple GLUT demo that renders an animated and
// colored tetrahedron which the edges outlined in black.
//
// $Id: hello_glut.cpp 4782 2014-01-29 07:47:59Z mshafae $
//

#include <cstdlib>
#include <cstdio>
#include <sys/time.h>

#include <GL/glew.h>

#ifdef __APPLE__
#include <GLUT/glut.h>
#else
#include <GL/glut.h>
#endif

#ifdef FREEGLUT
#include <GL/freeglut_ext.h>
#endif


#define msglError( ) _msglError( stderr, __FILE__, __LINE__ )

bool _msglError( FILE *out, const char *filename, int line ){
  bool ret = false;
  GLenum err = glGetError( );
  while( err != GL_NO_ERROR ) {
    ret = true;
    fprintf( out, "GL ERROR:%s:%d: %s\n",
      filename, line, (char*)gluErrorString( err ) );
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
  default:
    fprintf( stderr, "You pushed '%c' (%d).\n", key, key );
    break;
  }
}

void reshapeCallback( int width, int height ){
  if (height == 0){
		height = 1;
	}
	glViewport( 0, 0, (GLsizei)width, (GLsizei)height );
  double ratio = double(width) / double(height);
	glMatrixMode( GL_PROJECTION );
	glLoadIdentity( );
  glFrustum(-ratio, ratio, -ratio, ratio, 1.0f, 40.0f);
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

#ifdef WIN32
#include <windows.h>
double winGetElapsedTime( ){
  LARGE_INTEGER frequency;
  LARGE_INTEGER now;
  static char firstTime = 1;
  static double resolution;
  static double start;
  if( firstTime ){
    // initialize
    QueryPerformanceFrequency(frequency);
    resolution = 1.0 / double(frequency);
    QueryPerformanceCounter(&start);
  }
  QueryPerformanceCounter(&now);
  return double(now - start) * resolution;
}
#else
double posixGetElapsedTime( ){
  static struct timeval start;
  static int firstTime = 1;
  struct timeval now;
  struct timeval elapsed;
  if( firstTime ){
    firstTime = 0;
    gettimeofday(&start, NULL);
  }
  gettimeofday(&now, NULL);
  elapsed.tv_sec = now.tv_sec - start.tv_sec;
  elapsed.tv_usec = now.tv_usec - start.tv_usec;
  if (elapsed.tv_usec < 0){
    elapsed.tv_sec--;
    elapsed.tv_usec += 1000000;
  }
  double n = ((uint64_t) elapsed.tv_sec * (uint64_t) 1000000 + (uint64_t) elapsed.tv_usec) / 1000000.0;
  return n;
}
#endif

double getElapsedTime( ){
#ifdef WIN32
  return winGetElapsedTime( );
#else
  return posixGetElapsedTime( );
#endif  
}


void displayCallback( ){
  glClear( GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT );
  glMatrixMode(GL_MODELVIEW);
  glLoadIdentity( );
  gluLookAt(0.0f, 0.0f, -2.5f, 0.0f, 0.0f, 0.0f, 0.0f, 1.0f, 0.0f);

  glRotatef(float(getElapsedTime( )) * 50.0f, 0.0f, 0.0f, 1.0f);
  glRotatef(float(getElapsedTime( )) * 30.0f, 0.0f, 1.0f, 0.0f);
  glRotatef(float(getElapsedTime( )) * 15.0f, 1.0f, 0.0f, 0.0f);

  drawTetrahedron( );
  
  glutSwapBuffers( );
}

void updateCallback( int x ){
  glutPostRedisplay( );
  glutTimerFunc( 16, updateCallback, 0 );
}

int main( int argc, char* argv[] ){
  glutInit( &argc, argv );
  glutInitDisplayMode( GLUT_RGBA | GLUT_DOUBLE | GLUT_DEPTH );
  glutInitWindowSize( 500, 500);
  glutCreateWindow( "Hello GLUT and OpenGL" );
  glewExperimental = true;
  if( glewInit( ) != GLEW_OK ){
    fprintf(stderr, "GLEW init failed.\n");
    exit(1);
  }
  glClearColor( 0.0f, 0.0f, 0.0f, 1.0f );
  glEnable( GL_DEPTH_TEST );
  glDepthFunc(GL_LESS);
  glutKeyboardFunc( keyboardCallback );
  glutDisplayFunc( displayCallback );
  glutReshapeFunc( reshapeCallback );
  glutTimerFunc( 16, updateCallback, 0 );
  msglVersion( );
  glutMainLoop( );
  return(0);
}
