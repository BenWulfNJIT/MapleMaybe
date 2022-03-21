#include "simple_logger.h"
#include "gf2d_draw.h"
#include "mob_turret.h"
#include "physics.h"
#include "collision.h"
#include "vector_map.h"
#include "damage.h"
#define ES_DEAD 1

void turret_think(Entity* self, VectorMap* map)
{
    Entity* player;
    Vector2D eye,target;
    if (self->hitBox.y && self->knownPlatHeight)
    {
        if (self->hitBox.y + self->hitBox.h > self->knownPlatHeight)
        {
            //slog("ERROR BROSKI");
        }
    }

    int mx, my;
    double distance;

    //if (self->movementLock == 1) self->velocity.x = 0;
    //else self->velocity.x = gfc_random() * 2 - 1;


            eye.x = self->position.x;
            eye.y = self->position.y - 60;
            player = GetPlayer();

            
           
    if (self->laserTimer < 360) self->laserTimer++;
    if (self->laserTimer == 250)
    {
       
        self->laserTarget.x = player->position.x;
        self->laserTarget.y = player->position.y;

        self->laserExplosion.x = player->position.x;
        self->laserExplosion.y = player->position.y;



        
    }
    else if (self->laserTimer > 300 && self->laserTimer < 340)
    {
        gf2d_draw_line(self->laserTarget, eye, vector4d(255, 20, 20, 255));
        eye.y += 5;
        gf2d_draw_line(self->laserTarget, eye, vector4d(255, 20, 20, 255));
        eye.y += 5;
        gf2d_draw_line(self->laserTarget, eye, vector4d(255, 20, 20, 255));

        gf2d_draw_rect(self->laserExplosion, vector4d(255, 20, 20, 255));
        //slog("TEST: %i, %i", self->laserExplosion.x, player->hitBox.x);
        if (SDL_HasIntersection(&player->hitBox, &self->laserExplosion))
        {
           // slog("shot em");
            InflictDamage(self, player, 10);
        }
    }
     
     if (self->laserTimer == 360) self->laserTimer = 0;
   



    self->hitBox.x = self->position.x - 64;
    self->hitBox.y = self->position.y - 80;
    self->hitBox.w = 128;
    self->hitBox.h = 128;






    //dont let it fall through platform
    if (self->standingOnPlatform == 1 && self->velocity.y > 0)
    {
        self->velocity.y = 0;
    }

    // if (intDistance <= 10)
     //{
        // entity_free(self);
     //}

}



Entity* turret_new(Vector2D position, Vector2D velocity)
{
    Entity* self;
    self = entity_new();
    if (!self)return NULL;
    self->sprite = gf2d_sprite_load_all(
        "images/turret.png",
        128,
        128,
        1);
    self->radius = 24;
    self->size.x = 128;
    self->size.y = 128;
    self->team = 2;
    self->maxHealth = 100;
    self->health = self->maxHealth;
    self->spawnMobNumber = 5;
    self->laserTimer = 0;
    self->laserTarget.x = 0;
    self->laserTarget.y = 0;
    self->laserExplosion.x = 0;
    self->laserExplosion.y = 0;
    self->laserExplosion.w = 5;
    self->laserExplosion.h = 5;
    self->think = turret_think;


    vector2d_copy(self->position, position);
    vector2d_copy(self->velocity, velocity);
    vector2d_set(self->drawOffset, -64, -78);
    return self;
}