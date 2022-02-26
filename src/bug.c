#include "simple_logger.h"

#include "bug.h"

#define ES_DEAD 1

void bug_think(Entity* self)
{
    int mx, my;
    double distance;
    SDL_GetMouseState(&mx, &my);
    distance = sqrt(((mx - self->position.x) * (mx - self->position.x)) + ((my - self->position.y) * (my - self->position.y)));
   int intDistance = (int)distance;
   int speed = intDistance / 100;
   if (speed <= 2)speed = 2;
   //slog("Distance is: %i\n", intDistance);
    //vector2d_copy(self->position, vector2d(mx, my));

   self->velocity.x = (mx - self->position.x);
   self->velocity.y = (my - self->position.y);
   
   vector2d_normalize(&self->velocity);

   vector2d_set_magnitude(&self->velocity, speed);

   if (intDistance <= 10)
   {
       entity_free(self);
   }

   // self->velocity.x *= 3;
    //self->velocity.y *= 3;

    
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