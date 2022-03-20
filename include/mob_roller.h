#ifndef __MOB_ROLLER_H__
#define __MOB_ROLLER_H_

#include "entity.h"

Entity* roller_new(Vector2D position, Vector2D velocity);

void roller_think(Entity* self, VectorMap* map);

#endif
