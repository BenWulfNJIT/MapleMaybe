#ifndef __ENTITY_H__
#define __ENTITY_H__
#include <SDL_mixer.h>
#include "gf2d_sprite.h"
#include "vector_map.h"
typedef struct Entity_S
{
    Uint8       _inuse;     /**<check if this entity in memory is active or not*/
    Sprite*     sprite;     /**<a pointer to the sprite that is used by this entity*/
    Sprite* healthBar;
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
    int         currency;
    int         level;
    Sprite* healthShop;
    Sprite* healthPotSprite;
    Sprite* talkDiag;

    Sprite* level1;
    Sprite* level2;
    Sprite* level3;
    Sprite* level4;
    Sprite* level5;
    Sprite* hp;
    Sprite* xp;


    int         canPurchase;
    int         shopping;
    int         healthPotCount;

    int         canTalk;
    int         talking;
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

    int         portalInMapID;
    int         portalTeleportMapID;
    int         playerCanTeleportToMapID;
    int         teleporting;

    int         team;  /**<default 0, 1 for friendly player, 2 for monsters, 3 for a portal, 4 for item, 5 for interactable objects>*/
    int         movementLock; /**<0 for default free to move, 1 to lock movement>*/

    int         isSmokeActive;
    SDL_Rect    smokeArea;
    int         isCharInSmoke;
    int         smokeTimer;
    int         damageBoostTime;



    //item info
    int         hasMirrorShield; /**0 for false 1 for true*/
    int         hasBFS; /**0 for false 1 for true*/
    int         hasSneakers; /**0 for false 1 for true*/
    int         hasRegenBracelet; /**0 for false 1 for true*/
    int         hasFireCape; /**0 for false 1 for true*/
    int         itemID;
    int         isMapOpen; /**0 for false 1 for true*/
    //Sprite*     map;
    //Sprite*     mapMarker;
    int         isReflecting; /**0 for false 1 for true*/


    SDL_Rect    itemRect;

    //interactables info
    SDL_Rect    objectRect;
    int         isSlowed;
    int         objectID; /**1 for grass, 2 for explosive, 3 for healthpot, 4 for chest, 5 for mimic*/
    int         showExplosion;
    int         showHealing;
    int         dashTimer;
    int         canWin;

    //ability upgrades info
    int         canUpgrade;
    int         healthBonus;
    int         damageBonus;
    int         healthSlot;
    int         moveSpeedBonus;
    int         dodgeBonus;

    //quest info
    int         activeQuest; /**quests 1-5*/
    int         questOpen;
    int         quest1Counter;

    //sound?
    Mix_Chunk* jumpNoise;

    int         pause;
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

    Vector2D odinLaserTarget;
    int thorns; /**<0 for false, 1 for true*/

    int dashing;

    float flySpeed;


    int gameState; /**<0 for main menu, 1 for normal game, 2 for level editor*/

    int isBlackHoleActive;
    int slowed;
    int carried;
    int doubleJump; /**<0 for not available, 1 for available*/
    float jumpPower;
    int floatTimer;
    void (*think)(struct Entity_S* self);   /**<called when an entity draws*/
    void (*touch)(struct Entity_S* self, struct Entity_S* other);   /**<called when an entity touches another entity*/

}Entity;

void SetCarried(Entity* carrier);
void ReleaseAllCarried();

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


void FreeCurrentMobs();


/**
 * @brief performs a collision check between a skill and all ents
 */
void SkillCollisionCheck(Entity* attacker, int skill, SDL_Rect* skillHitBox);

void BurnNearby();

/**
 * @brief draww every active entity
 */
void entity_draw_all();

void entity_draw(Entity* self);

Entity* GetPlayer();

Entity* GetNearestMob(Entity* self);

Entity* GetRandomMob();

void DoVacuum(Vector2D location);

void DamageBoost(Entity* ent, int time);
#endif