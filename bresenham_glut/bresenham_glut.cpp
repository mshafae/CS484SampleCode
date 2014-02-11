/* 
 * Your Name Here
 * somebody at something dot TLD
 * CS 484
 *
 * This is a very trivial interactive program that used OpenGL
 * to simulate "large pixels", depicted by a regular grid of circles,
 * and allows the user to interactively pick start and end points
 * for drawing lines by clicking the left mouse button.  The task of
 * rasterizing a line is carried out by the function RasterizeLine.
 * A crude working version of this function is supplied; it operates
 * by rounding floating point coordinates that lie along the actual line.
 *
 * Your job is to rewrite RasterizeLine so that it uses Bresenham's
 * algorithm, as done on the previous assignment.  Your re-written
 * version should use no floating point arithmetic at all.  You may
 * find that  Bresenham's algorithm occasionally selects slightly
 * different pixels than the crude algorithm that is supplied. This 
 * is O.K.
 *
 * $Id: bresenham_glut.cpp 4828 2014-02-11 10:35:54Z mshafae $
 *
 */

#include <cstdlib>
#include <cstdio>
#include <cmath>
#include <cstring>

#include <GL/glew.h>

#ifdef __APPLE__
#include <GLUT/glut.h>
#else
#include <GL/glut.h>
#endif

#ifdef FREEGLUT
#include <GL/freeglut_ext.h>
#endif

#ifndef MIN
#define MIN( x, y ) ((x) <= (y) ? (x) :  (y))
#endif
#ifndef MAX
#define MAX( x, y ) ((x) >= (y) ? (x) :  (y))
#endif
#ifndef ABS
#define ABS( x )    ((x) >= 0.0 ? (x) : -(x))
#endif


// Rather than specifying RGB values for colors, this trivial
// program will simply use an enumerated type, since we only
// need four different colors.
enum ColorFlag {
  unset = 0,
  highlight,
  picked,
  rasterized
};

// Define some basic parameters that determine the size and
// spacing of the pixels, the maximum size of the raster, etc.
static const int
  gNUM_PIXELS    = 30,
  gWINDOW_X_SIZE = 750,
  gWINDOW_Y_SIZE = 600,
  gPIXEL_SPACING = 40,
  gPIXEL_RADIUS  = 14;

// Declare the global variables that will be used to keep
// track of which pixel is highlighted, which pixels have been
// chosen as the start and end points, etc.
static int
  gCurr_i   =  0,
  gCurr_j   =  0,
  gLast_i   = -1,
  gLast_j   = -1,
//  gPick_i   = -1,
//  gPick_j   = -1,
  gCount    =  0,
  gFirst_i  =  0,
  gFirst_j  =  0,
  gSecond_i =  0,
  gSecond_j =  0;

// Define the array that will hold the colors associated with
// each pixel in the raster, and also the original color of the
// pixel that is currently being highlighted.
static ColorFlag last_color = { unset };
static ColorFlag raster[gNUM_PIXELS][gNUM_PIXELS];

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
  fprintf(stderr, "GLSL Version: %s\n",
    glGetString(GL_SHADING_LANGUAGE_VERSION));
}

// Translate the enumerated type into an actual RGB triple and
// tell OpenGL to use this color for drawing subsequent polygons
// (which will be used to depict pixels).
void SetColor( ColorFlag c ){
  switch( c ){
    case unset:
      glColor3f( 0.2, 0.2, 0.2 );
      break;
    case highlight:
      glColor3f( 0.1, 1.0, 0.1 );
      break;
    case picked:
      glColor3f( 1.0, 0.0, 0.0 );
      break;
    case rasterized:
      glColor3f( 0.3, 0.6, 0.6 );
      break;
    default:
      // Throw an error & exit
      fprintf( stderr, "unknown color flag.\n" );
      exit(1);
      break;
  }
}

// Draw a circle centered at the point (x,y) with radius "rad".
// The circle will be drawn using a polygon with N vertices.
void drawCircle( int x, int y, int rad ){ 
  int N = 32;
  double scale = 2 * 3.1415926 / N;
  glBegin( GL_POLYGON );
  for( int i = 0; i < N; i++ ){
    double theta = i * scale;
    double px = x + rad * cos( theta );
    double py = y + rad * sin( theta );
    glVertex3f(  px, py, 0.0 );
  }
  glEnd();
}

// Set the pixel (i,j) to the given color.  This function
// updates the display, and also records the color of this pixel
// in the array "raster".  This is for use in highlighting -- i.e.
// when a pixel is highlighted and then unhighlighted, we need to
// set it back to the color it was before.
void setPixel( int i, int j, ColorFlag color ){
  if( i < 0 || i >= gNUM_PIXELS ){
    return;
  }
  if( j < 0 || j >= gNUM_PIXELS ){
    return;
  }
  int x = i * gPIXEL_SPACING;
  int y = j * gPIXEL_SPACING;
  SetColor( color );
  drawCircle( x, y, gPIXEL_RADIUS );
  raster[i][j] = color;
  if( i == gLast_i && j == gLast_j ){
     last_color = color;
   }
}

// Return the color currently assigned to the pixel (i,j).
ColorFlag getPixel( int i, int j ){
  return( raster[i][j] );
}

// Draw the initial "raster", which is a regular grid of "pixels"
// that are depicted by circles.  Set all the pixels to the "unset"
// color.
void clearRaster( ){
  gCount = 0;
  glClear( GL_COLOR_BUFFER_BIT ); // clear frame buffer
  for( int i = 0; i < gNUM_PIXELS; i++ ){
    for( int j = 0; j < gNUM_PIXELS; j++ ){
      setPixel( i, j, unset );
    }
  }
}

//**************************************************
// THIS IS THE FUNCTION YOU MUST REPLACE!
// This version of RasterizeLine is very crude.  It
// uses rounded floating-point arithmetic to determine
// which pixels between (x0,y0) and (x1,y1) to set
// in order to best approximate the line between these
// points.  Your version should implement Bresenham's
// algorithm, and should therefore contain NO floating
// point arithmetic at all.  Be sure to handle all
// cases of (x0,y0) and (x1,y1) -- that is, all slopes,
// and all directions!
//**************************************************
void RasterizeLine( int x0, int y0, int x1, int y1 ){
  int delta_x = x1 - x0;
  int delta_y = y1 - y0;
  int steps   = MAX( ABS(delta_x), ABS(delta_y) );
  double c    = 1.0 / MAX( 1, steps );
  for( int i = 0; i <= steps; i++ ){
    int x = int( x0 + ( i * delta_x * c ) + 0.5 );
    int y = int( y0 + ( i * delta_y * c ) + 0.5 );
    setPixel( x, y, rasterized );
  }
}

// This function is called by OpenGL whenever the display
// must be updated.  ALL drawing operations should be
// performed via this function.  OpenGL will call this
// function at various times, such as at startup, and 
// whenever glutPostRedisplay() is called.
void display( ){
  // Clear the raster once at startup.
  static int initialized = 0;
  if( !initialized ){
    clearRaster( );
    initialized = 1;
  }
  // Determine whether the cursor is now over a new
  // pixel, which must be highlighted.  If so, first
  // unhighlight the previously highlighted pixel.
  if( gCurr_i != gLast_i || gCurr_j != gLast_j ){
    setPixel( gLast_i, gLast_j, last_color );
    last_color = getPixel( gCurr_i, gCurr_j );
    setPixel( gCurr_i, gCurr_j, highlight  );
    gLast_i = gCurr_i;
    gLast_j = gCurr_j;
  }
  glFlush();
}

// As the cursor moves through the viewport, continuously
// determine which "pixel" (i.e. circle) it is nearest to,
// so that the pixel can be highlighted.
void mousePassiveMotionCallback( int x, int y ){
  double space = double(gPIXEL_SPACING);
  gCurr_i = int( 0.5 + x / space );
  gCurr_j = int( 0.5 + ( gWINDOW_Y_SIZE - y ) / space );
  glutPostRedisplay();
}

// Handle key presses: Q for "Quit", and C for "Clear".
void keyboardCallback( unsigned char key, int x, int y ){
  switch( key ){
    case 27: // The 'esc' key
    case 'q':
    case 'Q':
  #ifdef FREEGLUT
      glutLeaveMainLoop( );
  #else
      exit( 0 );
  #endif
      break;
    case 'c':
    case 'C':
      clearRaster();
      glutPostRedisplay();
      break;
    default:
        fprintf( stderr, "Unrecognized key press: %c (%d)", key, key );
        break;
  }
}

// Initialize the projection to be orthographic such that
// the "window" is exactly the size of the window on the
// screen (in pixels), with x to the right, y is up, and
// z is into the screen.  (You needn't worry about how
// this part of the program works for this assignment.)
void reshapeCallback( int width, int height ){
  if (height == 0){
		height = 1;
	}
	glViewport( 0, 0, (GLsizei)width, (GLsizei)height );
  glMatrixMode( GL_PROJECTION );
  glLoadIdentity( );
  glOrtho( 0.0, gWINDOW_X_SIZE, 0.0, gWINDOW_Y_SIZE, -1.0, 1.0 );
  
}

// When the mouse button is clicked over a "pixel", that pixel
// is "picked".  This function colors the pixel appropriately
// and detemines whether it is the first or second pixel of
// a pair.  When the second pixel of a pair is selected, it
// passes the coordinates of both pixels off to the rasterization
// algorithm, RasterizeLine.
void pickPixel( int i, int j ){
  setPixel( i, j, picked );
  if( gCount == 0 ){
    // This is the first pixel of a pair.
    gFirst_i = i;
    gFirst_j = j;
    gCount   = 1;
  }else if( gCount == 1 ){
    // This is the second pixel of a pair.
    gSecond_i = i;
    gSecond_j = j;
    gCount    = 0;
    RasterizeLine( gFirst_i, gFirst_j, gSecond_i, gSecond_j );
  }
}

// Handle mouse button events.  In this program, the left
// mouse button is used for selecting (i.e. picking) the start
// and end pixels of a line to rasterize.
void mouseButtonCallback( int button, int state, int x, int y ){
  if( button == GLUT_LEFT_BUTTON && state == GLUT_DOWN ){
    pickPixel( gCurr_i, gCurr_j );
    glutPostRedisplay();
  }
}


int main( int argc, char** argv ){

  // Do some basic initialization and setup.  Here is
  // where we set the initial size of the graphics window,
  // its placement on the screen, the background color, etc.

  // Always have GLUT take a look at argc and argv first.
  glutInit( &argc, argv );

  // Set all the values in the raster to 'unset'
  memset( raster, unset, (gNUM_PIXELS * gNUM_PIXELS * sizeof(ColorFlag)) );

  // Finish initializing our GL context and GLUT window
  glutInitDisplayMode( GLUT_SINGLE | GLUT_RGB );
  glutInitWindowSize( gWINDOW_X_SIZE, gWINDOW_Y_SIZE );
  glutInitWindowPosition( 100, 100 );
  glutCreateWindow( "Bresenham's line rasterization algorithm" );
  glClearColor( 0.0, 0.0, 0.1, 0 ); // clear window

  // Set the various callback functions, then let GLUT take over.
  glutDisplayFunc( display );
  glutPassiveMotionFunc( mousePassiveMotionCallback );
  glutMouseFunc( mouseButtonCallback );
  glutKeyboardFunc( keyboardCallback );
  glutReshapeFunc( reshapeCallback );

  msglVersion( );
  // Give GLUT control, which is never returned to this program.
  glutMainLoop( );

  return( 0 );
}
