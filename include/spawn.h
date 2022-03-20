#ifndef __SPAWN_H__
#define __SPAWN_H__

#include "entity.h"




Entity* spawner_new(int entityToSpawn, Vector2D position, int maxSpawn, int frequency);

void GetSpawnList(VectorMap* map, Entity* spawner);

void SpawnerThink(Entity* spawner, Entity* spawnList);

#endif
