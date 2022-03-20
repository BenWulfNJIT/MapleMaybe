#ifndef __MOB_MAN_H__
#define __MOB_MAN_H_

#include "entity.h"

Entity* man_new(Vector2D position, Vector2D velocity);

void man_think(Entity* self, VectorMap* map);

#endif
