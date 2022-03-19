#include "simple_logger.h"
#include "gfc_input.h"

#include "player.h"
#include "skill.h"


void player_think(Entity* self)
{
    Entity* ent = self;
  
    //entity_new(skill);

    

    ControlMovement(ent);


    self->hitBox.x = self->position.x - 32;
    self->hitBox.y = self->position.y - 32;
    self->hitBox.w = 64;
    self->hitBox.h = 64;

    if (self->standingOnPlatform == 1 && self->velocity.y > 0)
    {
        self->velocity.y = 0;
    }

}

Entity* player_new(Vector2D position)
{
    Entity* self;
    self = entity_new();
    if (!self)return NULL;
    self->sprite = gf2d_sprite_load_all(
        "images/space_bug_top.png",
        128,
        128,
        16);
    self->skillOneSprite = gf2d_sprite_load_all("images/fireball.png", 64, 64, 1);
    self->radius = 24;
    self->size.x = 32;
    self->size.y = 32;
    self->walkSpeed = 2;
    self->jumpHeight = -7;
    self->level = 1;
    self->experience = 0;
    self->skillOneCD = 0;
    self->activeSkill = 0;
    self->team = 1;
    self->think = player_think;


    vector2d_copy(self->position, position);
    //vector2d_copy(self->velocity, velocity);
    vector2d_set(self->drawOffset, -64, -78);
    return self;
}

void ControlMovement(Entity* self)
{
    int speed, jump;
    Entity* skill;

    //skill->sprite = gf2d_sprite_load_image("images/fireball.png");
    Vector2D skillPos;

    speed = self->walkSpeed;
    jump = self->jumpHeight;

    gfc_input_update();
    

    //Basic movement commands

    if (gfc_input_key_pressed(" ") && self->standingOnPlatform)
    {
        self->velocity.y = jump;
    }

    if (gfc_input_key_held("a") && !gfc_input_key_held("d"))
    {
        //accelerate to walk
        self->facing = 0;
        self->velocity.x = -speed;
    }
    else if (gfc_input_key_released("a") && !gfc_input_key_held("d"))
    {
        //slow down to stop
        self->velocity.x = 0;
    }
    else if (gfc_input_key_held("d") && !gfc_input_key_held("a"))
    {
        self->facing = 1;
        self->velocity.x = speed;
    }
    else if (gfc_input_key_released("d") && !gfc_input_key_pressed("a"))
    {
        self->velocity.x = 0;
    }
    else if (gfc_input_key_held("a") && gfc_input_key_held("d"))
    {
        self->velocity.x = 0;
    }
    else
    {
        return;
    }

  

}

void DoSkills(Entity* self)
{
    //slog("active skill: %i", self->activeSkill);
    if (self->activeSkill == 0 && self->skillOneCD > 0)
    {
        self->skillOneCD--;
        return;
    }
    //First check for inputs 1-4 for attacks
    //If it works set attack flag to true, set self->active to that num

    if (gfc_input_key_pressed("1") && self->level >= 1 && self->skillOneCD <= 0)
    {
        //60 cd ~= 1s
        self->skillOneCD = 180;
        self->skillOneDurationCounter = 60;
        self->activeSkill = 1;
        return;
        
    }
    else if (gfc_input_key_pressed("2") && self->level >= 2)
    {
        slog("Skill'd 2");
    }
    else if (gfc_input_key_pressed("3") && self->level >= 3)
    {
        slog("Skill'd 3");
    }
    else if (gfc_input_key_pressed("4") && self->level >= 4)
    {
        slog("Skill'd 4");
    }
    else
    {

        return;
    }

    return;
}