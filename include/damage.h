#ifndef __DAMAGE_H__
#define __DAMAGE_H__

#include "entity.h"


/**
 * @brief simple damage function
 * @param attacker - who is dealing the damage
 * @param recipient - who is taking the damage
 * @damage - raw int value of damage
 */
void InflictDamage(Entity* attacker, Entity* recipient, int damage);

int GetDamage(int skill);

#endif
