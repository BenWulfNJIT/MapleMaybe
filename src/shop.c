#include "simple_logger.h"
#include "gf2d_draw.h"
#include "hela_spear.h"
#include "damage.h"

#define ES_DEAD 1

void shop_think(Entity* self)
{
    Entity* player = GetPlayer();
    self->hitBox.x = self->position.x - 64;
    self->hitBox.y = self->position.y - 72;
    self->hitBox.w = 64;
    self->hitBox.h = 64;
    if (SDL_HasIntersection(&self->hitBox, &player->hitBox))
    {
        player->canPurchase = 1;
    }
    else
    {
        player->canPurchase = 0;

    }


}



Entity* shop_new(Vector2D position)
{
    Entity* self;
    self = entity_new();
    if (!self)return NULL;
    self->sprite = gf2d_sprite_load_all(
        "images/chars/shop.png",
        64,
        64,
        1);
    self->radius = 24;
    self->size.x = 32;
    self->size.y = 32;
    self->team = -1;
    //self->maxHealth = 100;
    //self->health = self->maxHealth;
    self->flySpeed = 1;
    self->spawnMobNumber = 3;
    self->health = 999999;
    self->think = shop_think;


    vector2d_copy(self->position, position);
    vector2d_set(self->drawOffset, -64, -78);
    return self;
}