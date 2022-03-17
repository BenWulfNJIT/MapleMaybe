#ifndef __GFC_PHYSICS_H__
#define __GFC_PHYSICS_H__




typedef struct 
{
	float gravity;
	float MAX_FALL_SPEED;

}Physics;

/**
* @brief performs gravity on a specific entity
* @param entity to do gravity on
*/
void DoPlayerGravity(Entity* ent);


#endif
