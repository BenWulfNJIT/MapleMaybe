#ifndef __SPAWN_H__
#define __SPAWN_H__

#include "entity.h"



Entity* spawner_new(Entity* entityToSpawn, Vector2D position, int frequency);

void GetSpawnList(VectorMap* map, Entity* spawner);



#endif
