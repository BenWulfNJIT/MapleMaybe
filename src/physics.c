#include "entity.h"
#include "physics.h"


void DoPlayerGravity(Entity* ent)
{
	Physics playerPhysics;
	playerPhysics.gravity = 0.15;
	playerPhysics.MAX_FALL_SPEED = 7;

	if (ent && ent->standingOnPlatform == 0 && ent->velocity.y < playerPhysics.MAX_FALL_SPEED)
	{
		ent->velocity.y += playerPhysics.gravity;
	}
}
