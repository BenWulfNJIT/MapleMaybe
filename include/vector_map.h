#ifndef __GF2D_VECTOR_MAP_H__
#define __GF2D_VECTOR_MAP_H__


#include "gfc_text.h"

#include "gf2d_sprite.h"


typedef struct VectorMap
{

	TextLine filename;
	Sprite *backgroundImage;
	char *testTest;
	int *topLeftBound;
	int* topRightBound;
	int* bottomLeftBound;
	int* bottomRightBound;
	int *platformCount;
	int *platformCoords;
	

}VectorMap;

VectorMap* vectormap_load(char* filename);
void vectormap_free(VectorMap* map);
void vectormap_draw(VectorMap* map);



#endif