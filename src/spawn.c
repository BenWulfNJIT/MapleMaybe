#include "simple_logger.h"
#include "simple_json.h"
#include "gf2d_draw.h"

#include "vector_map.h"
#include "spawn.h"
#include "bug.h"




Entity* spawner_new(int entityToSpawn, Vector2D position, int maxSpawn, int frequency)
{

    Entity* self;
    //Entity* spawnList;
    self = entity_new();
    if (!self)return NULL;
   // self->entityToSpawn = entityToSpawn;
    self->positionToSpawn = position;
    self->frequencyToSpawn = frequency;
    self->currentSpawnTime = 0;
    self->spawnMobNumber = entityToSpawn;
    self->spawnMax = maxSpawn;
    self->spawnCount = 0;
    //spawnList = (Entity*)gfc_allocate_array(sizeof(Entity), 100);

    return self;
}

void SpawnerThink(Entity* spawner, Entity* spawnList)
{
    int numToSpawn, currentNum;
    Entity* tempEnt;

    for (int i = 0; i < spawner->spawnCount; i++)
    {
        //slog("GGG");
        //spawnList[i].velocity.x = gfc_random()*2 -1;
        //log("hm %f", spawnList->velocity.x);
        //entity_update(&spawnList[i]);
        //entity_update_all();
        entity_draw_all();
        
    }

    if (spawner->spawnCount >= spawner->spawnMax)
    {
        //slog("test %i", spawner->spawnCount);

        spawner->currentSpawnTime = spawner->frequencyToSpawn;
        return;
    }
    else if(spawner->currentSpawnTime <= 0 && spawner->spawnCount < spawner->spawnMax)
    {
        //take the difference between max and count, and spawn that many, then reset spawn timer
        numToSpawn = spawner->spawnMax - spawner->spawnCount;
        for (int i = 0; i < numToSpawn; i++)
        {
            switch (spawner->spawnMobNumber)
            {
            case 1 :
                //bug spawner
                //tempEnt = bug_new(spawner->positionToSpawn, vector2d(0, 0));
                spawnList[spawner->spawnCount] = *bug_new(spawner->positionToSpawn, vector2d(20, 0));
                //spawner->spawnList[1] = tempEnt;
                //temp->think;
                spawner->spawnCount++;
                return;
            default:
                //should not default
                slog("Error: invalid mob spawn ID");
                return;
            }
           
                
        }
    }
    else if (spawner->currentSpawnTime > 0)
    {
        spawner->currentSpawnTime--;
    }
    else
    {
        slog("idk how i got here, error?");
    }
}


