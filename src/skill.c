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
        "images/fireball.png",
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
    //slog("skill cd: %i", attacker->skillOneCD);
    if (attacker->skillOneDurationCounter > 0)
    {
        //do skill stuff
       // slog("hello");
        if (attacker->facing == 0)
        {
            attacker->skillOnePosition.x = attacker->position.x - (70 + attacker->skillOneSprite->frame_w);
            attacker->skillOnePosition.y = attacker->position.y - 32;
            attacker->skillHitBox.x = attacker->position.x - (70 + attacker->skillOneSprite->frame_w);
            attacker->skillHitBox.y = attacker->position.y - 32;
        }
        else if (attacker->facing == 1)
        {
            attacker->skillOnePosition.x = attacker->position.x + 70;
            attacker->skillOnePosition.y = attacker->position.y - 32;
            attacker->skillHitBox.x = attacker->position.x + 70;
            attacker->skillHitBox.y = attacker->position.y - 32;
        }
        else
        {
            attacker->skillOnePosition.x = attacker->position.x + 70;
            attacker->skillOnePosition.y = attacker->position.y - 32;
            attacker->skillHitBox.x = attacker->position.x + 70;
            attacker->skillHitBox.y = attacker->position.y - 32;
        }
       //update hitbox before drawing
       
        attacker->skillHitBox.w = 64;
        attacker->skillHitBox.h = 64;

        gf2d_sprite_draw_image(attacker->skillOneSprite, attacker->skillOnePosition);
        //check for collision here
        gf2d_draw_rect(attacker->skillHitBox, vector4d(76, 250, 129, 255));
        skillCollisionCheck(&attacker->skillHitBox);
        attacker->skillOneDurationCounter--;
        return;
    }
    else if (attacker->activeSkill != 0 && (attacker->skillOneDurationCounter <= 0))
    {
        //end skill and free ent
        slog("skill ended");
        //attacker->skillOneCD = 60;
        attacker->activeSkill = 0;
        //entity_free(skill);
        return;
    }
    else
    {
        //slog("Error?");
        return;
        //error and return
    }
}