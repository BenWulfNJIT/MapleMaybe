#ifndef __MOB_TURRET_H__
#define __MOB_TURRET_H_

#include "entity.h"

Entity* turret_new(Vector2D position, Vector2D velocity);

void turret_think(Entity* self, VectorMap* map);

#endif
