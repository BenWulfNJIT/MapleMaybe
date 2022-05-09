#include "simple_logger.h"
#include "gf2d_draw.h"
#include "mob_man.h"
#include "physics.h"
#include "collision.h"
#include "vector_map.h"
#include "damage.h"
#define ES_DEAD 1

void man_think(Entity* self, VectorMap* map)
{
    Entity* player = GetPlayer();

    if (player->isBlackHoleActive)return;
    if (self->carried == 1)
    {
        self->position.x = player->position.x;
        self->position.y = player->position.y;
        return;
    }

    if (self->hitBox.y && self->knownPlatHeight)
    {
        if (self->hitBox.y + self->hitBox.h > self->knownPlatHeight)
        {
            //slog("ERROR BROSKI");
        }
    }

   // int mx, my;
   // double distance;
    
    
    int leftBound = 300;
    int rightBound = 900;
    
    if (self->position.x > leftBound && self->position.x < rightBound)
    {
        self->velocity.x = self->mobSpeed;
        if (gfc_random() < 0.005) self->mobSpeed *= -1;
    }
    else if (self->hitBox.x <= leftBound )
    {
        self->velocity.x = 0.5;
       // slog("hello?");
    }
    else if (self->hitBox.x >= rightBound)
    {
        self->velocity.x = -0.5;
    }


    self->hitBox.x = self->position.x - 64;
    self->hitBox.y = self->position.y - 80;
    self->hitBox.w = 64;
    self->hitBox.h = 64;
   
    if (SDL_HasIntersection(&self->hitBox, &player->hitBox))
    {
        InflictDamage(self, player, 10);
    }

    if (self->standingOnPlatform == 1 && self->velocity.y > 0)
    {
        self->velocity.y = 0;
    }

  
}



Entity* man_new(Vector2D position, Vector2D velocity)
{
    Entity* self;
    self = entity_new();
    if (!self)return NULL;
    self->sprite = gf2d_sprite_load_all(
        "images/mobs/man.png",
        64,
        64,
        1);
    self->radius = 24;
    self->size.x = 64;
    self->size.y = 64;
    self->team = 2;
    self->maxHealth = 200;
    self->health = self->maxHealth;
    self->spawnMobNumber = 2;
    self->standingOnPlatform = 0;
    self->standingPlatform.x = 0;
    self->standingPlatform.y = 0;
    self->standingPlatform.z = 0;
    self->standingPlatform.w = 0;
    self->mobSpeed = 0.5;
    self->carried = 0;

    self->think = man_think;


    vector2d_copy(self->position, position);
    vector2d_copy(self->velocity, velocity);
    vector2d_set(self->drawOffset, -64, -78);
    return self;
}