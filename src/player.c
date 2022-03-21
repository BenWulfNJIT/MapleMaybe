#include "simple_logger.h"
#include "gfc_input.h"

#include "player.h"
#include "skill.h"


void player_think(Entity* self)
{
    Entity* ent = self;
  
    //entity_new(skill);

    

    ControlMovement(ent);

    if (self->damageBoostTime > 0) self->damageBoostTime--;

    self->hitBox.x = self->position.x - 64;
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
    self->sprite = gf2d_sprite_load_all("images/chars/thor.png", 64, 114, 1);
    self->skillOneSprite = gf2d_sprite_load_all("images/skills/thorSkill1.png", 128, 64, 1);
    self->skillTwoSprite = gf2d_sprite_load_all("images/skills/thorSkill2.png", 256, 32, 1);
    self->skillThreeSprite = gf2d_sprite_load_all("images/skills/thorSkill3.png", 64, 256, 1);
    self->skillFourSprite = gf2d_sprite_load_all("images/skills/thorSkill4.png", 512, 1024, 1);
    self->radius = 24;
    self->size.x = 32;
    self->size.y = 32;
    self->walkSpeed = 2;
    self->jumpHeight = -7;
    self->level = 1;
    self->experience = 0;
    self->skillOneCD = 0;
    self->skillTwoCD = 0;
    self->skillThreeCD = 0;
    self->skillFourCD = 0;
    self->activeSkill = 0;
    self->team = 1;
    self->movementLock = 0;
    self->maxHealth = 1000;
    self->health = self->maxHealth;
    self->isSmokeActive = 0;
    self->isCharInSmoke = 0;
    self->smokeTimer = 0;
    self->smokeArea.x = -20;
    self->smokeArea.y = -20;
    self->smokeArea.w = 256;
    self->smokeArea.h = 256;

    self->damageBoostTime = 0;
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
    
    if (self->movementLock == 1)
    {
        if (self->standingOnPlatform) 
        {
            self->velocity.x = 0;
            return;
        }
        else return;
       // return;
    }
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

    if (gfc_input_key_pressed("1") && self->level >= 1 && self->skillOneCD <= 0 && self->activeSkill == 0)
    {
        //60 cd ~= 1s

        switch (self->classNum)
        {
        case 0: //---thor skill timer
            self->skillOneCD = 60;
            self->skillOneDurationCounter = 15;
            break;
        case 1: //---loki skill timer
            self->skillOneCD = 60;
            self->skillOneDurationCounter = 15;
            break;
        case 2: //---odin skill timer
            self->skillOneCD = 60;
            self->skillOneDurationCounter = 15;
            break;
        case 3: //---hela skill timer
            self->skillOneCD = 60;
            self->skillOneDurationCounter = 15;
            break;
        case 4: //---fenrir skill timer
            self->skillOneCD = 60;
            self->skillOneDurationCounter = 15;
            break;
        }
       
        self->activeSkill = 1;
        SkillThink(self, 1, vector2d(0, 0));
        SkillCollisionCheck(self, self->activeSkill, &self->skillHitBox);
        return;
        
    }
    //else if (gfc_input_key_pressed("2") && self->level >= 2 && self->skillTwoCD <= 0 && self->activeSkill == 0)
    else if (gfc_input_key_pressed("2") && self->level >= 2 && self->skillTwoCD <= 0 && self->activeSkill == 0)
    {
        slog("Skill'd 2");
        //60 cd ~= 1s
        
        switch (self->classNum)
        {
        case 0: //---thor skill timer
            self->skillTwoCD = 300;
            self->skillTwoDurationCounter = 90;
            break;
        case 1: //---loki skill timer
            slog("weird");
            self->skillTwoCD = 1500;
            self->skillTwoDurationCounter = 900;
            self->smokeArea.x = self->position.x - 150;
            self->smokeArea.y = self->position.y - 128 - 64;
            self->smokeArea.w = 256;
            self->smokeArea.h = 256;

            break;
        case 2: //---odin skill timer
            self->skillOneCD = 60;
            self->skillOneDurationCounter = 15;
            break;
        case 3: //---hela skill timer
            self->skillOneCD = 60;
            self->skillOneDurationCounter = 15;
            break;
        case 4: //---fenrir skill timer
            self->skillOneCD = 60;
            self->skillOneDurationCounter = 15;
            break;
        }

        self->activeSkill = 2;
        SkillThink(self, 2, vector2d(0, 0));
        SkillCollisionCheck(self, self->activeSkill, &self->skillHitBox);
        return;
    }
    else if (gfc_input_key_pressed("3") && self->level >= 3 && self->skillThreeCD <= 0 && self->activeSkill == 0)
    {
        slog("Skill'd 3");
        //60 cd ~= 1s
        

        switch (self->classNum)
        {
        case 0: //---thor skill timer
            self->skillThreeCD = 600;
            self->skillThreeDurationCounter = 120;
            break;
        case 1: //---loki skill timer
            self->skillThreeCD = 60;
            self->skillThreeDurationCounter = 15;
            break;
        case 2: //---odin skill timer
            self->skillThreeCD = 60;
            self->skillThreeDurationCounter = 15;
            break;
        case 3: //---hela skill timer
            self->skillThreeCD = 60;
            self->skillThreeDurationCounter = 15;
            break;
        case 4: //---fenrir skill timer
            self->skillThreeCD = 60;
            self->skillThreeDurationCounter = 15;
            break;
        }

        self->activeSkill = 3;
        SkillThink(self, 3, vector2d(0, 0));
        SkillCollisionCheck(self, self->activeSkill, &self->skillHitBox);
    }
    else if (gfc_input_key_pressed("4") && self->level >= 4 && self->skillFourCD <= 0 && self->activeSkill == 0)
    {

        slog("Skill'd 4");
        //60 cd ~= 1s
        


        switch (self->classNum)
        {
        case 0: //---thor skill timer
            self->skillFourCD = 6000;
            self->skillFourDurationCounter = 300;
            break;
        case 1: //---loki skill timer
            self->skillFourCD = 60;
            self->skillFourDurationCounter = 15;
            break;
        case 2: //---odin skill timer
            self->skillFourCD = 60;
            self->skillFourDurationCounter = 15;
            break;
        case 3: //---hela skill timer
            self->skillFourCD = 60;
            self->skillFourDurationCounter = 15;
            break;
        case 4: //---fenrir skill timer
            self->skillFourCD = 60;
            self->skillFourDurationCounter = 15;
            break;
        }

        self->activeSkill = 4;
        SkillThink(self, 4, vector2d(0, 0));
        SkillCollisionCheck(self, self->activeSkill, &self->skillHitBox);
    }
    else
    {

        return;
    }

    return;
}