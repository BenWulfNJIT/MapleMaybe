#include <SDL.h>
#include <SDL_ttf.h>
#include "gf2d_draw.h"
#include "gfc_input.h"
#include "gf2d_graphics.h"
#include "gf2d_sprite.h"
#include "simple_logger.h"
#include "entity.h"
#include "bug.h"
#include "vector_map.h"
#include "collision.h"
#include "physics.h"
#include "spawn.h"
#include "skill.h"
#include "shop.h"
#include "npc.h"

int main(int argc, char * argv[])
{
    /*variable declarations*/
    int done = 0;
    const Uint8 * keys;
    Sprite* sprite, * test;
    
    int mx,my, healthPercent;
    float mf = 0;
    Sprite *mouse;
    Sprite* healthBar;
    Vector4D mouseColor = {255,100,255,200};
    Vector4D healthColor = { 255,255,255,255 };

    VectorMap *testMap;
    Entity* bug, *test_player, *testSkill, *testSpawner, *bugSpawnList, 
        *manSpawner, *manSpawnList, 
        *jumperSpawner, *jumperSpawnList,
        *rollerSpawner, *rollerSpawnList,
        *turretSpawner, *turretSpawnList;
    

    /*program initializtion*/
    init_logger("gf2d.log");
    slog("---==== BEGIN ====---");
    gf2d_graphics_initialize(
        "gf2d",
        1200,
        720,
        1200,
        720,
        vector4d(0,0,0,255),
        0);
    gf2d_graphics_set_frame_delay(16);
    gf2d_sprite_init(1024);
    SDL_ShowCursor(SDL_DISABLE);
    entity_manager_init(1024);
    slog("test1");

    gfc_input_init("config/input.cfg");
    slog("test2");

    /*demo setup*/
//    sprite = gf2d_sprite_load_image("images/backgrounds/bg_flat.png");
    sprite = gf2d_sprite_load_image("images/backgrounds/crayonBackground.png");
   // test = gf2d_sprite_load_all("images//skills/fireball.png", 64, 64, 1);

    mouse = gf2d_sprite_load_all("images/pointer.png",32,32,16);
    /*main game loop*/

    //bug = bug_new(vector2d(100, 100), vector2d(gfc_crandom(), gfc_crandom()));

    Vector2D p1 = { 20, 670 };
    Vector2D p2 = { 1180, 670 };
    Vector4D pinkColor = { 255, 105, 190, 255 };

    testMap = vectormap_load("maps/test.json");
   

    testSkill = entity_new(vector2d(100, 100));
    test_player = player_new(vector2d(100, 100));
    test_player->classNum = 0;
    //test_player->skillOneSprite = gf2d_sprite_load_all("images/chars/loki.png", 64, 64, 1);
    slog("test3");


    Entity* shop;
    shop = shop_new(vector2d(100, 700));

    Entity* npc;
    npc = npc_new(vector2d(400, 260));

    bugSpawnList = entity_new();
    bugSpawnList = (Entity*)gfc_allocate_array(sizeof(Entity), 100);

    manSpawnList = entity_new();
    manSpawnList = (Entity*)gfc_allocate_array(sizeof(Entity), 100);

    jumperSpawnList = entity_new();
    jumperSpawnList = (Entity*)gfc_allocate_array(sizeof(Entity), 100);

    rollerSpawnList = entity_new();
    rollerSpawnList = (Entity*)gfc_allocate_array(sizeof(Entity), 100);

    turretSpawnList = entity_new();
    turretSpawnList = (Entity*)gfc_allocate_array(sizeof(Entity), 100);

    testSpawner = spawner_new(1, testMap->spawnerCoords[3], 3, 600);
    manSpawner = spawner_new(2, testMap->spawnerCoords[1], 5, 600);
    manSpawner->standingPlatform = testMap->platformCoords[2];
    jumperSpawner = spawner_new(3, testMap->spawnerCoords[2], 3, 1000);
    rollerSpawner = spawner_new(4, testMap->spawnerCoords[0], 2, 800);
    turretSpawner = spawner_new(5, testMap->spawnerCoords[4], 1, 5000);

    //for (int i = 0; i < 10; i++)
    //{
////    spawnList[i] = *bug_new(vector2d(gfc_random()*100, gfc_random()*100), vector2d(gfc_random(), gfc_random()));
   // }
    int experiencePercent;
    int testBoy = 25;
    for (int i = 0; i < 20; i++)
        slog("");
    while(!done)
    {
        SDL_PumpEvents();   // update SDL's internal event structures
        keys = SDL_GetKeyboardState(NULL); // get the keyboard state for this frame
        /*update things here*/

       // gfc_input_update();
        SDL_GetMouseState(&mx,&my);
        mf+=0.1;
        if (mf >= 16.0)mf = 0;
        
       

        gf2d_graphics_clear_screen();// clears drawing buffers
        // all drawing should happen betweem clear_screen and next_frame
            //backgrounds drawn first
            gf2d_sprite_draw_image(sprite,vector2d(0,0));

            //entity_draw_all();
            
            //entity_draw(bug);
            //bug->think;
            //SimplePlatformCollision(bug, testMap);
            //BoundingBoxCollision(bug, testMap);
            entity_draw(shop);
            shop_think(shop);

            entity_draw(npc);
            npc_think(npc);

            entity_draw(test_player);
            SimplePlatformCollision(test_player, testMap);
            BoundingBoxCollision(test_player, testMap);
            DoPlayerGravity(test_player);
            DoSkills(test_player);
            SkillThink(test_player, test_player->activeSkill, test_player->skillOnePosition);
            //slog("current skill: %i", test_player->activeSkill);
           // slog("skill 1 cd %i", test_player->skillOneCD);
           // slog("skill 1 duration %i", test_player->skillOneDurationCounter);

            //entity_update(&spawnList[7]);
            //entity_draw(&spawnList[7]);

          
                testSpawner->spawnCount = test_player->spawnBugCount;
                SpawnerThink(testSpawner, bugSpawnList, testMap);

                manSpawner->spawnCount = test_player->spawnManCount;
                SpawnerThink(manSpawner, manSpawnList, testMap);

                //for (int i = 0; i < manSpawner->spawnBugCount; i++)
              //  {
              //      SimplePlatformCollision(&manSpawnList[i], testMap);
              ////      BoundingBoxCollision(&manSpawnList[i], testMap);
               //     DoPlayerGravity(&manSpawnList[i]);
             //   }

                jumperSpawner->spawnCount = test_player->spawnJumperCount;
                SpawnerThink(jumperSpawner, jumperSpawnList, testMap);

                rollerSpawner->spawnCount = test_player->spawnRollerCount;
                SpawnerThink(rollerSpawner, rollerSpawnList, testMap);

                turretSpawner->spawnCount = test_player->spawnTurretCount;
                SpawnerThink(turretSpawner, turretSpawnList, testMap);
                //test_player->spawnBugCount = testSpawner->spawnCount;
            
            //slog("Bugs: %i", test_player->spawnBugCount);
            //slog("Men: %i", test_player->spawnManCount);

            //gf2d_draw_line(test_player->position, GetNearestMob()->position, vector4d(20, 20, 250, 255));


            vectormap_draw(testMap);

            //gf2d_sprite_draw(test, test_player->position, NULL, NULL, NULL, NULL, NULL, 1);
            //UI elements last
            //health/maxHealth * 512
            
            healthPercent = (int)(((float)test_player->health / (float)test_player->maxHealth) * 512);
            experiencePercent = (int)(((float)test_player->experience / (float)50) * 512);

            /*
            //slog("healthPercent: %i", healthPercent);
            //testBoy++;
            healthBar = gf2d_sprite_load_all("images/hud/healthBar.png", healthPercent, 32, 0);
            //slog("healthPercent: ")
            gf2d_sprite_draw(healthBar, vector2d(344, 20), NULL, NULL, NULL, NULL, &healthColor, 0);
            gf2d_sprite_free(healthBar);
            */
            
            for (int i = 0; i < healthPercent; i++)
            {
                Vector2D p1 = { (i + 344), 10 };
                Vector2D p2 = { (i + 344), 30 };

                gf2d_draw_line(p1, p2, vector4d(255, 20, 20, 255));
            }
            //slog("xp: %i",test_player->experience);
            for (int i = 0; i < experiencePercent; i++)
            {
                Vector2D p1 = { (i + 344), 40 };
                Vector2D p2 = { (i + 344), 60 };


                gf2d_draw_line(p1, p2, vector4d(255, 255, 20, 255));
            }
            if (test_player->shopping)
            {
                gf2d_sprite_draw_image(test_player->healthShop, vector2d(600-128, 360-128));

            }
            if (test_player->talking)
            {
                gf2d_sprite_draw_image(test_player->talkDiag, vector2d(600 - 128, 360 - 128));

            }
            int j = 20;
            for (int i = 0; i < test_player->healthPotCount; i++)
            {
                Vector2D spot;
                spot.x = j;
                    spot.y = 20;
                    j += 20;
                gf2d_sprite_draw_image(test_player->healthPotSprite, spot);

            }


            switch (test_player->level)
            {
            case 1:
                gf2d_sprite_draw_image(test_player->level1, vector2d(250, 10));

                break;
            case 2:
                gf2d_sprite_draw_image(test_player->level2, vector2d(250, 10));

                break;
            case 3:
                gf2d_sprite_draw_image(test_player->level3, vector2d(250, 10));

                break;
            case 4:
                gf2d_sprite_draw_image(test_player->level4, vector2d(250, 10));

                break;
            case 5:
                gf2d_sprite_draw_image(test_player->level5, vector2d(250, 10));

                break;
            default:
                gf2d_sprite_draw_image(test_player->level5, vector2d(250, 10));

                break;
            }
            gf2d_sprite_draw_image(test_player->hp, vector2d(300, 6));
            gf2d_sprite_draw_image(test_player->xp, vector2d(300, 40));


            gf2d_sprite_draw(
                mouse,
                vector2d(mx,my),
                NULL,
                NULL,
                NULL,
                NULL,
                &mouseColor,
                (int)mf);
                
           // if (keys[SDL_SCANCODE_SPACE]) test_player->velocity.y = -5;
           //gf2d_draw_line(p1, p2, pinkColor);
           // gf2d_draw_line();
   

        gf2d_grahics_next_frame();// render current draw frame and skip to the next frame

        entity_update_all();
        entity_draw_all();
        //entity_update(bug);
    
        if (keys[SDL_SCANCODE_LEFTBRACKET]) test_player->level -= 1;
        if (keys[SDL_SCANCODE_RIGHTBRACKET]) test_player->level += 1;

        if (keys[SDL_SCANCODE_Z])
        {
            test_player->sprite = gf2d_sprite_load_all("images/chars/thor.png", 64, 114, 1);

            test_player->skillOneSprite = gf2d_sprite_load_all("images/skills/thorSkill1.png", 128, 64, 1);
            test_player->skillTwoSprite = gf2d_sprite_load_all("images/skills/thorSkill2.png", 256, 32, 1);
            test_player->skillThreeSprite = gf2d_sprite_load_all("images/skills/thorSkill3.png", 64, 256, 1);
            test_player->skillFourSprite = gf2d_sprite_load_all("images/skills/thorSkill4.png", 512, 1024, 1);
            test_player->health = test_player->maxHealth;

            test_player->skillOneCD = 0;
            test_player->skillTwoCD = 0;
            test_player->skillThreeCD = 0;
            test_player->skillFourCD = 0;

            test_player->classNum = 0;
            test_player->level = 1;
            test_player->experience = 0;
        }
        if (keys[SDL_SCANCODE_X])
        {
            test_player->sprite = gf2d_sprite_load_all("images/chars/loki.png", 64, 114, 1);
            test_player->skillOneSprite = gf2d_sprite_load_all("images/skills/lokiSkill1.png", 128, 64, 1);
            test_player->skillTwoSprite = gf2d_sprite_load_all("images/skills/lokiSkill2.png", 256, 256, 1);
            test_player->skillThreeSprite = gf2d_sprite_load_all("images/skills/lokiSkill3.png", 128, 128, 1);
            test_player->skillFourSprite = gf2d_sprite_load_all("images/skills/lokiSkill4.png", 32, 32, 1);
            test_player->health = test_player->maxHealth;

            test_player->skillOneCD = 0;
            test_player->skillTwoCD = 0;
            test_player->skillThreeCD = 0;
            test_player->skillFourCD = 0;
            test_player->classNum = 1;
            test_player->level = 1;
            test_player->experience = 0;
        }
        if (keys[SDL_SCANCODE_C])
        {
            test_player->sprite = gf2d_sprite_load_all("images/chars/odin.png", 64, 114, 1);
            test_player->skillOneSprite = gf2d_sprite_load_all("images/skills/odinSkill1.png", 128, 64, 1);
            test_player->skillTwoSprite = gf2d_sprite_load_all("images/skills/odinSkill2.png", 32, 32, 1);
            test_player->skillThreeSprite = gf2d_sprite_load_all("images/skills/odinSkill3.png", 512, 32, 1);
            test_player->skillFourSprite = gf2d_sprite_load_all("images/skills/odinSkill4.png", 1024, 256, 1);
            test_player->health = test_player->maxHealth;

            test_player->skillOneCD = 0;
            test_player->skillTwoCD = 0;
            test_player->skillThreeCD = 0;
            test_player->skillFourCD = 0;
            test_player->classNum = 2;
            test_player->level = 1;
            test_player->experience = 0;
        }
        if (keys[SDL_SCANCODE_V])
        {
            test_player->sprite = gf2d_sprite_load_all("images/chars/hela.png", 64, 114, 1);
            test_player->skillOneSprite = gf2d_sprite_load_all("images/skills/helaSkill1.png", 128, 64, 1);
            test_player->skillTwoSprite = gf2d_sprite_load_all("images/skills/helaSkill2.png", 64, 64, 1);
            test_player->skillThreeSprite = gf2d_sprite_load_all("images/skills/helaSkill3.png", 64, 64, 1);
            test_player->skillFourSprite = gf2d_sprite_load_all("images/skills/helaSkill4.png", 128, 128, 1);
            test_player->health = test_player->maxHealth;

            test_player->skillOneCD = 0;
            test_player->skillTwoCD = 0;
            test_player->skillThreeCD = 0;
            test_player->skillFourCD = 0;
            test_player->classNum = 3;
            test_player->level = 1;
            test_player->experience = 0;
        }
        if (keys[SDL_SCANCODE_B])
        {
            test_player->sprite = gf2d_sprite_load_all("images/chars/fenrir.png", 64, 114, 1);
            test_player->skillOneSprite = gf2d_sprite_load_all("images/skills/fenrirSkill1.png", 128, 64, 1);
            test_player->skillTwoSprite = gf2d_sprite_load_all("images/skills/fenrirSkill2.png", 256, 64, 1);
            test_player->skillThreeSprite = gf2d_sprite_load_all("images/skills/fenrirSkill3.png", 64, 16, 1);
            test_player->skillFourSprite = gf2d_sprite_load_all("images/skills/fenrirSkill4.png", 128, 128, 1);
            test_player->health = test_player->maxHealth;
            test_player->skillOneCD = 0;
            test_player->skillTwoCD = 0;
            test_player->skillThreeCD = 0;
            test_player->skillFourCD = 0;
            test_player->classNum = 4;
            test_player->level = 1;
            test_player->experience = 0;
        }
        if (keys[SDL_SCANCODE_EQUALS])
        {
            test_player->health = test_player->maxHealth;
        }

        if (keys[SDL_SCANCODE_ESCAPE])done = 1; // exit condition
        //slog("Rendering at %f FPS",gf2d_graphics_get_frames_per_second());
    }
    slog("---==== END ====---");
    return 0;
}
/*eol@eof*/
