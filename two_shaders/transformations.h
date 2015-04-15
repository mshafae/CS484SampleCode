// 
// Michael Shafae
// mshafae at fullerton.edu
// 
// Procedural module that implements transformations used in
// the homework assignment.
//
// $Id: transformations.h 5672 2015-04-09 01:55:03Z mshafae $
//
// STUDENTS _MUST_ ADD THEIR CODE INTO THIS FILE
//

#include "GFXMath.h"

#ifndef _TRANSFORMATIONS_H_
#define _TRANSFORMATIONS_H_

// This is for testing, just ignore it.
//#define __SOLUTION__

/*
 * rotateCameraLeft( ) rotates the coordinate system defined by
 * the eyePosition and upVector by degrees around the upVector.
 * eyePosition and upVector are passed and returned by reference.
 * degrees: The number of degrees to rotate by.
 * eyePosition: Specifies the position of the eye point.
 * centerPosition: Specifies the position of the reference point.
 * upVector: Specifies the direction of the up vector.
 */
void rotateCameraLeft(float degrees, Vec3& eyePosition, Vec3& centerPosition, Vec3& upVector);

/*
 * rotateCameraUp( ) rotates the coordinate system defined by
 * the eyePosition and upVector by degrees around the right vector.
 * eyePosition and upVector are passed and returned by reference.
 * degrees: The number of degrees to rotate by.
 * eyePosition: Specifies the position of the eye point.
 * centerPosition: Specifies the position of the reference point.
 * upVector: Specifies the direction of the up vector.
 */
void rotateCameraUp(float degrees, Vec3& eyePosition, Vec3& centerPosition, Vec3& upVector);

#endif
