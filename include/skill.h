#ifndef __SKILL_H__
#define __SKILL_H__

#include "entity.h"




Entity* skill_new(Entity* attacker, Vector2D position);
//void skill_free(Entity* skill);
void DoSkill(Entity* attacker, Entity* skill, Vector2D position);

void SkillThink(Entity* attacker, int skill, Vector2D position);

#endif