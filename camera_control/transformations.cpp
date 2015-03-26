// 
// Michael Shafae
// mshafae at fullerton.edu
// 
// Procedural module that implements transformations used in
// the homework assignment.
//
// $Id: transformations.cpp 4897 2014-04-07 05:13:41Z mshafae $
//
// STUDENTS _MUST_ ADD THEIR CODE INTO THIS FILE
//

#include "transformations.h"

// Just in case you have a weird cmath header file...
#ifndef M_PI
#define M_PI                3.14159265358979323846264338327950288
#endif
#ifndef PI_OVER_ONE_EIGHTY
#define PI_OVER_ONE_EIGHTY  0.01745329251994329547437168059786927188
#endif
#ifndef ONE_EIGHTY_OVER_PI
#define ONE_EIGHTY_OVER_PI  57.29577951308232286464772187173366546631
#endif

// Don't forget:
// OpenGL's unit for angles is degrees.
// C math library's unit for angles is radians.
#ifndef DEG2RAD
#define DEG2RAD( theta ) ((theta) * (PI_OVER_ONE_EIGHTY))
#endif
#ifndef RAD2DEG
#define RAD2DEG( theta ) ((theta) * (ONE_EIGHTY_OVER_PI))
#endif
// Quick-n-dirty absolute value macro
#ifndef ABS
#define ABS( x ) ((x) < (0) ? (-x) : (x))
#endif
// Don't use pow( ) to square a value.
#ifndef SQR
#define SQR( x ) ((x) * (x))
#endif


#ifndef __SOLUTION__

void rotateCameraLeft(float degrees, float *eyePosition, float *centerPosition, float *upVector){
  // Please implement this function.
}

void rotateCameraUp(float degrees, float *eyePosition, float *centerPosition, float *upVector){
  // Please implement this function.
}

void myTranslatef( GLfloat *matrix, GLfloat x, GLfloat y, GLfloat z ){
  // Please implement this function.
}

void myScalef( GLfloat *matrix, GLfloat x, GLfloat y, GLfloat z ){
  // Not needed in this exercise.
}

void myRotatef( GLfloat *matrix,
                GLfloat angle, GLfloat x, GLfloat y, GLfloat z ){
  // Remember the Rodrigues' rotation formula?
}

void myLookAt( GLfloat *matrix,
               GLdouble eyeX, GLdouble eyeY, GLdouble eyeZ,
               GLdouble centerX, GLdouble centerY, GLdouble centerZ,
               GLdouble upX, GLdouble upY, GLdouble upZ ){
  // Please implement this function.

  // This code is just a placeholder to demonstrate how this procedure
  // returns the LookAt matrix by reference.
  // YOU MUST REMOVE THE CODE BELOW AND WRITE YOUR OWN ROUTINE.
  int mode;
  glGetIntegerv(GL_MATRIX_MODE, &mode);
  glPushMatrix( );
  gluLookAt(
    eyeX, eyeY, eyeZ,
    centerX, centerY, centerZ,
    upX, upY, upZ
  );
  glGetFloatv(mode, matrix);
  glPopMatrix( );
}

void myFrustum( GLfloat *matrix,
                GLdouble left, GLdouble right, GLdouble bottom,
                GLdouble top, GLdouble zNear, GLdouble zFar ){
  // Not needed in this exercise.
}

void myPerspective( GLfloat *matrix,
                    GLdouble fovy, GLdouble aspect,
                    GLdouble zNear, GLdouble zFar ){
  // Not needed in this exercise.
}

void myOrtho( GLfloat *matrix,
              GLdouble left, GLdouble right, GLdouble bottom,
              GLdouble top, GLdouble zNear, GLdouble zFar ){
  // Not needed in this exercise.
}

#else
#include "transformations_solution.cpp"
#endif
