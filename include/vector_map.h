#ifndef __GF2D_VECTOR_MAP_H__
#define __GF2D_VECTOR_MAP_H__


#include "gfc_text.h"

#include "gf2d_sprite.h"
#include "entity.h"

typedef struct VectorMap
{

	TextLine	filename;
	Sprite*		backgroundImage;
	char*		testTest;
	SDL_Rect	boundingBox;
	int			platformCount;
	Vector4D*	platformCoords;
	Vector2D*	spawnerCoords;
	Vector3D*	spawnerInfo;
	int			spawnerCount;
	int			mapID;

	struct Entity*		spawners;

	

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