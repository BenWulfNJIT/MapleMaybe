#include "damage.h"
#include "simple_logger.h"
#include "entity.h"

void InflictDamage(Entity* attacker, Entity* recipient, int damage)
{
	recipient->health -= damage;
	//slog("health: %i", recipient->health);
	//slog("damage: %i", damage);

	if (recipient->health <= 0) 
	{
		recipient->health = 0;
		recipient->movementLock = 1;
		entity_free(recipient);
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
