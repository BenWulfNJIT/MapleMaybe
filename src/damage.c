#include "damage.h"
#include "simple_logger.h"
#include "entity.h"

void InflictDamage(Entity* attacker, Entity* recipient, float damage)
{
	if (recipient->team == -1) return;
	if (recipient->damageBoostTime && recipient->damageBoostTime > 0) damage = 0;
	else
	{

		if (recipient->team == 1 && damage > 10) damage = 10;

		//temp debug invinc
		//if (recipient->team == 1) damage = 0;
		
		if (recipient->team == 1 && (recipient->isCharInSmoke == 1 || recipient->canPurchase || recipient->talking) )
		{
			damage = 0;
			//slog("avoided");
		}
		if (recipient->team == 1 && recipient->thorns == 1)
		{
			InflictDamage(recipient, attacker, damage * 10);
		}
		recipient->health -= damage;
		if(recipient->team == 1) recipient->damageBoostTime = 60;
		
		

		//slog("Health Remaining: %i/%i", recipient->health, recipient->maxHealth);
	}
	//slog("health: %i", recipient->health);
	//slog("damage: %i", damage);


	if (recipient->health <= 0) 
	{
		if (attacker->team == 1)
		{
			attacker->experience += 12;
			attacker->currency += 100;
			if (attacker->experience >= 50)
			{
				attacker->level++;
				attacker->experience -= 50;
			}
		}
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
			damage = 25;
			break;
		case 2:
			damage = 100;
			break;
		case 3:
			damage = 100;
			break;
		case 4:
			damage = 300;
			break;
		default:
			damage = 0;
			break;
	}

	return damage;

}
