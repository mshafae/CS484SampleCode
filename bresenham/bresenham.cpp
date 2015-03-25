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
 * $Id: bresenham.cpp 5542 2015-02-18 07:18:17Z mshafae $
 *
 */

#include <cstdlib>
#include <cstdio>
#include <cmath>
#include <cstring>

#ifdef __linux__
#ifdef minor
#undef minor
#endif
#ifdef major
#undef major
#endif
#endif

#include "GFXMath.h"
#include "GLFWApp.h"

class Bresenham : public GLFWApp{
private:
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
  
    // Define the array that will hold the colors associated with
    // each pixel in the raster, and also the original color of the
    // pixel that is currently being highlighted.
    ColorFlag raster[gNUM_PIXELS][gNUM_PIXELS];
    
    Vec2i _currentPixel;
    Vec2i _startPixel;
    Vec2i _stopPixel;
    bool _startStopFlag;
    bool _mouseButtonDown;
  
  public:
    Bresenham(int argc, char* argv[]):GLFWApp(argc, argv, std::string("Bresenham's Line Rasterization Algorithm").c_str( ), gWINDOW_X_SIZE, gWINDOW_Y_SIZE),
    _currentPixel(0, 0),
    _startPixel(0, 0),
    _stopPixel(0, 0),
    _startStopFlag(false),
    _mouseButtonDown(false){ }
    
  private:
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
  void RasterizeLine( ){
    int x0, y0, x1, y1;
    x0 = _startPixel[0];
    y0 = _startPixel[1];
    x1 = _stopPixel[0];
    y1 = _stopPixel[1];

    int delta_x = x1 - x0;
    int delta_y = y1 - y0;
    int steps   = fmax( fabs(delta_x), fabs(delta_y) );
    double c    = 1.0 / fmax( 1, steps );
    for( int i = 0; i <= steps; i++ ){
      int x = int( x0 + ( i * delta_x * c ) + 0.5 );
      int y = int( y0 + ( i * delta_y * c ) + 0.5 );
      setPixel( x, y, rasterized );
    }
  }
  
  // Draw the initial "raster", which is a regular grid of "pixels"
  // that are depicted by circles.  Set all the pixels to the "unset"
  // color.
  void clearRaster( ){
    _startStopFlag = false;
    for( int i = 0; i < gNUM_PIXELS; i++ ){
      for( int j = 0; j < gNUM_PIXELS; j++ ){
        setPixel( i, j, unset );
      }
    }
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
  }

  // Return the color currently assigned to the pixel (i,j).
  ColorFlag getPixel( int i, int j ){
    return( raster[i][j] );
  }

  // When the mouse button is clicked over a "pixel", that pixel
  // is "picked".  This function colors the pixel appropriately
  // and detemines whether it is the first or second pixel of
  // a pair.  When the second pixel of a pair is selected, it
  // passes the coordinates of both pixels off to the rasterization
  // algorithm, RasterizeLine.
  void pickPixel( Vec2i& pixel){
    //int i, int j
    setPixel( pixel[0], pixel[1], picked );
    if( _startStopFlag == false ){
      // This is the first pixel of a pair.
      _startPixel = pixel;
      _startStopFlag = true;
    }else if( _startStopFlag ){
      // This is the second pixel of a pair.
      _stopPixel = pixel;
      _startStopFlag = false;
      RasterizeLine( );
    }
  }

  // Draw a circle centered at the point (x,y) with radius "rad".
  // The circle will be drawn using a polygon with N vertices.
  void drawCircle( Vec2i& pixel, int rad ){ 
    int N = 16;
    double scale = 2 * M_PI / N;
    glBegin( GL_POLYGON );
    for( int i = 0; i < N; i++ ){
      double theta = i * scale;
      double px = pixel[0] + rad * cos( theta );
      double py = pixel[1] + rad * sin( theta );
      glVertex3f( px, py, 0.0 );
    }
    glEnd();
  }

  void drawRaster( ){
    Vec2i cp = _currentPixel * int(gPIXEL_SPACING);
    for(int i = 0; i < gNUM_PIXELS; i++ ){
      for(int j = 0; j < gNUM_PIXELS; j++){
        Vec2i p(i * gPIXEL_SPACING, j * gPIXEL_SPACING );
        if(cp == p){
          setColor( highlight );
        }else{
          setColor( getPixel(i, j) );
        }
        drawCircle( p, gPIXEL_RADIUS );
      }
    }
  }
  
public:
  bool begin( ){
    bool rv = true;
    glClearColor( 0.0, 0.0, 0.1, 0 );
    glEnable(GL_DEPTH_TEST);
    glDepthFunc(GL_LESS);
    memset(raster, unset, (gNUM_PIXELS * gNUM_PIXELS * sizeof(ColorFlag)) );
    clearRaster( );
    return rv;
  }

  bool end( ){
    windowShouldClose( );
    return true;
  }

  bool render( ){
    float ortho[16] = {0.002666666666667, 0.0, 0.0, 0.0, 0.0, 0.003333333333333, 0.0, 0.0, 0.0, 0.0, -1.0, 0.0, -1.0, -1.0, 0.0, 1.0};
    
    bool rv = true;

    if(isKeyPressed('C')){
      clearRaster( );
    }
    if(isKeyPressed('Q')){
      end( );
    }
    
    Vec2 mp = mouseCurrentPosition( );
    int x = int(floor(mp[0]));
    int y = int(floor(mp[1]));  
    double space = double(gPIXEL_SPACING);
    _currentPixel = Vec2i( int( 0.5 + x / space ), int( 0.5 + ( gWINDOW_Y_SIZE - y ) / space ) );
    
    if(mouseButtonFlags( ) == GLFWApp::MOUSE_BUTTON_LEFT){
      _mouseButtonDown = true;
    }else if(_mouseButtonDown){
      _mouseButtonDown = false;
      pickPixel(_currentPixel);
    }
    
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity( );
    glMultMatrixf(ortho);
    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity( );
    drawRaster( );
    return rv;
  };
};


int main(int argc, char* argv[])
{
  Bresenham app(argc, argv);
  return app();
}
