#include "simple_logger.h"
#include "simple_json.h"
#include "vector_map.h"
#include "spawn.h"

Entity* spawner_new(Entity* entityToSpawn, Vector2D position, int frequency)
{

    Entity* self;
    self = entity_new();
    if (!self)return NULL;
   // self->entityToSpawn = entityToSpawn;
    self->positionToSpawn = position;
    self->frequencyToSpawn = frequency;

    return self;
}

void GetSpawnList(VectorMap* map, Entity* spawner)
{
    SJson *json;

}

