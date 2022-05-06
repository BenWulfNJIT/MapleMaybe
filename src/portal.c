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

    if (self->position.x < 0)return;
    Entity* player = GetPlayer();
    
    if (abs(self->position.x - player->position.x) < 64 && abs(self->position.y - player->position.y))
    {
      // slog("TEST1: %i", player->playerCanTeleportToMapID);
       //slog("TEST2: %i", self->portalTeleportMapID);

        player->playerCanTeleportToMapID = self->portalTeleportMapID;

       // slog("TEST3: %i", player->playerCanTeleportToMapID);

    }
    else
    {
        player->playerCanTeleportToMapID = -1;
    }
       
    /*
    slog("Portal Location: [%f, %f]", self->position.x, self->position.y);
    slog("In MapID: %i", self->portalInMapID);
    slog("Trying to teleport to: %i", self->portalTeleportMapID);
    slog("Player teleport ID: %i", player->playerCanTeleportToMapID);
    slog("\n\n");
    */
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


