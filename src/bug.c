#include "simple_logger.h"
#include "gf2d_draw.h"
#include "bug.h"

#define ES_DEAD 1

void bug_think(Entity* self)
{

    if (self->hitBox.y && self->knownPlatHeight) 
    {
        if (self->hitBox.y + self->hitBox.h > self->knownPlatHeight)
        {
            //slog("ERROR BROSKI");
        }
    }
    
    int mx, my;
    double distance;
   
    if (self->movementLock == 1) self->velocity.x = 0;
    else self->velocity.x = gfc_random() * 2 - 1;

  
    

   self->hitBox.x = self->position.x - 32;
   self->hitBox.y = self->position.y - 32;
   self->hitBox.w = 64;
   self->hitBox.h = 64;

   gf2d_draw_rect(self->hitBox, vector4d(78, 250, 29, 255));

  
   //dont let it fall through platform
   if (self->standingOnPlatform == 1 && self->velocity.y > 0)
   {
       self->velocity.y = 0;
   }

  // if (intDistance <= 10)
   //{
      // entity_free(self);
   //}

}



Entity* bug_new(Vector2D position, Vector2D velocity)
{
    Entity* self;
    self = entity_new();
    if (!self)return NULL;
    self->sprite = gf2d_sprite_load_all(
        "images/space_bug_top.png",
        128,
        128,
        16);
    self->radius = 24;
    self->size.x = 32;
    self->size.y = 32;
    self->team = 2;
    self->maxHealth = 100;
    self->health = self->maxHealth;
    self->spawnMobNumber = 1;
    self->think = bug_think;
  

    vector2d_copy(self->position, position);
    vector2d_copy(self->velocity, velocity);
    vector2d_set(self->drawOffset, -64, -78);
    return self;
}