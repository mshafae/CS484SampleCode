#include "myGL.h"

/* Do not edit these variables. */
bool myMatrixModeOn;
bool myTranslateOn;
bool myRotateOn;
bool myScaleOn;
bool myLookAtOn;
bool myFrustumOn;
bool myPerspectiveOn;
bool myOrthoOn;
int _myMatrixMode;

/* To toggle something on or off, change from false to true. */
void myGLInit( ){
  myMatrixModeOn = false;
  myTranslateOn = false;
  myRotateOn = false;
  myScaleOn = false;
  myLookAtOn = false;
  myFrustumOn = false;
  myPerspectiveOn = false;
  myOrthoOn = false;
  /*if( myMatrixModeOn ){
    myProjectionStack = new std::stack<Mat3>( );
    myModelingStack = new std::stack<Mat3>( );
    glGetIntegerv(GL_MATRIX_MODE, &_myMatrixMode);
  }*/
}

void myMatrixMode( GLenum mode ){
  if( myMatrixModeOn ){
    _myMatrixMode = mode;
  }else{
    glMatrixMode(mode);
  }
}

void myPushMatrix( ){
  if( myMatrixModeOn ){
    if(_myMatrixMode == GL_MODELVIEW){
      // your code here
    }else if(_myMatrixMode == GL_PROJECTION){
      // your code here
    }
  }else{
    glPushMatrix( );
  }
}

void myPopMatrix( ){
  if( myMatrixModeOn ){
    if(_myMatrixMode == GL_MODELVIEW){
      // your code here
    }else if(_myMatrixMode == GL_PROJECTION){
      // your code here
    }
  }else{
    glPopMatrix( );
  }
}

void myLoadIdentity( ){
  if( myMatrixModeOn ){
    if(_myMatrixMode == GL_MODELVIEW){
      // your code here
    }else if(_myMatrixMode == GL_PROJECTION){
      // your code here
    }
  }else{
    glLoadIdentity( );
  }
}

void myTranslatef( float x, float y, float z ){
  if( myTranslateOn ){
    // your code here
  }else{
    glTranslatef( x, y, z );
  }
}
		 
void myRotatef( float angle, float x, float y, float z){
  if( myRotateOn ){
    // your code here
  }else{
    glRotatef(angle, x, y, z);
  }
}
		 
void myScalef(float x, float y, float z ){
  if(myScaleOn){
    // your code here
  }else{
    glScalef(x, y, z);
  }
}
		  
void myLookAt(double eyeX, double eyeY, double eyeZ, double centerX, double centerY, double centerZ, double upX, double upY, double upZ){
  if( myLookAtOn ){
    // your code here
  }else{
    gluLookAt( eyeX, eyeY, eyeZ, centerX, centerY, centerZ, upX, upY, upZ);
  }
}

void myFrustum(double left, double right, double bottom, double top, double zNear, double zFar){
  if( myFrustumOn ){
    // your code here
  }else{
    glFrustum(left, right, bottom, top, zNear, zFar);
  }
}

void myPerspective(double fovy, double aspect, double zNear, double zFar){
  if( myPerspectiveOn ){
    // your code here
  }else{
    gluPerspective(fovy, aspect, zNear, zFar);
  }
}

void myOrtho(double left, double right, double bottom, double top, double zNear, double zFar ){
  if( myOrthoOn ){
    // your code here
  }else{
    glOrtho(left, right, bottom, top, zNear, zFar);
  }
}


void toggleMyMatrixMode( ){
  printf("toggleMyMatrixMode not implemented\n");
}

void toggleMyTranslate( ){
  printf("toggleMyTranslate not implemented\n");
}

void toggleMyRotate( ){
  printf("toggleMyRotate not implemented\n");
}

void toggleMyScale( ){
  printf("toggleMyScale not implemented\n");
}

void toggleMyLookAt( ){
  printf("toggleMyLookAt not implemented\n");
}

void toggleMyFrustum( ){
  printf("toggleMyFrustum not implemented\n");
}

void toggleMyPerspective( ){
  printf("toggleMyPerspective not implemented\n");
}

void toggleMyOrtho( ){
  printf("toggleMyOrtho not implemented\n");
}
