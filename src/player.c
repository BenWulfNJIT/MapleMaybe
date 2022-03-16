#include "simple_logger.h"
#include "gfc_input.h"
#include "player.h"



void player_think(Entity* self)
{
    Input input;
    //handle inputs
    gfc_input_update();
    //input = gfc_input_key_pressed

    if (gfc_input_key_held("a"))
    {
        self->velocity.x = -5;
    }
    if (gfc_input_key_held("d"))
    {
        self->velocity.x = 5;
    }
    if (gfc_input_key_pressed("80"))
    {
        slog("b");
    }
    /**
    * SCANCODES
    *   SDL_SCANCODE_RIGHT = 79,
    *   SDL_SCANCODE_LEFT = 80,
    *   SDL_SCANCODE_DOWN = 81,
    *   SDL_SCANCODE_UP = 82,
    */
    SDL_Scancode kc = SDL_SCANCODE_LEFT;
   // slog("LEFT: %i",kc);
   


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
    self->think = player_think;


    vector2d_copy(self->position, position);
    //vector2d_copy(self->velocity, velocity);
    vector2d_set(self->drawOffset, -64, -78);
    return self;
}

