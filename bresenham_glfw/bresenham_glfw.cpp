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
 * $Id: bresenham_glfw.cpp 4830 2014-02-13 09:09:42Z mshafae $
 *
 */

#include <cstdlib>
#include <cstdio>
#include <cmath>
#include <cstring>

#include <GL/glew.h>
#define GLFW_INCLUDE_GLU
#include <GLFW/glfw3.h>

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
void setColor( ColorFlag c ){
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
  raster[i][j] = color;
  if( i == gLast_i && j == gLast_j ){
     last_color = color;
   }
}

// Return the color currently assigned to the pixel (i,j).
ColorFlag getPixel( int i, int j ){
  return( raster[i][j] );
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

void drawRaster( ){
  int c_x = gCurr_i * gPIXEL_SPACING;
  int c_y = gCurr_j * gPIXEL_SPACING;
  
  for(int i = 0; i < gNUM_PIXELS; i++ ){
    for(int j = 0; j < gNUM_PIXELS; j++){
      int x = i * gPIXEL_SPACING;
      int y = j * gPIXEL_SPACING;
      if( x == c_x && y == c_y ){
        setColor( highlight );
      }else{
        setColor( getPixel(i, j) );
      }
      drawCircle( x, y, gPIXEL_RADIUS );
    }
  }
}

void drawCurrentPixel( ){
  printf("%d %d\n", gCurr_i, gCurr_j);
  int x = gCurr_i * gPIXEL_SPACING;
  int y = gCurr_j * gPIXEL_SPACING;
  setColor( highlight );
  drawCircle( x, y, gPIXEL_RADIUS );
}

// Draw the initial "raster", which is a regular grid of "pixels"
// that are depicted by circles.  Set all the pixels to the "unset"
// color.
void clearRaster( ){
  gCount = 0;
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

static void errorCallback(int error, const char* description){
  fprintf(stderr, "GLFW Error: %s\n", description);
}

// As the cursor moves through the viewport, continuously
// determine which "pixel" (i.e. circle) it is nearest to,
// so that the pixel can be highlighted.
void mouseCurpsorPositionCallback( GLFWwindow* window, double _x, double _y ){
  int x = int(floor(_x));
  int y = int(floor(_y));  
  double space = double(gPIXEL_SPACING);
  gCurr_i = int( 0.5 + x / space );
  gCurr_j = int( 0.5 + ( gWINDOW_Y_SIZE - y ) / space );
}

// Handle key presses: Q for "Quit", and C for "Clear".
static void keyCallback(GLFWwindow* window, int key, int scancode, int action, int mods){
  if( action == GLFW_PRESS ){
    switch( key ){
      case GLFW_KEY_ESCAPE:
      case 'q':
      case 'Q':
        glfwSetWindowShouldClose(window, GL_TRUE);
        break;
      case 'c':
      case 'C':
        clearRaster();
        break;
      default:
          fprintf( stderr, "Key pressed: %c (%d)", key, key );
          break;
    }
  }
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
void mouseButtonCallback( GLFWwindow* window, int button, int action, int mods ){
  if( action == GLFW_PRESS && button == GLFW_MOUSE_BUTTON_1 ){
    pickPixel( gCurr_i, gCurr_j );
  }
}


int main( int argc, char** argv ){

  // Always init GLFW before you do anything else
  GLFWwindow* window;
  glfwSetErrorCallback(errorCallback);
  if( !glfwInit( ) ){
    exit(1);
  }

  glfwWindowHint(GLFW_RESIZABLE, GL_FALSE);
  
  // Hints to help set up the GL context
  //glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
  //glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 2);
  //glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
  //glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);
  //glfwWindowHint(GLFW_OPENGL_DEBUG_CONTEXT, GL_TRUE);
  window = glfwCreateWindow(gWINDOW_X_SIZE, gWINDOW_Y_SIZE,
    "Bresenham's line rasterization algorithm", 0, NULL);
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
  glfwSetCursorPosCallback(window, mouseCurpsorPositionCallback);
  glfwSetMouseButtonCallback(window, mouseButtonCallback);

  glClearColor( 0.0, 0.0, 0.1, 0 );
  glEnable(GL_DEPTH_TEST);
  glDepthFunc(GL_LESS);

  msglVersion( );

  // Set all the values in the raster to 'unset'
  memset( raster, unset, (gNUM_PIXELS * gNUM_PIXELS * sizeof(ColorFlag)) );

  clearRaster( );

  while( !glfwWindowShouldClose(window) ){
    int width, height;
    glfwGetFramebufferSize(window, &width, &height);
    glViewport(0, 0, width, height);

    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    glMatrixMode( GL_PROJECTION );
    glLoadIdentity( );
    glOrtho( 0.0, gWINDOW_X_SIZE, 0.0, gWINDOW_Y_SIZE, -1.0, 1.0 );
  
    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity( );

    drawRaster( );
    
    glfwSwapBuffers(window);
    glfwPollEvents( );
  }
  
  glfwDestroyWindow(window);
  glfwTerminate( );

  return( 0 );
}
