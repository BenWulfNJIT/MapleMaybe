#include "mimic.h"
#include "gf2d_draw.h"
#include "damage.h"
Entity* SpawnMimic(Vector2D position)
{
    Entity* self;
    self = entity_new();
    if (!self)return NULL;
    self->sprite = gf2d_sprite_load_all(
        "images/mimicAttack.png",
        256,
        256,
        1);
    self->radius = 24;
    self->size.x = 64;
    self->size.y = 64;
    self->team = 2;
    self->maxHealth = 10000;
    self->health = self->maxHealth;
    self->spawnMobNumber = 6;
    self->standingOnPlatform = 0;
    self->standingPlatform.x = 0;
    self->standingPlatform.y = 0;
    self->standingPlatform.z = 0;
    self->standingPlatform.w = 0;
    self->mobSpeed = 2;
    self->carried = 0;
    self->dashTimer = 0;
    self->think = MimicThink;


    vector2d_copy(self->position, position);
    //vector2d_copy(self->velocity, velocity);
    vector2d_set(self->drawOffset, -64, -78);
    return self;
}


void MimicThink(Entity* self)
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

  //  int mx, my;
  //  double distance;
    self->dashTimer++;

    if (player->position.x > self->position.x)
    {
        if (self->dashTimer < 40) self->velocity.x = 5;
        else self->velocity.x = 0;
    }
    if (player->position.x < self->position.x)
    {
        if (self->dashTimer < 40) self->velocity.x = -5;
        else self->velocity.x = 0;
    }

    if (self->dashTimer >= 120) self->dashTimer = 0;

    self->hitBox.x = self->position.x - 114;
    self->hitBox.y = self->position.y - 114;
    self->hitBox.w = 256;
    self->hitBox.h = 256;
    gf2d_draw_rect(self->hitBox, vector4d(250, 0, 0, 255));


    
    if (SDL_HasIntersection(&self->hitBox, &player->hitBox))
    {
        InflictDamage(self, player, 10);
    }

    if (self->standingOnPlatform == 1 && self->velocity.y > 0)
    {
        self->velocity.y = 0;
    }


}