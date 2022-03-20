#include <stdlib.h>
#include "simple_logger.h"
#include "gf2d_draw.h"
#include "entity.h"
#include "physics.h"
#include "vector_map.h"
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
    for (i = 0; i < entity_manager.maxEnts; i++)
    {
        if (!entity_manager.entityList[i]._inuse)continue;
        if (entity_manager.entityList[i].think)
        {
            entity_manager.entityList[i].think(&entity_manager.entityList[i]);
        }
        entity_update(&entity_manager.entityList[i]);
        //slog("Entity count: %i", i);
    }
}

void skillCollisionCheck(SDL_Rect* skillHitBox)
{
    
    int i;
    for (i = 0; i < entity_manager.maxEnts; i++)
    {

        if (!entity_manager.entityList[i]._inuse)continue;
        if (entity_manager.entityList[i].think)
        {
           // slog("so %i", &entity_manager.entityList[i].hitBox.x);

            entity_manager.entityList[i].think(&entity_manager.entityList[i]);
            
        }
        //working
        //if ( skillHitBox->x+skillHitBox->w >= entity_manager.entityList[i].hitBox.x && skillHitBox->x <= (entity_manager.entityList[i].hitBox.x + entity_manager.entityList[i].hitBox.w) && entity_manager.entityList[i].team == 2)
        if(SDL_HasIntersection(skillHitBox, &entity_manager.entityList[i].hitBox))
        {
            slog("Colliding");
        }
        else
        {
            //slog("nerrr");
        }
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

   // gf2d_draw_rect(rect, vector4d(255, 0, 255, 255));

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

void entity_draw_all()
{
    int i;
    for (i = 0; i < entity_manager.maxEnts; i++)
    {
        if (!entity_manager.entityList[i]._inuse)continue;
        entity_draw(&entity_manager.entityList[i]);
    }
}



/*eol@eof*/