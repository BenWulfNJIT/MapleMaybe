#ifndef __SHOP_H__
#define __SHOP_H__


#include "entity.h"

Entity* shop_new(Vector2D position);

void shop_think(Entity* self);


#endif