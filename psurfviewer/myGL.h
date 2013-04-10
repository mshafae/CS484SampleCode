
#ifndef _MYGL_H_
#define _MYGL_H_

#ifdef __APPLE__
/* Apple's weird location of their OpenGL & GLUT implementation */
#include <GLUT/glut.h>
#include <OpenGL/OpenGL.h>
#else
#include <GL/glut.h>
#include <GL/gl.h>
#endif

#include "myGL.h"
#include "Vec3.h"
#include "Mat3.h"

/* Initialize your mini-GL library */
void myGLInit( );

/* Controlled by myMatrixModeOn */
void myMatrixMode( GLenum mode );

/* Controlled by myMatrixModeOn */
void myPushMatrix( );

/* Controlled by myMatrixModeOn */
void myPopMatrix( );

/* Controlled by myMatrixModeOn */
void myLoadIdentity( );

/* Controlled by myTranslateOn */
void myTranslatef( float x, float y, float z );
		 
/* Controlled by myRotateOn */
void myRotatef( float angle, float x, float y, float z);
		 
/* Controlled by myScaleOn */
void myScalef(float x, float y, float z );
		  
/* Controlled by myLookAtOn */
void myLookAt(double eyeX, double eyeY, double eyeZ, double centerX, double centerY, double centerZ, double upX, double upY, double upZ);

/* Controlled by myFrustumOn */
void myFrustum(double left, double right, double bottom, double top, double zNear, double zFar);
		                                  
/* Controlled by myPerspectiveOn */
void myPerspective(double fovy, double aspect, double zNear, double zFar);

/* Controlled by myOrthoOn */
void myOrtho(double left, double right, double bottom, double top, double zNear, double zFar );

/* Advanced students who want to toggle things on or off at
 * runtime can implement these functions. */
void toggleMyMatrixMode( );
void toggleMyTranslate( );
void toggleMyRotate( );
void toggleMyScale( );
void toggleMyLookAt( );
void toggleMyFrustum( );
void toggleMyPerspective( );
void toggleMyOrtho( );

#endif