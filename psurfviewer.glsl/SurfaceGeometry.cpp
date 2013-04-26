/*
 *  SufaceGeometry.c
 *  Carbon OpenGL
 *
 *  Created by Geoff Stahl.
	Copyright:	Copyright © 2002-2003 Apple Computer, Inc., All Rights Reserved

	Disclaimer:	IMPORTANT:  This Apple software is supplied to you by Apple Computer, Inc.
			("Apple") in consideration of your agreement to the following terms, and your
			use, installation, modification or redistribution of this Apple software
			constitutes acceptance of these terms.  If you do not agree with these terms,
			please do not use, install, modify or redistribute this Apple software.

			In consideration of your agreement to abide by the following terms, and subject
			to these terms, Apple grants you a personal, non-exclusive license, under AppleÕs
			copyrights in this original Apple software (the "Apple Software"), to use,
			reproduce, modify and redistribute the Apple Software, with or without
			modifications, in source and/or binary forms; provided that if you redistribute
			the Apple Software in its entirety and without modifications, you must retain
			this notice and the following text and disclaimers in all such redistributions of
			the Apple Software.  Neither the name, trademarks, service marks or logos of
			Apple Computer, Inc. may be used to endorse or promote products derived from the
			Apple Software without specific prior written permission from Apple.  Except as
			expressly stated in this notice, no other rights or licenses, express or implied,
			are granted by Apple herein, including but not limited to any patent rights that
			may be infringed by your derivative works or by other works in which the Apple
			Software may be incorporated.

			The Apple Software is provided by Apple on an "AS IS" basis.  APPLE MAKES NO
			WARRANTIES, EXPRESS OR IMPLIED, INCLUDING WITHOUT LIMITATION THE IMPLIED
			WARRANTIES OF NON-INFRINGEMENT, MERCHANTABILITY AND FITNESS FOR A PARTICULAR
			PURPOSE, REGARDING THE APPLE SOFTWARE OR ITS USE AND OPERATION ALONE OR IN
			COMBINATION WITH YOUR PRODUCTS.

			IN NO EVENT SHALL APPLE BE LIABLE FOR ANY SPECIAL, INDIRECT, INCIDENTAL OR
			CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE
			GOODS OR SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION)
			ARISING IN ANY WAY OUT OF THE USE, REPRODUCTION, MODIFICATION AND/OR DISTRIBUTION
			OF THE APPLE SOFTWARE, HOWEVER CAUSED AND WHETHER UNDER THEORY OF CONTRACT, TORT
			(INCLUDING NEGLIGENCE), STRICT LIABILITY OR OTHERWISE, EVEN IF APPLE HAS BEEN
			ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
 *
 */

 /* Uses techniques described by Paul Bourke 1999 - 2002 */ 
 /* Tranguloid Trefoil and other example surfaces by Roger Bagula see <http://astronomy.swin.edu.au/~pbourke/surfaces/> */
// New URL <http://paulbourke.net/geometry/>

#include <cmath>
#include <cstdio>
#include <cstdlib>

#include "SurfaceGeometry.h"

#define PI M_PI
#define TWOPI (M_PI*2)
#define vcopy( dest, src, t )	(dest)[X] = (t)(src)[X]; \
(dest)[Y] = (t)(src)[Y]; \
(dest)[Z] = (t)(src)[Z]

/* Code based on work by Paul Bourke */

// globals for apps to use
// info
char gSurfName[256] = "";
char gSurfCredit[256] = "";
char gSurfX[256] = "";
char gSurfY[256] = "";
char gSurfZ[256] = "";
char gSurfRange[256] = "";

float simpleRGBColors[8][4] = {
  { 0.0f, 0.0f, 1.0f, 1.0f },
  { 0.0f, 1.0f, 0.0f, 1.0f },
  { 1.0f, 0.0f, 0.0f, 1.0f },
  { 1.0f, 1.0f, 0.0f, 1.0f },
  { 1.0f, 0.0f, 1.0f, 1.0f },
  { 0.0f, 1.0f, 1.0f, 1.0f },
  { 1.0f, 0.65f, 0.0f, 1.0f },
  { 0.64f, 0.80f, 0.35f, 1.0f }
};

const char* simpleRGBNames[8] = {
  "blue",
  "green",
  "red",
  "yellow",
  "magenta",
  "cyan",
  "orange",
  "darkolivegreen3"
};

int simpleRGBShuffle[8] = { 3, 7, 1, 4, 2, 6, 0, 5 };


void setColor( double c[3] ){
  static int i = 0;
  vcopy(c, simpleRGBColors[i], float);
  i = (i + 1) % 8;
}
void setColorX( float c[3] ){
	//recColor c = {1.0,1.0,1.0};
  c[0] = 1.0;
  c[1] = 1.0;
  c[2] = 1.0;
	static char toggle = 0;
  if(toggle){
    // blue
    c[0] = 0.0;
    c[1] = 0.0;
    c[2] = 1.0;
  }else{
    // orange
    c[0] = 0.8f;
    c[1] = 0.6f;
    c[2] = 0.0f;
  }
  toggle = !toggle;
}

void normalise( double p[3] ){
   double length;
  length = sqrt(p[X] * p[X] + p[Y] * p[Y] + p[Z] * p[Z]);
   if (length != 0) {
      p[X] /= length;
      p[Y] /= length;
      p[Z] /= length;
   } else {
      p[X] = 0;
      p[Y] = 0;
      p[Z] = 0;
   }
}

void CalcNormal( double p[3], double p1[3], double p2[3], double n[3] ){
  double pa[3],pb[3];

  pa[X] = p1[X] - p[X];
  pa[Y] = p1[Y] - p[Y];
  pa[Z] = p1[Z] - p[Z];
  pb[X] = p2[X] - p[X];
  pb[Y] = p2[Y] - p[Y];
  pb[Z] = p2[Z] - p[Z];
  normalise(pa);
  normalise(pb);

  n[X] = pa[Y] * pb[Z] - pa[Z] * pb[Y];
  n[Y] = pa[Z] * pb[X] - pa[X] * pb[Z];
  n[Z] = pa[X] * pb[Y] - pa[Y] * pb[X];
  normalise(n);
}

// expects u & v (-PI to PI)
void Eval(double u, double v, int type, double p[3] ){
	double temp;
	switch( type ){
		case kTranguloidTrefoil:
			p[X] = sin( 3*u ) * 2 / (2 + cos( v ));
			p[Y] = (sin( u ) + 2 * sin( 2*u )) * 2 / (2 + cos( v + TWOPI / 3 ));
			p[Z] = (cos( u ) - 2 * cos( 2*u )) * (2 + cos( v )) * (2 + cos( v + TWOPI/3 ))/4;
		break;
		case kTriaxialTritorus:
			p[X] = 2.0 * sin( u ) * (1 + cos( v ));
			p[Y] = 2.0 * sin( u + 2 * PI / 3 ) * (1 + cos( v + 2 * PI / 3 ));
			p[Z] = 2.0 * sin( u + 4 * PI / 3 ) * (1 + cos( v + 4 * PI / 3 ));
		break;
		case kStilettoSurface:
			// reverse u and v for better distribution or points
			temp = u;
			u = v + PI;
			// convert to: 0 <= u <= 2 pi, 0 <= v <= 2 pi 
			v = (temp + PI) / 2.0;
			p[X] = 4.0 *  (2.0 + cos( u )) * pow(cos( v ), 3.0) * sin( v );
			p[Y] = 4.0 *  (2.0 + cos( u+TWOPI/3.0 )) * pow( cos( v+TWOPI/3.0 ), 2.0 ) * pow( sin( v+TWOPI/3.0 ), 2.0 );
			p[Z] = 4.0 * -(2.0 + cos( u-TWOPI/3.0 )) * pow( cos( v+TWOPI/3.0 ), 2.0 ) * pow( sin( v+TWOPI/3.0 ), 2.0 );
 		break;
		case kSlippersSurface:
			temp = u;
			u = v + PI * 2;
			// convert to: 0 <= u <= 4 pi, 0 <= v <= 2 pi 
			v = temp + PI;
			p[X] = 4.0 *  (2 + cos( u )) * pow( cos( v ), 3 ) * sin( v );
			p[Y] = 4.0 *  (2 + cos( u + TWOPI / 3 )) * pow( cos( TWOPI / 3 + v ), 2) * pow( sin( TWOPI / 3 + v ), 2 );
			p[Z] = 4.0 * -(2 + cos( u - TWOPI / 3 )) * pow( cos( TWOPI / 3 - v ), 2 ) * pow( sin( TWOPI / 3 - v ), 3 );
		break;
		case kMaedersOwl:
		// convert to: 0 <= u <= 4 pi, 0 <= v <= 1 
			u = (u + PI) * 2;
			v = (v + PI) / TWOPI;
			p[X] = 3.0 *  v * cos( u ) - 0.5 * v * v * cos( 2 * u );
			p[Y] = 3.0 * -v * sin( u ) - 0.5 * v * v * sin( 2 * u );
			p[Z] = 3.0 *  4 * pow( v, 1.5 ) * cos( 1.5 * u ) / 3;
		break;
		default:
			p[X] = 0.0;
			p[Y] = 0.0;
			p[Z] = 0.0;
		break;
 	}
}

void GetStrings( unsigned int surface, char ** strName, char ** strAuthor,
								 char ** strX, char ** strY, char ** strZ, char ** strRange ){
	static char strings[6][6][256] = {{"Color Cube", 
									   " ", 
									   " ", 
									   " ", 
									   " ", 
									   " "},
									  {"Tranguloid Trefoil", 
									   "by Roger Bagula", 
									   "x = 2 sin(3 u) / (2 + cos(v))", 
									   "y = 2 (sin(u) + 2 sin(2 u)) / (2 + cos(v + 2 pi / 3))", 
									   "z = (cos(u) - 2 cos(2 u)) (2 + cos(v)) (2 + cos(v + 2 pi / 3)) / 4", 
									   "-pi <= u <= pi, -pi <= v <= pi"},
									  {"Triaxial Tritorus", 
									   "by Roger Bagula", 
									   "x = sin(u) (1 + cos(v))", 
									   "y = sin(u + 2pi / 3) (1 + cos(v + 2pi / 3))", 
									   "z = z = sin(u + 4pi / 3) (1 + cos(v + 4pi / 3))", 
									   "0 <= u <= 2 pi, 0 <= v <= 2 pi"},
									  {"Stiletto Surface", 
									   "by Roger Bagula", 
									   "x =  (2 + cos(u)) cos(v)^3 sin(v)", 
									   "y =  (2 + cos(u + 2pi /3)) cos(v + 2pi / 3)^2 sin(v + 2pi / 3)^2", 
									   "z = -(2 + cos(u - 2pi / 3)) cos(v + 2pi / 3)^2 sin(v + 2pi / 3)^2", 
									   "0 <= u <= 2 pi, 0 <= v <= 2 pi"},
									  {"Slippers Surface", 
									   "by Roger Bagula", 
									   "x =  (2 + cos(u)) cos(v)^3 sin(v)", 
									   "y =  (2 + cos(u + 2pi / 3)) cos(2pi / 3 + v)^2 sin(2pi / 3 + v)^2", 
									   "z = -(2 + cos(u - 2pi / 3)) cos(2pi / 3 - v)^2 sin(2pi / 3 - v)^3", 
									   "0 <= u <= 2 pi, 0 <= v <= 2 pi"},
									  {"Maeder's Owl", 
									   "by R. Maeder", 
									   "x = v cos(u) - 0.5 v^2 cos(2 u)", 
									   "y = - v sin(u) - 0.5 v^2 sin(2 u)", 
									   "z = 4 v^1.5 cos(3 u / 2) / 3", 
									   "0 <= u <= 4 pi, 0 <= v <= 1"}};
	*strName = strings[surface][0];
	*strAuthor = strings[surface][1];
	*strX = strings[surface][2];
	*strY = strings[surface][3];
	*strZ = strings[surface][4];
	*strRange = strings[surface][5];
}

// Cube is a special case
SGFaceList* BuildCube( ){
  float cube_vertices[8][3] = {
  {1.0, 1.0, 1.0}, {1.0, -1.0, 1.0}, {-1.0, -1.0, 1.0}, {-1.0, 1.0, 1.0},
  {1.0, 1.0, -1.0}, {1.0, -1.0, -1.0}, {-1.0, -1.0, -1.0}, {-1.0, 1.0, -1.0}};
  
  float cube_vertex_colors [8][3] = {
  {1.0, 1.0, 1.0}, {1.0, 1.0, 0.0}, {0.0, 1.0, 0.0}, {0.0, 1.0, 1.0},
  {1.0, 0.0, 1.0}, {1.0, 0.0, 0.0}, {0.0, 0.0, 0.0}, {0.0, 0.0, 1.0} };
  
  int cube_faces[12][3] = {
  {3, 2, 0}, {2, 1, 0}, {2, 3, 7}, {6,2, 7}, {0, 1, 5}, {5, 4, 0}, {3, 0, 4}, {3, 4, 7}, {1, 2, 6}, {1, 6, 5}, {4, 5, 6}, {4, 6, 7} };
  
  SGFaceList *f;
	int i, j;
  
  for( i = 0; i < 8; i++ ){
    for( j = 0; j < 3; j++ ){
      cube_vertices[i][j] *= 2.0;
    }
  }
  
  f = new SGFaceList( 8, 12, kCube, 0, 0 );
  
  for( i = 0; i < f->fc; i++ ){
		vcopy( f->faces[i], cube_faces[i], int );
  }

  for( i = 0; i < f->vc; i++ ){
		vcopy( f->v_normals[i], cube_vertices[i], float );
		vcopy( f->vertices[i], cube_vertices[i], float );
		vcopy( f->colors[i], cube_vertex_colors[i], float );
  }
  return( f );
}

SGFaceList* BuildGeometry( unsigned int surface, unsigned int colorScheme,
												 unsigned int subdivisions, unsigned int xyRatio ){
	long i,j, index;
	long maxI = subdivisions * xyRatio, maxJ = subdivisions;
	double u, v, delta=0.001;
	double p1[3];
  double p2[3];
  double p[3];
  double q[3];
  SGFaceList *f;

	// set valid surface and color scheme
	surface %= kSurfaces;
	colorScheme %= kColorSchemes;	

	if( surface == kCube ){
    // build the standard color cube (disregard color, subdivisions, and xyRatio)
		f = BuildCube( );
	}else{
    // init the FaceList
    f = new SGFaceList( (maxI*maxJ), 1, surface, maxI, maxJ );

		// build surface
		for (i = 0; i < maxI; i++) {
			for (j = 0; j < maxJ; j++) {
				index = i * maxJ + j;
				u  = -PI + (i % maxI) * TWOPI / maxI;
				v  = -PI + (j % maxJ) * TWOPI / maxJ;

        Eval(u,v, surface, p);
				vcopy( f->vertices[index], p, float );

				Eval(u + delta, v, surface, p1);
				Eval(u, v + delta, surface, p2);

        CalcNormal( p, p1, p2, q );
				vcopy( f->v_normals[index], q, float );

        setColor( p );
				vcopy( f->colors[index], p, float );
			}
		}
	} // end else
  return( f );
}

