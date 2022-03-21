#include "simple_logger.h"
#include "gf2d_draw.h"
#include "mob_roller.h"
#include "physics.h"
#include "collision.h"
#include "vector_map.h"
#define ES_DEAD 1

void roller_think(Entity* self, VectorMap* map)
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


    int leftBound = 300;
    int rightBound = 900;

    if (self->position.x > leftBound && self->position.x < rightBound)
    {
        self->velocity.x = self->mobSpeed;
        if (gfc_random() < 0.01) self->mobSpeed *= -1;
    }
    else if (self->hitBox.x <= leftBound)
    {
        self->velocity.x = 2;
        self->mobSpeed *= -1;
        // slog("hello?");
    }
    else if (self->hitBox.x >= rightBound)
    {
        self->velocity.x = -2;
        self->mobSpeed *= -1;
    }




    self->hitBox.x = self->position.x - 64;
    self->hitBox.y = self->position.y - 80;
    self->hitBox.w = 64;
    self->hitBox.h = 64;




    Entity* player = GetPlayer();
    if (SDL_HasIntersection(&self->hitBox, &player->hitBox))
    {
        InflictDamage(self, player, 10);
    }

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



Entity* roller_new(Vector2D position, Vector2D velocity)
{
    Entity* self;
    self = entity_new();
    if (!self)return NULL;
    self->sprite = gf2d_sprite_load_all(
        "images/mobs/roller.png",
        64,
        64,
        1);
    self->radius = 24;
    self->size.x = 64;
    self->size.y = 64;
    self->team = 2;
    self->maxHealth = 100;
    self->health = self->maxHealth;
    self->spawnMobNumber = 4;
    self->mobSpeed = 2;
    self->think = roller_think;


    vector2d_copy(self->position, position);
    vector2d_copy(self->velocity, velocity);
    vector2d_set(self->drawOffset, -64, -78);
    return self;
}