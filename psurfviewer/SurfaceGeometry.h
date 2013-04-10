
#include "SGFaceList.h"

#ifndef _SURFACEGEOMETRY_H_
#define _SURFACEGEOMETRY_H_

#define kSurfaces 6
#define kColorSchemes 21

enum {
	kCube = 0,
	kTranguloidTrefoil,
	kTriaxialTritorus,
	kStilettoSurface,
	kSlippersSurface,
	kMaedersOwl
};

void GetStrings( unsigned int surface, char ** strName, char ** strAuthor,
                 char ** strX, char ** strY, char ** strZ, char ** strRange );

SGFaceList* BuildGeometry( unsigned int surface, unsigned int colorScheme,
												 unsigned int subdivisions, unsigned int xyRatio );



#endif

