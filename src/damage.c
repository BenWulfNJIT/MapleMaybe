#include "damage.h"
#include "simple_logger.h"
#include "entity.h"
#include "items.h"

void InflictDamage(Entity* attacker, Entity* recipient, float damage)
{

	if (attacker->team == 1)
	{
		damage += attacker->damageBonus;

	}
	if (recipient->team == 1 && gfc_random() * 10 <= recipient->dodgeBonus)
	{
		//slog("avoided damage");
		recipient->damageBoostTime = 60;
	}

	if (recipient->team == -1) return;
	if (attacker->team == 1 && attacker->hasBFS == 1)
	{
		damage *= 10;
	}
	if (attacker->spawnMobNumber == 5 && recipient->team == 1 && recipient->hasMirrorShield)
	{
		damage = 0;
		recipient->isReflecting = 1;

	}
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
				if (attacker->level == 5 && attacker->activeQuest == 3)
				{
					attacker->activeQuest = 4;
				}
				attacker->experience -= 50;
				attacker->canUpgrade = 1;
			}
		}
		recipient->health = 0;
		recipient->movementLock = 1;
		if (attacker->team == 1)
		{
			int tempItemID = (int)(gfc_random() * 5 + 1);
			switch (tempItemID)
			{
			case 1:
				if (attacker->hasMirrorShield == 0) NewItem(recipient->position, tempItemID);
					break;
			case 2:

				break;
			case 3:
				if (attacker->hasSneakers == 0) NewItem(recipient->position, tempItemID);

				break;
			case 4:
				if (attacker->hasRegenBracelet == 0) NewItem(recipient->position, tempItemID);

				break;
			case 5:
				if (attacker->hasFireCape == 0) NewItem(recipient->position, tempItemID);

				break;
			}
			//if (tempItemID != 3) NewItem(recipient->position, tempItemID);
			//slog("%i",tempItemID);
		}
		if (recipient->spawnMobNumber == 6) attacker->canWin = 1;

		if (attacker->team == 1 && attacker->activeQuest == 2 && recipient->team == 2)
		{
			attacker->activeQuest = 3;
		}

		if (attacker->team == 1 && attacker->activeQuest == 5 && recipient->team == 2 && recipient->spawnMobNumber == 6)
		{
			attacker->activeQuest = 6;
		}

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
