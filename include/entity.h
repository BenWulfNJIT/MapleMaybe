#ifndef __ENTITY_H__
#define __ENTITY_H__

#include "gf2d_sprite.h"
#include "vector_map.h"
typedef struct Entity_S
{
    Uint8       _inuse;     /**<check if this entity in memory is active or not*/
    Sprite*     sprite;     /**<a pointer to the sprite that is used by this entity*/
    int         state;
    float       frame;      /**<current frame for the sprite*/

    Vector2D    position;   /**<where the entity is in 2D space*/
    Vector2D    velocity;

    Vector2D    drawOffset;
    float       radius;     /**<how wide this entity is*/
    Vector2D    size;

    int         madebabies;
    Uint32      age;

    SDL_Rect    hitBox;
    SDL_Rect    skillHitBox;
    int         standingOnPlatform; /**<1 if true, 0 if false>*/
    int         knownPlatHeight;
    int         walkSpeed;
    int         jumpHeight;
    int         health;
    int         maxHealth;
    int         facing; /**<0 if left, 1 if right>*/
    int         classNum; /**<0 for thor, 1 for loki, 2 for odin, 3 for hela, 4 for fenrir> */
    int         experience;
    int         level;


    int         activeSkill; /**<default 0, 1 for auto, 2 for 2, 3 for 3, 4 for 4>*/
    //skill 1?
    int         skillOneCD;
    Vector2D    skillOnePosition;
    int         skillOneDurationCounter;
    int         skillOneInProgress; /**<0 if not, 1 if in progress> */
    Sprite*     skillOneSprite;

    //skill 2?
    int         skillTwoCD;
    Vector2D    skillTwoPosition;
    int         skillTwoDurationCounter;
    int         skillTwoInProgress; /**<0 if not, 1 if in progress> */
    Sprite*     skillTwoSprite;

    //skill 3?
    int         skillThreeCD;
    Vector2D    skillThreePosition;
    int         skillThreeDurationCounter;
    int         skillThreeInProgress; /**<0 if not, 1 if in progress> */
    Sprite*     skillThreeSprite;

    //skill 4?
    int         skillFourCD;
    Vector2D    skillFourPosition;
    int         skillFourDurationCounter;
    int         skillFourInProgress; /**<0 if not, 1 if in progress> */
    Sprite*     skillFourSprite;

    int         team;  /**<default 0, 1 for friendly player, 2 for monsters>*/
    int         movementLock; /**<0 for default free to move, 1 to lock movement>*/

    int         isSmokeActive;
    SDL_Rect    smokeArea;
    int         isCharInSmoke;
    int         smokeTimer;
    int         damageBoostTime;
    //Spawner info
    //Entity* entityToSpawn;
    Vector2D positionToSpawn;
    Vector2D spawnList;
    int frequencyToSpawn; //?
    int currentSpawnTime;
    int spawnCount;
    int spawnMax;
    int spawnMobNumber; /**<each mob has a number to spawn by, 1 for bug, 2 for man, 3 for jumper, 4 for roller, 5 for boss */ 

    int spawnBugCount;
    int spawnManCount;
    int spawnJumperCount;
    int spawnRollerCount;
    int spawnTurretCount;
    float mobSpeed;

    int laserTimer;
    Vector2D laserTarget;
    SDL_Rect laserExplosion;

    Vector4D standingPlatform;

    int dashing;
    void (*think)(struct Entity_S* self);   /**<called when an entity draws*/
    void (*touch)(struct Entity_S* self, struct Entity_S* other);   /**<called when an entity touches another entity*/

}Entity;

/**
 * @brief get a pointer to a new entity
 * @return NULL on out of memory or error, a pointer to a blank entity otherwise
 */
Entity* entity_new();

/**
 * @brief initialize the entity resource manager
 * @param maxEnts upper bound of maximum concurrent entities to be supported
 * @note must be called before creating a new entity
 */
void entity_manager_init(Uint32 maxEnts);

/**
 * @brief free a previously allocated entity
 * @param self a pointer to the entity to free
 */
void entity_free(Entity* self);

/**
 * @brief update every active entity
 */
void entity_update_all();

void entity_update(Entity* self);


/**
 * @brief performs a collision check between a skill and all ents
 */
void SkillCollisionCheck(Entity* attacker, int skill, SDL_Rect* skillHitBox);


/**
 * @brief draww every active entity
 */
void entity_draw_all();


Entity* GetPlayer();

Entity* GetNearestMob();


void DamageBoost(Entity* ent, int time);
#endif