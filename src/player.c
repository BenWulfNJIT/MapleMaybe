#include "simple_logger.h"
#include "gfc_input.h"

#include "player.h"
#include "skill.h"
#include "portal.h"

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
    self->healthShop = gf2d_sprite_load_all("images/hud/healthShop.png", 256, 256, 1);
    self->healthPotSprite = gf2d_sprite_load_all("images/hud/healthPot.png", 32, 32, 1);
    self->talkDiag = gf2d_sprite_load_all("images/hud/talkDiag.png", 256, 256, 1);

    self->level1 = gf2d_sprite_load_all("images/hud/level1.png", 32, 32, 1);
    self->level2 = gf2d_sprite_load_all("images/hud/level2.png", 32, 32, 1);
    self->level3 = gf2d_sprite_load_all("images/hud/level3.png", 32, 32, 1);
    self->level4 = gf2d_sprite_load_all("images/hud/level4.png", 32, 32, 1);
    self->level5 = gf2d_sprite_load_all("images/hud/level5.png", 32, 32, 1);

    self->hp = gf2d_sprite_load_all("images/hud/hp.png", 32, 32, 1);
    self->xp = gf2d_sprite_load_all("images/hud/xp.png", 32, 32, 1);



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
    self->odinLaserTarget.x = 0;
    self->odinLaserTarget.y = 0;
    self->damageBoostTime = 0;
    self->thorns = 0;
    self->isBlackHoleActive = 0;
    self->slowed = 0;
    self->doubleJump = 0;
    self->jumpPower = 0.8;
    self->floatTimer = 0;
    self->currency = 0;
    self->healthPotCount = 0;
    self->canPurchase = 0;
    self->shopping = 0;
    self->canTalk = 0;
    self->talking = 0;
    self->teleporting = 0;
    self->gameState = 0;
    //item info
    self->hasMirrorShield = 0; 
    self->hasBFS = 0; 
    self->hasSneakers = 0;
    self->hasRegenBracelet = 0; 
    self->hasFireCape = 0;
    self->isMapOpen = 0;
    self->isReflecting = 0;
    self->isSlowed = 0;
    self->showExplosion = 0;
    self->showHealing = 0;
    self->canWin = 0;
    self->think = player_think;


    vector2d_copy(self->position, position);
    //vector2d_copy(self->velocity, velocity);
    vector2d_set(self->drawOffset, -64, -78);
    return self;
}

void ControlMovement(Entity* self)
{
    float speed, jump;
    Entity* skill;

    //skill->sprite = gf2d_sprite_load_image("images/fireball.png");
    Vector2D skillPos;

    if (self->classNum == 0) speed = self->walkSpeed * 1.5;
    else speed = self->walkSpeed;

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
    
    //slog("shopping = %i", self->shopping);
   // slog("canPurchase = %i", self->canPurchase);

   

    if (self->isMapOpen == 0 && gfc_input_key_pressed("m"))
    {
        slog("open map");
        self->isMapOpen = 1;
    }
    else if (self->isMapOpen == 1 && gfc_input_key_pressed("m"))
    {
        slog("close map");
        self->isMapOpen = 0;

    }


    if (self->playerCanTeleportToMapID != -1 && gfc_input_key_pressed("w"))
    {
        slog("Test");
        self->teleporting = 1;
    }
    else
    {
        self->teleporting = 0;
    }

    if (self->canTalk && !self->talking && gfc_input_key_pressed("t"))
    {
        //slog("hello");
        self->talking = 1;
    }
    else if (!self->canTalk || (self->canTalk && self->talking && gfc_input_key_pressed("t")))
    {
        // slog("hulbo");
        self->talking = 0;

    }

    if (self->canPurchase && !self->shopping && gfc_input_key_pressed("p"))
    {
        //slog("hello");
        self->shopping = 1;
    }
    else if (!self->canPurchase || (self->canPurchase && self->shopping && gfc_input_key_pressed("p")))
    {
       // slog("hulbo");
        self->shopping = 0;

    }
   
    if (self->shopping && gfc_input_key_pressed("h") && self->currency >= 50 && self->healthPotCount < 5)
    {
        self->healthPotCount++;
        self->currency -= 50;
    }

    if (gfc_input_key_pressed("e") && self->healthPotCount >= 1)
    {
        self->healthPotCount--;
        self->health += 100;
        if (self->health > self->maxHealth) self->health = self->maxHealth;
    }

    if (self->classNum == 2 && self->standingOnPlatform)
    {
        self->floatTimer = 0;
    }
    if (self->classNum == 2 && !self->standingOnPlatform)
    {
        self->floatTimer++;
    }
    if (self->classNum == 3 && self->standingOnPlatform == 1) self->doubleJump = 1;
    //slog()
    //Basic movement commands
    if (self->classNum == 1 && gfc_input_key_pressed("q") && self->facing == 1) self->position.x += 200;
    if (self->classNum == 1 && gfc_input_key_pressed("q") && self->facing == 0) self->position.x -= 200;

    

    if (gfc_input_key_held(" ") && self->classNum == 2 && self->floatTimer < 250)
    {
        self->velocity.y = -1.5;
    }
    if (gfc_input_key_held(" ") && self->classNum == 4 && self->jumpPower < 1.5)
    {
        self->jumpPower += 0.01;
    }
    if (gfc_input_key_released(" ") && self->classNum == 4 && self->standingOnPlatform) 
    {
        self->velocity.y = jump*self->jumpPower;
        self->jumpPower = 0.8;
    }

    if (gfc_input_key_pressed(" ") && self->standingOnPlatform && self->classNum != 4 && self->classNum != 2)
    {
        self->velocity.y = jump;
    }
    else if (gfc_input_key_pressed(" ") && self->classNum == 3  && !self->standingOnPlatform && self->doubleJump == 1)
    {
        self->velocity.y = jump;
        self->doubleJump = 0;
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

    if (self->slowed == 1)
    {
        self->velocity.x *= 0.5;
    }
    if (self->hasSneakers == 1)
    {
        self->velocity.x *= 2;
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
        //60 cd ~= 1s
        
        switch (self->classNum)
        {
        case 0: //---thor skill timer
            self->skillTwoCD = 300;
            self->skillTwoDurationCounter = 90;
            break;
        case 1: //---loki skill timer
           // slog("weird");
            self->skillTwoCD = 1500;
            self->skillTwoDurationCounter = 900;
            self->smokeArea.x = self->position.x - 150;
            self->smokeArea.y = self->position.y - 128 - 64;
            self->smokeArea.w = 256;
            self->smokeArea.h = 256;

            break;
        case 2: //---odin skill timer
            //slog("got into odin");
            self->odinLaserTarget.x = GetNearestMob(self)->hitBox.x + GetNearestMob(self)->hitBox.w/2;
            self->odinLaserTarget.y = GetNearestMob(self)->hitBox.y;
            self->skillTwoCD = 180;
            self->skillTwoDurationCounter = 1;
            break;
        case 3: //---hela skill timer
            self->skillTwoCD = 600;
            self->skillTwoDurationCounter = 300;
            break;
        case 4: //---fenrir skill timer
            self->skillTwoCD = 120;
            self->skillTwoDurationCounter = 15;
            break;
        }

        //slog("got before think");
        self->activeSkill = 2;
        //slog("uhhh %i", self->activeSkill);
        SkillThink(self, 2, vector2d(0, 0));
        SkillCollisionCheck(self, self->activeSkill, &self->skillHitBox);
        return;
    }
    else if (gfc_input_key_pressed("3") && self->level >= 3 && self->skillThreeCD <= 0 && self->activeSkill == 0)
    {
        //60 cd ~= 1s
        

        switch (self->classNum)
        {
        case 0: //---thor skill timer
            self->skillThreeCD = 600;
            self->skillThreeDurationCounter = 120;
            break;
        case 1: //---loki skill timer
            self->skillThreeCD = 60;
            self->skillThreeDurationCounter = 1;
            break;
        case 2: //---odin skill timer
            self->skillThreeCD = 180;
            self->skillThreeDurationCounter = 60;
            break;
        case 3: //---hela skill timer
            self->skillThreeCD = 600;
            self->skillThreeDurationCounter = 400;
            break;
        case 4: //---fenrir skill timer
            self->skillThreeCD = 360;
            self->skillThreeDurationCounter = 180;
            break;
        }

        self->activeSkill = 3;
        SkillThink(self, 3, vector2d(0, 0));
        SkillCollisionCheck(self, self->activeSkill, &self->skillHitBox);
    }
    else if (gfc_input_key_pressed("4") && self->level >= 4 && self->skillFourCD <= 0 && self->activeSkill == 0)
    {

        //60 cd ~= 1s
        


        switch (self->classNum)
        {
        case 0: //---thor skill timer
            self->skillFourCD = 600;
            self->skillFourDurationCounter = 300;
            break;
        case 1: //---loki skill timer
            self->skillFourCD = 600;
            self->skillFourDurationCounter = 360;
            break;
        case 2: //---odin skill timer
            self->skillFourCD = 600;
            self->skillFourDurationCounter = 300;
            break;
        case 3: //---hela skill timer
            self->skillFourCD = 600;
            self->skillFourDurationCounter = 300;
            break;
        case 4: //---fenrir skill timer
            self->skillFourCD = 600;
            self->skillFourDurationCounter = 400;
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