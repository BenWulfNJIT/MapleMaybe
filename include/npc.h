#ifndef __NPC_H__
#define __NPC_H__


#include "entity.h"

Entity* npc_new(Vector2D position);

void npc_think(Entity* self);


#endif