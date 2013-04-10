 
#ifdef __APPLE__
/* Apple's weird location of their OpenGL & GLUT implementation */
#include <GLUT/glut.h>
#include <OpenGL/OpenGL.h>
#else
#include <GL/glut.h>
#include <GL/gl.h>
#endif

#include <cstdlib>
#include <cstdio>
#include <string>

/* Thanks to Apple's Sample Code... */
#include "SurfaceGeometry.h"

#include "SGFaceList.h"
#include "getopt.h"

SGFaceList *gModel[kSurfaces];
unsigned int gCurrentModel;

float gTranslation[3], gRotationAngle[3], gScaleFactor[3];

void printVector(float v[3]){
  printf( "(%g, %g, %g)\n", v[0], v[1], v[2] );
}

void usage( std::string msg ){
  std::cerr << msg << std::endl;
  std::cerr << "usage: psurfviewer [-v -h]" << std::endl;
  std::cerr << "                 or" << std::endl;
  std::cerr << "       psurfviewer [--verbose --help]" << std::endl;
}

/*  Initialize material property, light source, lighting model,
 *  and depth buffer.
 */
void init( void ) 
{
   glClearColor( 0.0, 0.0, 0.0, 0.0 );
   glDisable( GL_LIGHTING );
   glEnable( GL_DEPTH_TEST );
   glFrontFace( GL_CCW );
 	
   for( int i = 0; i < kSurfaces; i++ ){
     gModel[i] = BuildGeometry( i, 4, 8, 3 );     
   }
   gCurrentModel = 0;
   for( int i = 0; i < 3; i++ ){
     gRotationAngle[i] = 0.0f;
     gTranslation[i] = 0.0f;
     gScaleFactor[i] = 1.0f;
   }
}

void drawSurface( SGFaceList *f ){
  int i = 0;
  int j = 0;
  int index;
  if( f->surface == kCube ){
    glEnable( GL_POLYGON_OFFSET_FILL );
    glBegin( GL_TRIANGLES );
    for( i = 0; i < f->fc; i++ ){
      for( j = 0; j < 3; j++ ){
        glColor3fv( f->colors[ f->faces[i][j] ] );
        glVertex3fv( f->vertices[ f->faces[i][j] ] );
      }
    }
    glEnd( );
    glColor3f( 0.0, 0.0, 0.0 );
    for( i = 0; i < (f->fc); i++ ){
      glBegin( GL_LINE_LOOP );
      for( j = 0; j < 3; j++ ){
        glVertex3fv( f->vertices[ f->faces[i][j] ] );
      }
      glEnd( );
    }
    glDisable( GL_POLYGON_OFFSET_LINE );
  }else{
    for( i = 0; i < (f->maxI); i++ ){
      glBegin( GL_TRIANGLE_STRIP );
      for( j = 0; j <= (f->maxJ); j++ ){
        index = (i % (f->maxI)) * (f->maxJ) + (j % (f->maxJ));
        glColor3fv( f->colors[index] );
        glNormal3fv( f->v_normals[index] );
        glVertex3fv( f->vertices[index] );
        
        index = ((i + 1) % f->maxI) * f->maxJ + (j % f->maxJ);
        glColor3fv( f->colors[index] );
        glNormal3fv( f->v_normals[index] );
        glVertex3fv( f->vertices[index] );
      }
      glEnd( );
    }
  }
}

void display( void ){
   glClear (GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
   glLoadIdentity( );
   gluLookAt( 0.0, 0.0, -15.0, 0.0, 0.0, 0.0, 0.0, 1.0, 0.0 );
   glRotatef( gRotationAngle[X], 1.0, 0.0, 0.0 );
   glRotatef( gRotationAngle[Y], 0.0, 1.0, 0.0 );
   glRotatef( gRotationAngle[Z], 0.0, 0.0, 1.0 );
   glScalef( gScaleFactor[X], gScaleFactor[Y], gScaleFactor[Z] );
   glTranslatef(gTranslation[X], gTranslation[Y], gTranslation[Z] );
   //glutSolidTorus (0.5, 1.0, 32, 60);
   drawSurface( gModel[gCurrentModel] );
   glFlush ();
   glutSwapBuffers();
}

void reshape( int w, int h ){
   glViewport( 0, 0, (GLsizei) w, (GLsizei) h );
   glMatrixMode( GL_PROJECTION );
   glLoadIdentity( );
   gluPerspective( 40.0, (GLfloat) w/(GLfloat) h, 1.0, 20.0 );
   glMatrixMode( GL_MODELVIEW );
   glLoadIdentity( );
}

void mouse( int button, int state, int x, int y ) {
  if( glutGetModifiers( ) == GLUT_ACTIVE_SHIFT ){
	   switch (button) {
       case GLUT_LEFT_BUTTON:
         break;
       case GLUT_MIDDLE_BUTTON:
         // Fall through
       case GLUT_RIGHT_BUTTON:
         break;
       default:
         // You have more than three buttons on your mouse?
         break;
    }
	}else if( glutGetModifiers( ) == GLUT_ACTIVE_CTRL ){
     switch (button) {
       case GLUT_LEFT_BUTTON:
         break;
       case GLUT_MIDDLE_BUTTON:
         // Fall through
       case GLUT_RIGHT_BUTTON:
         break;
       default:
         // You have more than three buttons on your mouse?
         break;
    }
  }else{
    switch (button) {
      case GLUT_LEFT_BUTTON:
        break;
      case GLUT_MIDDLE_BUTTON:
        // Fall through
      case GLUT_RIGHT_BUTTON:
        break;
      default:
        // You have more than three buttons on your mouse?
        break;
   }
 }
 glutPostRedisplay( );
}

void mouseMotion(int x, int y){
  
  glutPostRedisplay( );
}

void special( int key, int px, int py ){
	if( glutGetModifiers( ) == GLUT_ACTIVE_SHIFT ){
		switch( key ){
		case GLUT_KEY_UP:
			break;
		case GLUT_KEY_DOWN:
			break;
	  }
	}else{
	  switch( key ){
		case GLUT_KEY_UP:
			break;
		case GLUT_KEY_DOWN:
			break;
		case GLUT_KEY_LEFT:
			break;
		case GLUT_KEY_RIGHT:
			break;
	  }
	}
  glutPostRedisplay( );
}

void keyboard( unsigned char key, int x, int y ){
  switch( key ){
    case 27:
      // The esc key
      exit( 0 );
    break;
    case '+':
    // do something
    break;
    case '-':
    // do something
    break;
    case ' ':
      gCurrentModel = (gCurrentModel + 1) % kSurfaces;
    break;
    default:
      std::cerr << "Unknown key press \'" << key << "\'" << std::endl;
    break;
  }
  glutPostRedisplay( );
}

int main(int argc, char** argv){
  int ch;
  struct option longopts[] = {
    { "verbose", required_argument, NULL, 'v' },
    { "help", required_argument, NULL, 'h' },
    { NULL, 0, NULL, 0 }
  };
  
  // Let GLUT process the command line first
  glutInit(&argc, argv);

  // Let's figure out what the command line options are
  while( (ch = getopt_long(argc, argv, "vh", longopts, NULL)) != -1 ){
    switch( ch ){
      case 'v':
        // Turn on debugging
      break;
      case 'h':
        usage( std::string( "Hope this helps..." ) );
      break;
      default:
        /* do nothing */
        fprintf( stderr, "Ignoring unknown option: %c\n", ch );
      break;
    } 
  }

  glutInitDisplayMode( GLUT_DOUBLE | GLUT_RGB | GLUT_DEPTH );
  glutInitWindowSize( 800, 800 ); 
  glutInitWindowPosition( 100, 100 );
  glutCreateWindow( argv[0] );

  // Initialize our OpenGL environment
  init( );

 /*
   * Set up our call back functions to handle events
   */
  // Handle window size changes
  glutReshapeFunc( reshape );
  // Handle keyboard events
  glutKeyboardFunc( keyboard );
  glutSpecialFunc( special );
  // display gets called every time we want to refresh the screen
  glutDisplayFunc( display );
  // handle user input via the mouse
  glutMouseFunc( mouse );
  glutMotionFunc( mouseMotion );

  // The program doesn't return from the next call.
  glutMainLoop( );

  return( 0 );
}
