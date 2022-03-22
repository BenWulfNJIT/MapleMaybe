#include "simple_logger.h"
#include "gf2d_draw.h"
#include "hela_spear.h"
#include "damage.h"

#define ES_DEAD 1

void spear_think(Entity* self)
{
    
    
    Entity* target = GetNearestMob(self);
    float speed;
    //if (target->team == 1) return;
    slog("team of target: %i", target->team);
    
    Vector2D targetPos = target->position;
    if (!target || target->team == 1)
    {
        targetPos.x = 600;
        targetPos.y = 300;
    }
    Vector2D direction;
    vector2d_sub(direction, targetPos, self->position );
    vector2d_normalize(&direction);
    vector2d_set_magnitude(&direction, self->flySpeed);
    
    self->velocity = direction;
    self->flySpeed += 0.1;
   // self->position.x = 400;
    //self->position.y = 400;

    //gf2d_draw_rect(target->hitBox, vector4d(255, 255, 255, 255));
    self->hitBox.x = self->position.x - 64;
    self->hitBox.y = self->position.y - 72;
    self->hitBox.w = 64;
    self->hitBox.h = 64;


    if (SDL_HasIntersection(&self->hitBox, &target->hitBox))
    {
        self->flySpeed = 1;
        InflictDamage(self, target, 1);
    }

}



Entity* spear_new(Vector2D position)
{
    Entity* self;
    self = entity_new();
    if (!self)return NULL;
    self->sprite = gf2d_sprite_load_all(
        "images/skills/helaSkill3.png",
        64,
        64,
        1);
    self->radius = 24;
    self->size.x = 32;
    self->size.y = 32;
    self->team = 2;
    //self->maxHealth = 100;
    //self->health = self->maxHealth;
    self->flySpeed = 1;
    self->spawnMobNumber = 3;
    self->team = -1;
    self->health = 999999;
    self->think = spear_think;


    vector2d_copy(self->position, position);
    vector2d_set(self->drawOffset, -64, -78);
    return self;
}