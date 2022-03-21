#include "damage.h"
#include "simple_logger.h"
#include "entity.h"

void InflictDamage(Entity* attacker, Entity* recipient, int damage)
{

	if (recipient->damageBoostTime && recipient->damageBoostTime > 0) damage = 0;
	else
	{
		recipient->health -= damage;
		if(recipient->team == 1) recipient->damageBoostTime = 60;
		slog("Health Remaining: %i/%i", recipient->health, recipient->maxHealth);
	}
	//slog("health: %i", recipient->health);
	//slog("damage: %i", damage);

	if (recipient->health <= 0) 
	{
		recipient->health = 0;
		recipient->movementLock = 1;
		if (recipient->team == 1) return;
		else entity_free(recipient);
		//slog("should kill");
	}

	
}

int GetDamage(int skill)
{
	int damage;

	switch (skill)
	{
		case 1:
			damage = 50;
			break;
		default:
			damage = 0;
			break;
	}

	return damage;

}
