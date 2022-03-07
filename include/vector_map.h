#ifndef __GF2D_VECTOR_MAP_H__
#define __GF2D_VECTOR_MAP_H__


#include "gfc_text.h"

#include "gf2d_sprite.h"


typedef struct VectorMap
{

	TextLine filename;
	Sprite *backgroundImage;
	char *testTest;
	//Can probably update these to be a Vector4D
	int *topLeftBound;
	int* topRightBound;
	int* bottomLeftBound;
	int* bottomRightBound;

	int *platformCount;

	//Need to update *platformCoords and use/rename *platformsMaybe[]
	//int *platformCoords;
	Vector2D* platformTEST;
	Vector4D* platformCoords;
	

}VectorMap;

VectorMap* vectormap_load(char* filename);
void vectormap_free(VectorMap* map);
void vectormap_draw(VectorMap* map);



#endif