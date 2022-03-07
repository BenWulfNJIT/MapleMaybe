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

/*
 * @brief loads a VectorMap with data from the corresponding json
 * @param filename to load
 */
VectorMap* vectormap_load(char* filename);

/*
 * @brief frees a VectorMap 
 * @param filename of map to free
 */
void vectormap_free(VectorMap* map);

/*
 * @brief draws the VectorMap
 * @param filename to draw
 */
void vectormap_draw(VectorMap* map);



#endif