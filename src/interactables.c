#include "interactables.h"
#include "gf2d_draw.h"
#include "simple_logger.h"
#include "damage.h"

Entity* NewGrass(Vector2D position)
{
    Entity* self;
    self = entity_new();
    if (!self)return NULL;
    self->sprite = gf2d_sprite_load_all(
        "images/grass.png",
        64,
        64,
        1);
    self->objectRect.x = position.x;
    self->objectRect.y = position.y;
    self->objectRect.w = 64;
    self->objectRect.w = 64;
    self->team = 5;
    self->objectID = 1;
    self->maxHealth = 1;
    self->health = self->maxHealth;
    self->think = GrassThink;
    vector2d_copy(self->position, position);
    return self;
}

void GrassThink(Entity* self)
{
    Entity* player = GetPlayer();
   
    SDL_Rect tempRect = { self->position.x, self->position.y, 64, 64 };
    if (SDL_HasIntersection(&player->hitBox, &tempRect))
    {
        player->slowed = 1;
    }
    else
    {
        player->slowed = 0;
    }
  
}



Entity* NewExplosiveBarrel(Vector2D position)
{
    Entity* self;
    self = entity_new();
    if (!self)return NULL;
    self->sprite = gf2d_sprite_load_all(
        "images/explosiveBarrel.png",
        64,
        64,
        1);
    self->objectRect.x = position.x;
    self->objectRect.y = position.y;
    self->objectRect.w = 64;
    self->objectRect.w = 64;
    self->team = 5;
    self->objectID = 2;
    self->maxHealth = 1;
    self->health = self->maxHealth;
    self->think = ExplosiveBarrelThink;
    vector2d_copy(self->position, position);
    return self;
}

void ExplosiveBarrelThink(Entity* self)
{
    Entity* player = GetPlayer();

    //explode on hit
}


Entity* NewHealthBarrel(Vector2D position)
{
    Entity* self;
    self = entity_new();
    if (!self)return NULL;
    self->sprite = gf2d_sprite_load_all(
        "images/healthBarrel.png",
        64,
        64,
        1);
    self->objectRect.x = position.x;
    self->objectRect.y = position.y;
    self->objectRect.w = 64;
    self->objectRect.w = 64;
    self->team = 5;
    self->objectID = 3;
    self->maxHealth = 1;
    self->health = self->maxHealth;
    self->think = HealthBarrelThink;
    vector2d_copy(self->position, position);
    return self;
}

void HealthBarrelThink(Entity* self)
{
    Entity* player = GetPlayer();

    //heal on hit
}

Entity* NewTreasureChest(Vector2D position)
{
    Entity* self;
    self = entity_new();
    if (!self)return NULL;
    self->sprite = gf2d_sprite_load_all(
        "images/treasureChest.png",
        64,
        64,
        1);
    self->objectRect.x = position.x;
    self->objectRect.y = position.y;
    self->objectRect.w = 64;
    self->objectRect.w = 64;
    self->team = 5;
    self->objectID = 4;
    self->maxHealth = 1;
    self->health = self->maxHealth;
    self->think = TreasureChestThink;
    vector2d_copy(self->position, position);
    return self;
}

void TreasureChestThink(Entity* self)
{
    Entity* player = GetPlayer();

    //drop BFS on hit
}


Entity* NewMimicChest(Vector2D position)
{
    Entity* self;
    self = entity_new();
    if (!self)return NULL;
    self->sprite = gf2d_sprite_load_all(
        "images/mimicHidden.png",
        64,
        64,
        1);
    self->objectRect.x = position.x;
    self->objectRect.y = position.y;
    self->objectRect.w = 64;
    self->objectRect.w = 64;
    self->team = 5;
    self->objectID = 5;
    self->maxHealth = 1;
    self->health = self->maxHealth;
    self->think = MimicChestThink;
    vector2d_copy(self->position, position);
    return self;
}

void MimicChestThink(Entity* self)
{
    Entity* player = GetPlayer();

    //spawn mimic on death
}