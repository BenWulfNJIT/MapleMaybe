#include "simple_logger.h"
#include "gf2d_draw.h"
#include "bug.h"
#include "damage.h"

#define ES_DEAD 1

void bug_think(Entity* self)
{

    //if (self->hitBox.y && self->knownPlatHeight) 
   // {
      //  if (self->hitBox.y + self->hitBox.h > self->knownPlatHeight)
       // {
            //slog("ERROR BROSKI");
       // }
    //}
    
    Entity* player = GetPlayer();
    //Vector2D* playerPosition = &player->position;
    //gf2d_draw_line(self->position, player->position, vector4d(20, 20, 255, 255));
    //self->velocity.x = (gfc_random() -0.5) * 5;
    //self->velocity.y = (gfc_random() - 0.5) * 5;

    if (gfc_random() >= 0.8)
    {
        self->velocity.x = player->position.x - self->position.x;
        self->velocity.y = player->position.y - self->position.y;
        vector2d_normalize(&self->velocity);
        vector2d_set_magnitude(&self->velocity, 3);
    }
    else
    {
        self->velocity.x = (gfc_random() -0.5) * 7;
        self->velocity.y = (gfc_random() - 0.5) * 7;
    }

    if (SDL_HasIntersection(&self->hitBox, &player->hitBox))
    {
        InflictDamage(self, player, 10);
    }
        

  
    

   self->hitBox.x = self->position.x - 64;
   self->hitBox.y = self->position.y - 72;
   self->hitBox.w = 64;
   self->hitBox.h = 64;

   //gf2d_draw_rect(self->hitBox, vector4d(78, 250, 29, 255));

  
   //dont let it fall through platform
  // if (self->standingOnPlatform == 1 && self->velocity.y > 0)
   //{
    //   self->velocity.y = 0;
   //}

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
        "images/mobs/bug.png",
        64,
        64,
        1);
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