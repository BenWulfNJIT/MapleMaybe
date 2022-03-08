#include"simple_logger.h"
#include "collision.h"
#include "gf2d_draw.h"
#include "entity.h"
#include "vector_map.h"


void SimplePlatformCollision(Entity* ent, VectorMap* currentMap)
{
	int currentPlatBelow = 8000;
	int distanceToPlat;
	Vector2D bottomCenterOfHitBox = {ent->hitBox.x + ent->hitBox.w/2,ent->hitBox.y + ent->hitBox.h, };
	
	
for (int i = 0; i < currentMap->platformCount; i++)
{
	if (ent->hitBox.y + ent->hitBox.h > currentMap->platformCoords[i].y) continue;
	if (currentMap->platformCoords[i].y < currentPlatBelow &&
		ent->position.x > currentMap->platformCoords[i].x &&
		ent->position.x < currentMap->platformCoords[i].z)
	{
		currentPlatBelow = currentMap->platformCoords[i].y;
		
	}
}

if(currentPlatBelow != 8000 ) ent->knownPlatHeight = currentPlatBelow;

//at this point we would have at least found a plat or errored
distanceToPlat = currentPlatBelow - (ent->hitBox.y + ent->hitBox.h);
Vector2D belowEnt = { ent->position.x, (ent->hitBox.y+ent->hitBox.h) + distanceToPlat };
Vector4D redColor = { 255, 20, 20, 255 };
gf2d_draw_line(bottomCenterOfHitBox, belowEnt, redColor);

gf2d_draw_rect(ent->hitBox, redColor);
//slog("distance: %i", distanceToPlat);

//if (distanceToPlat < 0) slog("ERROR!! distanceToPlat: %i", distanceToPlat);

//check if entity is moving too fast and would go through platform
if (ent->velocity.y > distanceToPlat)
{
	slog("i think this will cause an issue");
	ent->position.y = currentPlatBelow - ent->hitBox.h/2;
}
//toggle whether or not entity is standing on platform
if ( distanceToPlat < 2 || ent->velocity.y > distanceToPlat)
{
	ent->standingOnPlatform = 1;
}
else
{
	ent->standingOnPlatform = 0;

}
//need to check for intersections with that lines, probably also check closest
//first find only the platforms below the ent
//also need to set up a hitbox situation



}
