#include "portal.h"
#include "simple_logger.h"
#include "gf2d_draw.h"
#include "entity.h"


Entity* portal_new(Vector2D position, int selfMapID, int mapIDToTeleport)
{
    Entity* self;
    self = entity_new();
    if (!self)return NULL;
    self->sprite = gf2d_sprite_load_all(
        "images/portal.png",
        64,
        64,
        1);
    self->radius = 24;
    self->size.x = 64;
    self->size.y = 64;
    self->team = 3;
    self->maxHealth = 999999;
    self->health = self->maxHealth;
 
    self->portalInMapID = selfMapID;
    self->portalTeleportMapID = mapIDToTeleport;

    self->think = portal_think;


    vector2d_copy(self->position, position);
    //vector2d_copy(self->velocity, velocity);
    vector2d_set(self->drawOffset, -64, -78);
    return self;
}


void portal_think(Entity* self, VectorMap* map)
{

    Entity* player = GetPlayer();
    
    if (abs(self->position.x - player->position.x) < 64 && abs(self->position.y - player->position.y))
    {
        player->playerCanTeleportToMapID = self->portalTeleportMapID;
    }
    else
    {
        player->playerCanTeleportToMapID = -1;
    }
       
    
}



void ChangeMap(VectorMap* map, int mapID)
{
    switch (mapID)
    {
    case 0:

        break;
        
    
    case 1:

        break;
    
    
    case 2:
        break;
    }
}


