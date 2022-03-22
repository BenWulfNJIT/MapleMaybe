#include"simple_logger.h"
#include "collision.h"
#include "gf2d_draw.h"
//#include "entity.h"
//#include "vector_map.h"


void SimplePlatformCollision(Entity* ent, VectorMap* currentMap)
{
	const int MAX_DISTANCE = 99999;
	int currentPlatBelowLeft = MAX_DISTANCE;
	int currentPlatBelowRight = MAX_DISTANCE;
	int distanceToPlatLeft, distanceToPlatRight, distanceToNearestPlat, nearestPlatHeight;
	Vector2D bottomLeftCenterOfHitBox = {ent->hitBox.x,ent->hitBox.y + ent->hitBox.h, };
	Vector2D bottomRightCenterOfHitBox = { ent->hitBox.x + ent->hitBox.w,ent->hitBox.y + ent->hitBox.h, };

	
for (int i = 0; i < currentMap->platformCount; i++)
{
	if (ent->hitBox.y + ent->hitBox.h > currentMap->platformCoords[i].y) continue;
	if (currentMap->platformCoords[i].y < currentPlatBelowLeft &&
		bottomLeftCenterOfHitBox.x > currentMap->platformCoords[i].x &&
		bottomLeftCenterOfHitBox.x < currentMap->platformCoords[i].z)
	{
		currentPlatBelowLeft = currentMap->platformCoords[i].y;
		
	}
	if (currentMap->platformCoords[i].y < currentPlatBelowRight &&
		bottomRightCenterOfHitBox.x > currentMap->platformCoords[i].x &&
		bottomRightCenterOfHitBox.x < currentMap->platformCoords[i].z)
	{
		currentPlatBelowRight = currentMap->platformCoords[i].y;

	}
}
//slog("RIGHT: %i", currentPlatBelowRight);

 

//at this point we would have at least found a plat or errored
distanceToPlatLeft = currentPlatBelowLeft - (ent->hitBox.y + ent->hitBox.h);
distanceToPlatRight = currentPlatBelowRight - (ent->hitBox.y + ent->hitBox.h);



Vector2D belowLeftEnt = { bottomLeftCenterOfHitBox.x, (ent->hitBox.y+ent->hitBox.h) + distanceToPlatLeft };
Vector2D belowRightEnt = { bottomRightCenterOfHitBox.x, (ent->hitBox.y + ent->hitBox.h) + distanceToPlatRight };

if (distanceToPlatLeft <= distanceToPlatRight) 
{
	distanceToNearestPlat = distanceToPlatLeft;
	nearestPlatHeight = currentPlatBelowLeft;
	
}
else 
{
	distanceToNearestPlat = distanceToPlatRight;
	nearestPlatHeight = currentPlatBelowRight;
}

if (nearestPlatHeight != MAX_DISTANCE) ent->knownPlatHeight = nearestPlatHeight;

Vector4D redColor = { 255, 20, 20, 255 };
//gf2d_draw_line(bottomLeftCenterOfHitBox, belowLeftEnt, redColor);
//gf2d_draw_line(bottomRightCenterOfHitBox, belowRightEnt, redColor);


////gf2d_draw_rect(ent->hitBox, redColor);
//if(&ent->skillHitBox) //gf2d_draw_rect(ent->skillHitBox, redColor);

//slog("distance: %i", distanceToPlat);

//if (distanceToPlat < 0) slog("ERROR!! distanceToPlat: %i", distanceToPlat);

//check if entity is moving too fast and would go through platform
if (ent->velocity.y > distanceToNearestPlat)
{
	//slog("i think this will cause an issue");
	ent->position.y = nearestPlatHeight - ent->hitBox.h/2;
}
//toggle whether or not entity is standing on platform
if ( distanceToNearestPlat < 2 || ent->velocity.y > distanceToNearestPlat)
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


void BoundingBoxCollision(Entity* ent, VectorMap* currentMap)
{
	
	if (ent->hitBox.x + ent->hitBox.w > currentMap->boundingBox.w)
	{
		//slog("too far right");
		ent->position.x = 32+ currentMap->boundingBox.w - ent->hitBox.w /2;
	}

	if (ent->hitBox.x  < currentMap->boundingBox.x)
	{
		//slog("too far left");
		ent->position.x = 32 + currentMap->boundingBox.x + ent->hitBox.w / 2;
	}

	if (ent->hitBox.y < currentMap->boundingBox.y)
	{
		//slog("too far up");
		ent->position.y = currentMap->boundingBox.y + ent->hitBox.h / 2;
	}

	if (ent->hitBox.y + ent->hitBox.h > currentMap->boundingBox.h)
	{
		//slog("too far down");
		ent->position.y = currentMap->boundingBox.h - ent->hitBox.h / 2;
	}
}
