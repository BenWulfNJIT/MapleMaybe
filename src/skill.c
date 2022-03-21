#include "simple_logger.h"
#include "gfc_input.h"
#include "gf2d_draw.h"
#include "skill.h"

Entity* skill_new(Entity* attacker, Vector2D position)
{
    Entity* self;
    self = entity_new();
    if (!self)return NULL;
    self->sprite = gf2d_sprite_load_all(
        "images/skills/thorSkill1.png",
        64,
        64,
        1);
    self->radius = 24;
    self->size.x = 32;
    self->size.y = 32;


    vector2d_copy(self->position, position);
    return self;
}

void DoSkill(Entity* attacker, Entity* skill, Vector2D position)
{
   // gf2d_sprite_draw_image(skill->sprite, position);
    //attacker->skillOneDurationCounter--;
    //entity_free(skill);
}

void SkillThink(Entity* attacker, int skill, Vector2D position)
{
    if (attacker->skillOneCD > 0) attacker->skillOneCD--;
    if (attacker->skillTwoCD > 0) attacker->skillTwoCD--;
    if (attacker->skillThreeCD > 0) attacker->skillThreeCD--;
    if (attacker->skillFourCD > 0) attacker->skillFourCD--;

    //slog("currentclass %i", attacker->classNum);
    switch (attacker->classNum)
    {
    case 0: //------------------ thor skills ---------------------
        switch (skill)
        {
        case 1:
            
            if (attacker->skillOneDurationCounter > 0)
            {
                //do skill stuff
                if (attacker->facing == 0)
                {
                    attacker->skillOnePosition.x = attacker->position.x - 220;
                    attacker->skillOnePosition.y = attacker->position.y - 32;
                    attacker->skillHitBox.x = attacker->position.x - 220;
                    attacker->skillHitBox.y = attacker->position.y - 32;
                }
                else if (attacker->facing == 1)
                {
                    attacker->skillOnePosition.x = attacker->position.x + 32;
                    attacker->skillOnePosition.y = attacker->position.y - 32;
                    attacker->skillHitBox.x = attacker->position.x + 32;
                    attacker->skillHitBox.y = attacker->position.y - 32;
                }
               
                //update hitbox before drawing

                attacker->skillHitBox.w = 128;
                attacker->skillHitBox.h = 64;


                gf2d_sprite_draw_image(attacker->skillOneSprite, attacker->skillOnePosition);

                //check for collision here
                attacker->movementLock = 1;
                gf2d_draw_rect(attacker->skillHitBox, vector4d(76, 250, 129, 255));

                attacker->skillOneDurationCounter--;
                return;
            }
            else if (attacker->activeSkill == 1 && (attacker->skillOneDurationCounter <= 0))
            {
                attacker->movementLock = 0;
                attacker->activeSkill = 0;
                return;
            }
            else
            {
                return;
            }
            break;
        case 2:
            //slog("attempting throw");
            
            if (attacker->skillTwoDurationCounter > 0)
            {
                //do skill stuff
                if (attacker->facing == 0)
                {
                    attacker->skillTwoPosition.x = attacker->position.x - 256;
                    attacker->skillTwoPosition.y = attacker->position.y - 32;
                    attacker->skillHitBox.x = attacker->position.x - 256;
                    attacker->skillHitBox.y = attacker->position.y - 32;
                }
                else if (attacker->facing == 1)
                {
                    attacker->skillTwoPosition.x = attacker->position.x -32;
                    attacker->skillTwoPosition.y = attacker->position.y - 32;
                    attacker->skillHitBox.x = attacker->position.x -32;
                    attacker->skillHitBox.y = attacker->position.y - 32;
                }
                else
                {
                    attacker->skillTwoPosition.x = attacker->position.x + 256;
                    attacker->skillTwoPosition.y = attacker->position.y - 32;
                    attacker->skillHitBox.x = attacker->position.x + 256;
                    attacker->skillHitBox.y = attacker->position.y - 32;
                }
                //update hitbox before drawing

                attacker->skillHitBox.w = 256;
                attacker->skillHitBox.h = 32;


                gf2d_sprite_draw_image(attacker->skillTwoSprite, attacker->skillTwoPosition);

                //check for collision here
                attacker->movementLock = 1;
                gf2d_draw_rect(attacker->skillHitBox, vector4d(76, 250, 129, 255));

                attacker->skillTwoDurationCounter--;
                return;
            }
            else if (attacker->activeSkill == 2 && (attacker->skillTwoDurationCounter <= 0))
            {
                attacker->movementLock = 0;
                attacker->activeSkill = 0;
                return;
            }
            else
            {
                return;
            }
            break;
        case 3:

            if (attacker->skillThreeDurationCounter > 0)
            {
                //do skill stuff
                if (attacker->facing == 0)
                {
                    attacker->skillThreePosition.x = attacker->position.x - 64*3;
                    attacker->skillThreePosition.y = attacker->position.y - 220;
                    attacker->skillHitBox.x = attacker->position.x - 64*3;
                    attacker->skillHitBox.y = attacker->position.y - 220;
                }
                else if (attacker->facing == 1)
                {
                    attacker->skillThreePosition.x = attacker->position.x + 64;
                    attacker->skillThreePosition.y = attacker->position.y - 220;
                    attacker->skillHitBox.x = attacker->position.x + 64;
                    attacker->skillHitBox.y = attacker->position.y - 220;
                }
               
                //update hitbox before drawing

                attacker->skillHitBox.w = 64;
                attacker->skillHitBox.h = 256;


                gf2d_sprite_draw_image(attacker->skillThreeSprite, attacker->skillThreePosition);

                //check for collision here
                attacker->movementLock = 1;
                gf2d_draw_rect(attacker->skillHitBox, vector4d(76, 250, 129, 255));

                attacker->skillThreeDurationCounter--;
                return;
            }
            else if (attacker->activeSkill == 3 && (attacker->skillThreeDurationCounter <= 0))
            {
                attacker->movementLock = 0;
                attacker->activeSkill = 0;
                return;
            }
            else
            {
                return;
            }
            break;
        case 4:
            if (attacker->skillFourDurationCounter > 0)
            {
                //do skill stuff
              
                    attacker->skillFourPosition.x = attacker->position.x-256;
                    attacker->skillFourPosition.y = attacker->position.y-1000;
                    attacker->skillHitBox.x = attacker->position.x-256;
                    attacker->skillHitBox.y = attacker->position.y-1000;
                
              

                //update hitbox before drawing

                attacker->skillHitBox.w = 512;
                attacker->skillHitBox.h = 1024;


                gf2d_sprite_draw_image(attacker->skillFourSprite, attacker->skillFourPosition);

                //check for collision here
                attacker->movementLock = 1;
                gf2d_draw_rect(attacker->skillHitBox, vector4d(76, 250, 129, 255));

                attacker->skillFourDurationCounter--;
                return;
            }
            else if (attacker->activeSkill == 4 && (attacker->skillFourDurationCounter <= 0))
            {
                attacker->movementLock = 0;
                attacker->activeSkill = 0;
                return;
            }
            else
            {
                return;
            }
            break;
        }
        
    case 1: //------------------ loki skills ---------------------
        switch (skill)
        {
        case 1:

            if (attacker->skillOneDurationCounter > 0)
            {
                //do skill stuff
                if (attacker->facing == 0)
                {
                    attacker->skillOnePosition.x = attacker->position.x - 220;
                    attacker->skillOnePosition.y = attacker->position.y - 32;
                    attacker->skillHitBox.x = attacker->position.x - 220;
                    attacker->skillHitBox.y = attacker->position.y - 32;
                }
                else if (attacker->facing == 1)
                {
                    attacker->skillOnePosition.x = attacker->position.x + 32;
                    attacker->skillOnePosition.y = attacker->position.y - 32;
                    attacker->skillHitBox.x = attacker->position.x + 32;
                    attacker->skillHitBox.y = attacker->position.y - 32;
                }

                //update hitbox before drawing

                attacker->skillHitBox.w = 128;
                attacker->skillHitBox.h = 64;


                gf2d_sprite_draw_image(attacker->skillOneSprite, attacker->skillOnePosition);

                //check for collision here
                attacker->movementLock = 1;
                gf2d_draw_rect(attacker->skillHitBox, vector4d(76, 250, 129, 255));

                attacker->skillOneDurationCounter--;
                return;
            }
            else if (attacker->activeSkill == 1 && (attacker->skillOneDurationCounter <= 0))
            {
                attacker->movementLock = 0;
                attacker->activeSkill = 0;
                return;
            }
            else
            {
                return;
            }
            break;
        case 2:
            //slog("attempting throw");
            //slog("hello?? %i", attacker->skillTwoDurationCounter);
            if (attacker->skillTwoDurationCounter > 0)
            {
                //do skill stuff
               
                    //attacker->skillTwoPosition.x = attacker->position.x - 256;
                   // attacker->skillTwoPosition.y = attacker->position.y - 32;
                    //attacker->skillHitBox.x = attacker->position.x - 256;
                    //attacker->skillHitBox.y = attacker->position.y - 32;
               
                    

                //update hitbox before drawing

                //attacker->skillHitBox.w = 256;
                //attacker->skillHitBox.h = 32;


                //gf2d_sprite_draw_image(attacker->skillTwoSprite, attacker->skillTwoPosition);

                //check for collision here
                //attacker->movementLock = 1;
               // gf2d_draw_rect(attacker->skillHitBox, vector4d(76, 250, 129, 255));
                //slog("smoke active");
                gf2d_draw_rect(attacker->smokeArea, vector4d(30, 250, 30, 255));
                attacker->skillTwoPosition.x = attacker->smokeArea.x;
                attacker->skillTwoPosition.y = attacker->smokeArea.y;

                gf2d_sprite_draw_image(attacker->skillTwoSprite, attacker->skillTwoPosition);

                if (SDL_HasIntersection(&attacker->hitBox, &attacker->smokeArea))
                {
                    //slog("intersectin");
                    attacker->isCharInSmoke = 1;
                }
                else
                {
                    attacker->isCharInSmoke = 0;

                    //slog("not in da smoke");
                }


                attacker->skillTwoDurationCounter--;
                return;
            }
            else if (attacker->activeSkill == 2 && (attacker->skillTwoDurationCounter <= 0))
            {
                attacker->movementLock = 0;
                attacker->isSmokeActive = 0;
                attacker->isCharInSmoke = 0;
                attacker->activeSkill = 0;
                return;
            }
            else
            {
                return;
            }
            break;
        case 3:

            if (attacker->skillThreeDurationCounter > 0)
            {
                //do skill stuff
                if (attacker->facing == 0)
                {
                    attacker->skillThreePosition.x = attacker->position.x - 64 * 3;
                    attacker->skillThreePosition.y = attacker->position.y - 220;
                    attacker->skillHitBox.x = attacker->position.x - 64 * 3;
                    attacker->skillHitBox.y = attacker->position.y - 220;
                }
                else if (attacker->facing == 1)
                {
                    attacker->skillThreePosition.x = attacker->position.x + 64;
                    attacker->skillThreePosition.y = attacker->position.y - 220;
                    attacker->skillHitBox.x = attacker->position.x + 64;
                    attacker->skillHitBox.y = attacker->position.y - 220;
                }

                //update hitbox before drawing

                attacker->skillHitBox.w = 64;
                attacker->skillHitBox.h = 256;


                gf2d_sprite_draw_image(attacker->skillThreeSprite, attacker->skillThreePosition);

                //check for collision here
                attacker->movementLock = 1;
                gf2d_draw_rect(attacker->skillHitBox, vector4d(76, 250, 129, 255));

                attacker->skillThreeDurationCounter--;
                return;
            }
            else if (attacker->activeSkill == 3 && (attacker->skillThreeDurationCounter <= 0))
            {
                attacker->movementLock = 0;
                attacker->activeSkill = 0;
                return;
            }
            else
            {
                return;
            }
            break;
        case 4:
            if (attacker->skillFourDurationCounter > 0)
            {
                //do skill stuff

                attacker->skillFourPosition.x = attacker->position.x - 256;
                attacker->skillFourPosition.y = attacker->position.y - 1000;
                attacker->skillHitBox.x = attacker->position.x - 256;
                attacker->skillHitBox.y = attacker->position.y - 1000;



                //update hitbox before drawing

                attacker->skillHitBox.w = 512;
                attacker->skillHitBox.h = 1024;


                gf2d_sprite_draw_image(attacker->skillFourSprite, attacker->skillFourPosition);

                //check for collision here
                attacker->movementLock = 1;
                gf2d_draw_rect(attacker->skillHitBox, vector4d(76, 250, 129, 255));

                attacker->skillFourDurationCounter--;
                return;
            }
            else if (attacker->activeSkill == 4 && (attacker->skillFourDurationCounter <= 0))
            {
                attacker->movementLock = 0;
                attacker->activeSkill = 0;
                return;
            }
            else
            {
                return;
            }
            break;
        }

        break;
    case 2: //------------------ odin skills ---------------------
        break;
    case 3: //------------------ hela skills ---------------------
        break;
    case 4: //------------------ fenrir skills -------------------
        break;
    }

}