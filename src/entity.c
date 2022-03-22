#include <stdlib.h>
#include <time.h>
#include "simple_logger.h"
#include "gf2d_draw.h"
#include "entity.h"
#include "physics.h"
#include "vector_map.h"
#include "damage.h"
//#include "level.h"
//#include "collisions.h"

typedef struct
{
    Uint32 maxEnts;     /**<max entities supported by the system*/
    Entity* entityList; /**<pointer to an allocated array of entities*/
}EntityManager;

static EntityManager entity_manager = { 0 };


//void entity_collide_check(Entity* entity);

void entity_manager_close()
{
    int i;
    for (i = 0; i < entity_manager.maxEnts; i++)
    {
        if (entity_manager.entityList[i]._inuse)
        {
            entity_free(&entity_manager.entityList[i]);
        }
    }
    entity_manager.maxEnts = 0;
    free(entity_manager.entityList);
    entity_manager.entityList = NULL;
    slog("entity manager closed");
}

void entity_manager_init(Uint32 maxEnts)
{
    if (entity_manager.entityList != NULL)
    {
        //TODO: cleanup
    }
    if (!maxEnts)
    {
        slog("cannot intialize a zero size entity list!");
        return;
    }
    entity_manager.entityList = (Entity*)malloc(sizeof(Entity) * maxEnts);
    if (entity_manager.entityList == NULL)
    {
        slog("failed to allocate %i entities for the entity manager", maxEnts);
        return;
    }
    entity_manager.maxEnts = maxEnts;
    memset(entity_manager.entityList, 0, sizeof(Entity) * maxEnts);
    slog("entity manager initialized");
    atexit(entity_manager_close);
}


Entity* entity_new()
{
    int i;
    for (i = 0; i < entity_manager.maxEnts; i++)
    {
        if (entity_manager.entityList[i]._inuse)continue;
        entity_manager.entityList[i]._inuse = 1;
        return &entity_manager.entityList[i];
    }
    slog("out of open entity slots in memory!");
    return NULL;
}


void entity_free(Entity* self)
{
    if (!self)return;
    gf2d_sprite_free(self->sprite);
    memset(self, 0, sizeof(Entity));
}

void entity_update(Entity* self)
{
    Vector2D normal = { 0,0 };
    if (!self)return;

    //comment

    vector2d_add(self->position, self->position, self->velocity);
    //SimplePlatformCollision(self, map);
    //BoundingBoxCollision(self, map);
    //DoPlayerGravity(self);
  
}

void entity_update_all()
{
    int i;
    int bugCount = 0;
    int manCount = 0;
    int jumperCount = 0;
    int rollerCount = 0;
    int turretCount = 0;

    int playerPos = 0;
    for (i = 0; i < entity_manager.maxEnts; i++)
    {
        if (!entity_manager.entityList[i]._inuse)continue;
        if (entity_manager.entityList[i].think)
        {
            if (entity_manager.entityList[i].team == 1)
            {
                playerPos = i;
            }
            //slog("hmmm %i", entity_manager.entityList[i].spawnMobNumber);
            if (entity_manager.entityList[i].spawnMobNumber == 1) bugCount++;
            entity_manager.entityList[playerPos].spawnBugCount = bugCount;

            if (entity_manager.entityList[i].spawnMobNumber == 2) manCount++;
            entity_manager.entityList[playerPos].spawnManCount = manCount;

            if (entity_manager.entityList[i].spawnMobNumber == 3) jumperCount++;
            entity_manager.entityList[playerPos].spawnJumperCount = jumperCount;

            if (entity_manager.entityList[i].spawnMobNumber == 4) rollerCount++;
            entity_manager.entityList[playerPos].spawnRollerCount = rollerCount;

            if (entity_manager.entityList[i].spawnMobNumber == 5) turretCount++;
            entity_manager.entityList[playerPos].spawnTurretCount = turretCount;


            

            entity_manager.entityList[i].think(&entity_manager.entityList[i]);
        }
        //DoPlayerGravity(&entity_manager.entityList[i]);
        entity_update(&entity_manager.entityList[i]);

        //slog("Entity count: %i", i);
    }
}

void SkillCollisionCheck(Entity* attacker, int skill, SDL_Rect* skillHitBox)
{
    
    int i;
    for (i = 0; i < entity_manager.maxEnts; i++)
    {

        if (!entity_manager.entityList[i]._inuse)continue;
        if (entity_manager.entityList[i].think)
        {
           // slog("so %i", &entity_manager.entityList[i].hitBox.x);
            //slog("huh");
           
            if (SDL_HasIntersection(skillHitBox, &entity_manager.entityList[i].hitBox) && entity_manager.entityList[i].team == 2)
            //slog("skill.x %i ent.x %i", skillHitBox->x, entity_manager.entityList[i].hitBox.x);
           // if(skillHitBox->x + skillHitBox->w >= &entity_manager.entityList[i].hitBox.x &&
             //   skillHitBox->x <= &entity_manager.entityList[i].hitBox.x + entity_manager.entityList[i].hitBox.w 
                //skillHitBox->y + skillHitBox->h >= &entity_manager.entityList[i].hitBox.y &&
                //skillHitBox->y <= &entity_manager.entityList[i].hitBox.y + entity_manager.entityList[i].hitBox.h)
           //     )
            {
                //slog("after intersection");
                //slog("damage: %i", GetDamage(skill));
                //slog("should inflict");
                InflictDamage(attacker, &entity_manager.entityList[i], GetDamage(skill));
                //slog("Colliding");
                
            }
            else
            {
                //slog("nerrr");
                entity_manager.entityList[i].think(&entity_manager.entityList[i]);

            }
          
        }
        //working
        //if ( skillHitBox->x+skillHitBox->w >= entity_manager.entityList[i].hitBox.x && skillHitBox->x <= (entity_manager.entityList[i].hitBox.x + entity_manager.entityList[i].hitBox.w) && entity_manager.entityList[i].team == 2)
      
    }
}

void entity_draw(Entity* self)
{
    SDL_Rect rect;
    if (self == NULL)
    {
        slog("cannot draw sprite, NULL entity provided!");
        return;
    }
    gf2d_sprite_draw(
        self->sprite,
        vector2d(self->position.x + self->drawOffset.x, self->position.y + self->drawOffset.y),
        NULL,
        NULL,
        NULL,
        NULL,
        NULL,
        (Uint32)self->frame);
    
    gfc_rect_set(rect,self->position.x,self->position.y,self->size.x,self->size.y);

   // //gf2d_draw_rect(rect, vector4d(255, 0, 255, 255));

}
//
//void entity_entity_collide(Entity* e1, Entity* e2)
//{
//    if (collide_circle(e1->position, e1->radius, e2->position, e2->radius))
//    {
//        if (e1->touch)
//        {
//            e1->touch(e1, e2);
//        }
//    }
//}
//
//void entity_collide_check(Entity* entity)
//{
//    int i;
//    if (!entity)return;
//    for (i = 0; i < entity_manager.maxEnts; i++)
//    {
//        if (!entity_manager.entityList[i]._inuse)continue;
//        if (&entity_manager.entityList[i] == entity)continue;
//        entity_entity_collide(entity, &entity_manager.entityList[i]);
//    }
//}

Entity* GetPlayer()
{
    Entity* player = NULL;
    for (int i = 0; i < entity_manager.maxEnts; i++)
    {
        if (!entity_manager.entityList[i]._inuse)continue;
        if (entity_manager.entityList[i].think)
        {
            if (entity_manager.entityList[i].team == 1)
            {
                player = &entity_manager.entityList[i];
            }
        }
    }
    //if (player) return player;
   // else return NULL;
    return player;
}

Entity* GetNearestMob(Entity* self) 
{
    ///Entity* player = NULL;
    Entity* nearest = NULL;
    Vector2D tempCoords = { 0,0 };
    float tempDistance, smallestDistance;
    smallestDistance = 999999999;
    //player = GetPlayer();

    for (int i = 0; i < entity_manager.maxEnts; i++)
    {

        if (!entity_manager.entityList[i]._inuse)continue;
        if (entity_manager.entityList[i].team == -1)continue;

        if (entity_manager.entityList[i].think)
        {
            if (entity_manager.entityList[i].team == 2);
            {
                tempCoords.x = entity_manager.entityList[i].position.x;
                tempCoords.y = entity_manager.entityList[i].position.y;

                //slog("x: %f, y: %f", tempCoords.x, tempCoords.y);
                //slog("woah %f", player->position.x);
                tempDistance = (((tempCoords.x - self->position.x) * (tempCoords.x - self->position.x)) + ((tempCoords.y - self->position.y) * (tempCoords.y - self->position.y)));
                //slog("temp %f", tempDistance);
                if (tempDistance < smallestDistance && tempDistance != 0 && &entity_manager.entityList[i].team != 1)
                {
                    smallestDistance = tempDistance;
                    nearest = &entity_manager.entityList[i];
                    //slog("maybe? %f", smallestDistance);
                }


            }
        }
    }

    //nearest = GetPlayer();
    return nearest;

}

void DoVacuum(Vector2D location)
{
    Vector2D direction;
    Entity* player = GetPlayer();

    for (int i = 0; i < entity_manager.maxEnts; i++)
    {

        if (!entity_manager.entityList[i]._inuse)continue;
        if (entity_manager.entityList[i].team == 1)continue;
        if (entity_manager.entityList[i].team == -1)continue;

        if (entity_manager.entityList[i].think)
        {
            if (entity_manager.entityList[i].team == 2);
            {
                
                vector2d_sub(direction, location, entity_manager.entityList[i].position);
                vector2d_normalize(&direction);
                vector2d_set_magnitude(&direction, 20);

                entity_manager.entityList[i].velocity = direction;

                InflictDamage(player, &entity_manager.entityList[i], 1);
                
            }
        }
    }
}

void SetCarried(Entity* carrier)
{
    for (int i = 0; i < entity_manager.maxEnts; i++)
    {

        if (!entity_manager.entityList[i]._inuse)continue;
        if (entity_manager.entityList[i].team == 1)continue;
        if (entity_manager.entityList[i].think)
        {
            if (entity_manager.entityList[i].team == 2);
            {

                if (SDL_HasIntersection(&carrier->hitBox, &entity_manager.entityList[i].hitBox))
                {
                    entity_manager.entityList[i].carried = 1;
                    carrier->damageBoostTime = 60;
                }

            }
        }
    }
}
void ReleaseAllCarried()
{
    for (int i = 0; i < entity_manager.maxEnts; i++)
    {

        if (!entity_manager.entityList[i]._inuse)continue;
        if (entity_manager.entityList[i].team == 1)continue;
        if (entity_manager.entityList[i].team == -1)continue;

        if (entity_manager.entityList[i].think)
        {
            if (entity_manager.entityList[i].team == 2);
            {

                if (entity_manager.entityList[i].carried == 1) 
                {
                       
                    InflictDamage(GetPlayer(), &entity_manager.entityList[i], 500);
                }
                  


            }
        }
    }
}

Entity* GetRandomMob()
{
    int flag = 0;
    int monsterCounter = 0;
    srand(time(0));

    for (int i = 0; i < entity_manager.maxEnts; i++)
    {

        if (!entity_manager.entityList[i]._inuse)continue;
        if (entity_manager.entityList[i].team == -1)continue;

        if (entity_manager.entityList[i].think)
        {
            if (entity_manager.entityList[i].team == 2);
            {
                //temporary
                //entity_manager.entityList[i].position.x = 400;
                //entity_manager.entityList[i].position.y = 400;

                monsterCounter++;
            }
        }
    }

    if (monsterCounter > 2)
    {
        while (flag == 0)
        {
            int num = (rand() % ((entity_manager.maxEnts) - 0 + 1)) + 0;
            if (entity_manager.entityList[num].team == 2)
            {
                flag == 1;
                return &entity_manager.entityList[num];
            }
        }
    }

    return NULL;
}


void entity_draw_all()
{
    int i;
    for (i = 0; i < entity_manager.maxEnts; i++)
    {
        if (!entity_manager.entityList[i]._inuse)continue;
        entity_draw(&entity_manager.entityList[i]);
        ////gf2d_draw_rect(entity_manager.entityList[i].hitBox, vector4d(78, 250, 29, 255));
    }
}

void DamageBoost(Entity* ent, int time)
{
    if (ent->damageBoostTime) ent->damageBoostTime = time;
}


/*eol@eof*/