#include "simple_logger.h"

#include "player.h"

Entity* player_new(Vector2D position)
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
    //self->think = player_think;


    vector2d_copy(self->position, position);
    //vector2d_copy(self->velocity, velocity);
    vector2d_set(self->drawOffset, -64, -78);
    return self;
}

void player_think(Entity* self)
{

}