#include "collision.h"
#include "gf2d_draw.h"
#include "entity.h"


void SimplePlatformCollision(Entity* ent)
{
Vector2D belowEnt = { ent->position.x, ent->position.y + 1000 };
Vector4D redColor = { 255, 20, 20, 255 };
gf2d_draw_line(ent->position, belowEnt, redColor);
}
