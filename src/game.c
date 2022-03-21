#include <SDL.h>
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

int main(int argc, char * argv[])
{
    /*variable declarations*/
    int done = 0;
    const Uint8 * keys;
    Sprite *sprite, *test;
    
    int mx,my;
    float mf = 0;
    Sprite *mouse;
    Vector4D mouseColor = {255,100,255,200};
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
    gfc_input_init("config/input.cfg");

    /*demo setup*/
    sprite = gf2d_sprite_load_image("images/backgrounds/bg_flat.png");
    test = gf2d_sprite_load_all("images/fireball.png", 64, 64, 1);
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
    //test_player->skillOneSprite = gf2d_sprite_load_all("images/skills/fireball.png", 128, 64, 1);

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


            gf2d_sprite_draw(test, test_player->position, NULL, NULL, NULL, NULL, NULL, 1);
            //UI elements last
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

            vectormap_draw(testMap);

        gf2d_grahics_next_frame();// render current draw frame and skip to the next frame
        
        entity_update_all();
        entity_draw_all();
        //entity_update(bug);
    
        if (keys[SDL_SCANCODE_LEFTBRACKET]) test_player->level -= 1;
        if (keys[SDL_SCANCODE_RIGHTBRACKET]) test_player->level += 1;


        if (keys[SDL_SCANCODE_ESCAPE])done = 1; // exit condition
        //slog("Rendering at %f FPS",gf2d_graphics_get_frames_per_second());
    }
    slog("---==== END ====---");
    return 0;
}
/*eol@eof*/
