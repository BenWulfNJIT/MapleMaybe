#include "items.h"
#include "simple_logger.h"



Entity* NewItem(Vector2D position, int ItemID)
{
    Entity* self;
    self = entity_new();
    if (!self)return NULL;

    switch (ItemID)
    {
    case 1:
        self->sprite = gf2d_sprite_load_all("images/items/mirrorShield.png", 64, 64, 1);
        break;
    case 2:
        self->sprite = gf2d_sprite_load_all("images/items/BFS.png", 64, 64, 1);
        break;
    case 3:
        self->sprite = gf2d_sprite_load_all("images/items/sneakers.png", 64, 64, 1);
        break;
    case 4:
        self->sprite = gf2d_sprite_load_all("images/items/regenBracelet.png", 64, 64, 1);
        break;
    case 5:
        self->sprite = gf2d_sprite_load_all("images/items/fireCape.png", 64, 64, 1);
        break;
    default:
        self->sprite = gf2d_sprite_load_all("images/null.png", 64, 64, 1);
        break;
    }
    self->team = 4;
    vector2d_copy(self->position, position);
    //vector4d_set(self->itemRect, self->position.x, self->position.y, 32, 32);
    self->itemRect.x = self->position.x;
    self->itemRect.y = self->position.y;
    self->itemRect.w = 32;
    self->itemRect.h = 32;
    self->itemID = ItemID;
    //vector2d_copy(self->velocity, velocity);
    //vector2d_set(self->drawOffset, -64, -78);
    return self;


}


void ItemThink(Entity* self)
{
    Entity* player = GetPlayer();

    if (SDL_HasIntersection(&self->itemRect, &player->hitBox))
    {
        switch (self->itemID)
        {
        case 1:
            player->hasMirrorShield = 1;
            break;
        case 2:
            player->hasBFS = 1;

            break;
        case 3:
            player->hasSneakers = 1;

            break;
        case 4:
            player->hasRegenBracelet = 1;

            break;
        case 5:
            player->hasFireCape = 1;
            break;
        }
    }
}