#include "simple_logger.h"
#include "simple_json.h"
#include "gf2d_draw.h"

#include "vector_map.h"
#include "spawn.h"
#include "bug.h"
#include "collision.h"
#include "mob_man.h"
#include "mob_jumper.h"
#include "mob_roller.h"
#include "mob_turret.h"




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

            switch (spawner->spawnMobNumber)
            {
            case 1 :
                bug_think(&spawnList[i], map);
                break;
            case 2:
                man_think(&spawnList[i], map);
                break;
            case 3:
                jumper_think(&spawnList[i], map);
                break;
            case 4:
                roller_think(&spawnList[i], map);
                break;
            case 5:
                turret_think(&spawnList[i], map);
                break;
            }
            entity_draw_all();

           

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
                spawnList[spawner->spawnCount] = *bug_new(spawner->positionToSpawn, vector2d(20, 0));
                spawner->spawnCount++;
                return;
            case 2:
                spawnList[spawner->spawnCount] = *man_new(spawner->positionToSpawn, vector2d(20, 0));
                spawner->spawnCount++;
                return;
            case 3:
                spawnList[spawner->spawnCount] = *jumper_new(spawner->positionToSpawn, vector2d(20, 0));
                spawner->spawnCount++;
                return;
            case 4:
                spawnList[spawner->spawnCount] = *roller_new(spawner->positionToSpawn, vector2d(20, 0));
                spawner->spawnCount++;
                return;
            case 5:
                spawnList[spawner->spawnCount] = *turret_new(spawner->positionToSpawn, vector2d(20, 0));
                //slog("spawned");
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


