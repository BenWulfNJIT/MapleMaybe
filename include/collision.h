#ifndef __GF2D_COLLISION_H__
#define __GF2D_COLLISION_H__

#include "entity.h"
#include "vector_map.h"


/**
* @brief checks for a possible platform below the entity, and prevents them from falling through it
* @param ent the entity you want to check
* @param map the current map in use
*/
void SimplePlatformCollision(Entity* ent, VectorMap* map);
void BoundingBoxCollision(Entity* ent, VectorMap* map);




#endif
