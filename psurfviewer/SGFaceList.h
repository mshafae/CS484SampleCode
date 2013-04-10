
#ifndef _SGFACELIST_H_
#define _SGFACELIST_H_

#include <iostream>

enum{X = 0, Y, Z, W};

/*
 * Macro to allocate/free 2D arrays using C constructs
 */
#define msAlloc2D( type, varName, dim_x, dim_y ) \
{ \
	int __i; \
	if( !((varName) = (type**)calloc( (dim_x), sizeof(type*) )) ){ \
		fprintf( stderr, "Could not allocate memory." ); \
	} \
	for( __i = 0; __i < dim_x; __i++ ){ \
		if( !((varName)[__i] = (type*)calloc( (dim_y), sizeof(type) )) ){ \
		fprintf( stderr, "Could not allocate memory." ); \
		} \
	} \
}

#define msFree2D( varName, dim_x, dim_y ) \
{ \
	int __i; \
	for( __i = 0; __i < dim_x; __i++ ){ \
		free( varName[__i] ); \
	} \
	free( varName ); \
}


/*
 * I have usesd arrays for the vertices, colors, normals, and faces
 * but that does not mean that if you have a Vector class that you can not
 * revise this code to use your Vector class.
 *
 * Add methods to this class as you see fit. If the need arises, create
 * a SGFaceList.cpp
 */

class SGFaceList{
public:
  // surface enum
  int surface;
  // # of samples
  int maxI;
  int maxJ;
  // array of vertices
  float **vertices;
  //array of vertex colors
  float **colors;
  // array of face indices
  int **faces;
  // vertex count
  int vc;
  // face count
  int fc;
  // The face's surface normal
  float **f_normals;
  float **v_normals;
  
  SGFaceList( int vertexCount, int faceCount, int s, int mi, int mj ){
    vc = vertexCount;
    fc = faceCount;
    surface = s;
    
    maxI = mi;
    maxJ = mj;

		msAlloc2D( float, vertices, vc, 3 );
    
		msAlloc2D( float, colors, vc, 3 );

		msAlloc2D( float, v_normals, vc, 3 );

		msAlloc2D( float, f_normals, fc, 3 );

		msAlloc2D( int, faces, fc, 3 );
  };
  
  ~SGFaceList( ){
		msFree2D( vertices, vc, 3 );
		msFree2D( v_normals, vc, 3 );
		msFree2D( f_normals, fc, 3 );
    msFree2D( faces, fc, 3 );
  };

  std::ostream& operator <<( std::ostream &out ){
    int i;
    out << "#Vertices" << std::endl;
    for( i = 0; i < vc; i++ ){
			out << vertices[i][X] << " " << vertices[i][Y] << vertices[i][Z] << std::endl;
    }
    out << "#Faces" << std::endl;
    for( i = 0; i < fc; i++ ){
			out << faces[i][X] << " " << faces[i][Y] << faces[i][Z] << std::endl;
    }
    return( out );
  }

};

#endif
