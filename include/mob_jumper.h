#ifndef __MOB_JUMPER_H__
#define __MOB_JUMPER_H_

#include "entity.h"

Entity* jumper_new(Vector2D position, Vector2D velocity);

void jumper_think(Entity* self);

#endif
