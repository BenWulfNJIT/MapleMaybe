#include "simple_logger.h"
#include "simple_json.h"
#include "gf2d_draw.h"

#include "vector_map.h"
#include "spawn.h"
#include "bug.h"
#include "collision.h"




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

void SpawnerThink(Entity* spawner, Entity* spawnList, VectorMap* map)
{
    int numToSpawn, currentNum;
    Entity* tempEnt;

    if (spawner->spawnCount != 0)
    {
        for (int i = 0; i < spawner->spawnCount; i++)
        {
           
            //slog("%i", spawner->spawnCount);
            //slog("test %i", spawnList[i].health);
            bug_think(&spawnList[i]);
            entity_draw_all();

            gf2d_draw_rect(spawnList[i].hitBox, vector4d(78, 250, 29, 255));

            SimplePlatformCollision(&spawnList[i], map);
            BoundingBoxCollision(&spawnList[i], map);
            DoPlayerGravity(&spawnList[i]);

        }
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
                
                //slog("uh %i", spawner->spawnCount);
                //slog("test %f", spawnList[spawner->spawnCount].position.x);
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


