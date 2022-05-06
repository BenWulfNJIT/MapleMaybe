#ifndef __INTERACTABLES_H__
#define __INTERACTABLES_H__

#include "entity.h"

Entity* NewGrass(Vector2D position);

void GrassThink(Entity* self);

void ExplosiveBarrelThink(Entity* self);
void HealthBarrelThink(Entity* self);
void TreasureChestThink(Entity* self);
void MimicChestThink(Entity* self);





#endif