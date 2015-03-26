// 
// Michael Shafae
// mshafae at fullerton.edu
// 
// Procedural module that implements transformations used in
// the homework assignment.
//
// $Id: transformations.h 4915 2014-04-10 07:05:10Z mshafae $
//
// STUDENTS _MUST_ ADD THEIR CODE INTO THIS FILE
//

#ifndef _TRANSFORMATIONS_H_
#define _TRANSFORMATIONS_H_

// This is for testing, just ignore it.
//#define __SOLUTION__

#ifdef _WIN32
#include <Windows.h>
#endif

#ifdef __APPLE__
/* Apple's weird location of their OpenGL & GLUT implementation */
#include <OpenGL/gl.h>
#include <OpenGL/glu.h>
#else
/* Unix, Linux, and BSD */
#include <GL/gl.h>
#include <GL/glu.h>
#endif

#ifdef WIN32
// For those who wish to use MSVS, the math defines, such as M_PI, are
// not defined by default.
#define _USE_MATH_DEFINES
#endif

#include <cmath>

/*
 * rotateCameraLeft( ) rotates the coordinate system defined by
 * the eyePosition and upVector by degrees around the upVector.
 * eyePosition and upVector are passed and returned by reference.
 * degrees: The number of degrees to rotate by.
 * eyePosition: Specifies the position of the eye point.
 * centerPosition: Specifies the position of the reference point.
 * upVector: Specifies the direction of the up vector.
 */
void rotateCameraLeft(float degrees, float *eyePosition, float *centerPosition, float *upVector);

/*
 * rotateCameraUp( ) rotates the coordinate system defined by
 * the eyePosition and upVector by degrees around the right vector.
 * eyePosition and upVector are passed and returned by reference.
 * degrees: The number of degrees to rotate by.
 * eyePosition: Specifies the position of the eye point.
 * centerPosition: Specifies the position of the reference point.
 * upVector: Specifies the direction of the up vector.
 */
void rotateCameraUp(float degrees, float *eyePosition, float *centerPosition, float *upVector);

/*
 * myTranslatef( ) is similar to glTranslate( ) except that the resulting
 * matrix is returned.
 * matrix: the scale matrix that is passed and returned by reference
 * x, y, z: Specify the x, y, and z coordinates of a translation vector.
 */
void myTranslatef( GLfloat *matrix, GLfloat x, GLfloat y, GLfloat z );

/*
 * myScalef( ) is similar to glScalef( ) except that the resulting
 * matrix is returned.
 * matrix: the scale matrix that is passed and returned by reference
 * x, y, z: Specify scale factors along the x, y, and z axes, respectively.
 */
void myScalef( GLfloat *matrix,
               GLfloat x, GLfloat y, GLfloat z );

/*
 * myRotatef( ) is similar to glRotatef( ) except that the resulting
 * matrix is returned.
 * matrix: the rotation matrix that is passed and returned by reference
 * angle: the amount of rotation in degrees
 * x, y, z: the vector to rotate around
 */
void myRotatef( GLfloat *matrix,
                GLfloat angle, GLfloat x, GLfloat y, GLfloat z );

/*
 * myLookAt( ) is similar to gluLookAt( ) except that the resulting
 * matrix is returned.
 * matrix: the viewing matrix that is passed and returned by reference
 * eyeX, eyeY, eyeZ: Specifies the position of the eye point.
 * centerX, centerY, centerZ: Specifies the position of the
 *                            reference point.
 * upX, upY, upZ: Specifies the direction of the up vector.
 */
void myLookAt( GLfloat *matrix,
               GLdouble eyeX, GLdouble eyeY, GLdouble eyeZ,
               GLdouble centerX, GLdouble centerY, GLdouble centerZ,
               GLdouble upX, GLdouble upY, GLdouble upZ );
/*
 * myFrustum( ) is similar to glFrustum( ) except that the resulting
 * matrix is returned.
 * matrix: the perspective matrix that is passed and returned by reference
 * left, right: Specify the coordinates for the left and right vertical
 *              clipping planes.
 * bottom, top: Specify the coordinates for the bottom and top
 *              horizontal clipping planes.
 * zNear, zFar: Specify the distances to the near and far depth
 *              clipping planes.  Both distances must be positive.
 */
void myFrustum( GLfloat *matrix,
                GLdouble left, GLdouble right, GLdouble bottom,
                GLdouble top, GLdouble zNear, GLdouble zFar );
/*
 * myPerspective( ) is similar to gluPerspective( ) except that
 * the resulting matrix is returned.
 * matrix: the perspective matrix that is passed and returned by reference
 * fovy: Specifies  the field of view angle, in degrees,
 *       in the y direction.
 * aspect: Specifies the aspect ratio that determines the field of view
 *         in the x direction.  The aspect ratio is the ratio of
 *         x (width) to y (height).
 * zNear: Specifies the distance from the viewer to the near clipping
 *        plane (always positive).
 * zFar: Specifies the distance from the viewer to the far clipping
 *       plane (always positive).
 */
void myPerspective( GLfloat *matrix,
                    GLdouble fovy, GLdouble aspect,
                    GLdouble zNear, GLdouble zFar );
/*
 * myPerspective( ) is similar to gluPerspective( ) except that
 * the resulting matrix is returned.
 * matrix: the orthographic perspective matrix that is passed and
 *         returned by reference
 * left, right: Specify the coordinates for the left and right vertical
 *              clipping planes.
 * bottom, top: Specify the coordinates for the bottom and top horizontal
 *              clipping planes.
 * zNear, zFar: Specify the distances to the nearer and farther depth
 *              clipping planes.  These values are negative if the
 *              plane is to be behind the viewer.
 */
void myOrtho( GLfloat *matrix,
              GLdouble left, GLdouble right, GLdouble bottom,
              GLdouble top, GLdouble zNear, GLdouble zFar );

#endif
