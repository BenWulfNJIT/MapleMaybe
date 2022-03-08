#include "simple_logger.h"

#include "bug.h"

#define ES_DEAD 1

void bug_think(Entity* self)
{

    if (self->hitBox.y && self->knownPlatHeight) 
    {
        if (self->hitBox.y + self->hitBox.h > self->knownPlatHeight)
        {
            slog("ERROR BROSKI");
        }
    }
    
    int mx, my;
    double distance;
    SDL_GetMouseState(&mx, &my);
    distance = sqrt(((mx - self->position.x) * (mx - self->position.x)) + ((my - self->position.y) * (my - self->position.y)));
   int intDistance = (int)distance;
   int speed = intDistance / 100;
   if (speed <= 2)speed = 2;

   self->velocity.x = (mx - self->position.x);
   self->velocity.y = (my - self->position.y);
   
   vector2d_normalize(&self->velocity);

   vector2d_set_magnitude(&self->velocity, speed);
  

   self->hitBox.x = self->position.x - 32;
   self->hitBox.y = self->position.y - 32;
   self->hitBox.w = 64;
   self->hitBox.h = 64;

  
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
    self->think = bug_think;
  

    vector2d_copy(self->position, position);
    vector2d_copy(self->velocity, velocity);
    vector2d_set(self->drawOffset, -64, -78);
    return self;
}