#include "simple_logger.h"
#include "gfc_input.h"
#include "player.h"



void player_think(Entity* self)
{
    Entity* ent = self;
    ControlMovement(ent);

    self->hitBox.x = self->position.x - 32;
    self->hitBox.y = self->position.y - 32;
    self->hitBox.w = 64;
    self->hitBox.h = 64;

    if (self->standingOnPlatform == 1 && self->velocity.y > 0)
    {
        self->velocity.y = 0;
    }

}

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
    self->walkSpeed = 2;
    self->think = player_think;


    vector2d_copy(self->position, position);
    //vector2d_copy(self->velocity, velocity);
    vector2d_set(self->drawOffset, -64, -78);
    return self;
}

void ControlMovement(Entity* self)
{
    int speed;

    speed = self->walkSpeed;


    gfc_input_update();


    if (gfc_input_key_held("a") && !gfc_input_key_held("d"))
    {
        //accelerate to walk
        self->velocity.x = -speed;
    }
    else if (gfc_input_key_released("a") && !gfc_input_key_held("d"))
    {
        //slow down to stop
        self->velocity.x = 0;
    }
    else if (gfc_input_key_held("d") && !gfc_input_key_held("a"))
    {

        self->velocity.x = speed;
    }
    else if (gfc_input_key_released("d") && !gfc_input_key_pressed("a"))
    {
        self->velocity.x = 0;
    }
    else if (gfc_input_key_held("a") && gfc_input_key_held("d"))
    {
        self->velocity.x = 0;
    }

}