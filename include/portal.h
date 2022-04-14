#ifndef __PORTAL_H__
#define __PORTAL_H__

#include "entity.h"
#include "vector_map.h"
Entity* portal_new(Vector2D position, int selfMapID, int mapIDToTeleport);

void portal_think(Entity* self, VectorMap* map);

void ChangeMap(VectorMap* map, int mapID);


#endif