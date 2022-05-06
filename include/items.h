#ifndef __ITEMS_H__
#define __ITEMS_H__
#include "entity.h"

Entity* NewItem(Vector2D position, int ItemID); /**1 mirror, 2 bfs, 3 sneaks, 4 regen, 5 flamecloak*/

void ItemThink(Entity* self);

#endif