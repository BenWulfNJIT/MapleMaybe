#include <SDL.h>
#include <SDL_ttf.h>
#include <SDL_mixer.h>
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
#include "portal.h"
#include "player.h"
#include "menu.h"
#include "items.h"
#include "interactables.h"
#include "simple_json.h"
#include "editor.h"
#include "server.h"
#include <SDL_mixer.h>



int main(int argc, char * argv[])
{
    /*variable declarations*/
    int done = 0;
    const Uint8 * keys;
    Sprite* sprite, *mainMenu;
    int cueGameWin = 0;
    int mx,my, healthPercent;
    float mf = 0;
    Sprite *mouse;
    //Sprite* healthBar;
    Vector4D mouseColor = {255,100,255,200};
    Vector4D healthColor = { 255,255,255,255 };

    VectorMap *testMap;
    Entity *test_player, *testSkill, *testSpawner, *bugSpawnList, 
        *manSpawner, *manSpawnList, 
        *jumperSpawner, *jumperSpawnList,
        *rollerSpawner, *rollerSpawnList,
        *turretSpawner, *turretSpawnList, *portalLeft, *portalRight;
    
    SDL_Surface;
    //SDL_Texture;

    Entity* spawnerList;
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
    //slog("test1");

    // =========================== music testing ========================= 
    Mix_Music* music = NULL;

    if (Mix_OpenAudio(22050, MIX_DEFAULT_FORMAT, 2, 4096) == -1)
    {
        return false;
    }
    music = Mix_LoadMUS("audio/background.mp3");
    //If there was a problem loading the music
    if (music == NULL)
    {
        slog("Could not load music");
    }
    else
    {
        slog("should've loaded music");
    }
    // =========================== music testing ========================= 


    gfc_input_init("config/input.cfg");
    //slog("test2");

    /*demo setup*/

    mouse = gf2d_sprite_load_all("images/pointer.png",32,32,16);
    //mouse = gf2d_sprite_load_all("images/atest.png",32,32,2);

    /*main game loop*/


    Vector2D p1 = { 20, 670 };
    Vector2D p2 = { 1180, 670 };
    Vector4D pinkColor = { 255, 105, 190, 255 };

    testMap = vectormap_load("maps/testTown.json");
   
    mainMenu = gf2d_sprite_load_image("images/backgrounds/mainMenu.png");
    sprite = gf2d_sprite_load_image("images/backgrounds/town.png");

    Sprite* map = gf2d_sprite_load_image("images/map.png");
    Sprite* mapMarker = gf2d_sprite_load_image("images/mapMarker.png");

    Sprite* wonGame = gf2d_sprite_load_image("images/win.png");
    //portalLeft = portal_new(vector2d(-100, -100), 0, 0);
    portalLeft = portal_new(vector2d(100, 700), 0, 2);

    portalRight = portal_new(vector2d(1100, 700), 0, 1);

    testSkill = entity_new(vector2d(100, 100));
    test_player = player_new(vector2d(100, 600));
    test_player->classNum = 0;
    //test_player->skillOneSprite = gf2d_sprite_load_all("images/chars/loki.png", 64, 64, 1);
    slog("test3");
    Entity* shop;
    Entity* npc;

    


        //TODO
        //clean up spawning code for entities \/\/ is ugly



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

        spawnerList = entity_new();
        spawnerList = (Entity*)gfc_allocate_array(sizeof(Entity), 100);

        /*
        for (int i = 0; i < testMap->spawnerCount; i++)
        {
            spawnerList = spawner_new(testMap->spawnerInfo[i].x, testMap->spawnerCoords[i], testMap->spawnerInfo[i].y, testMap->spawnerInfo[i].z);
            //testMap->spawners = spawner_new(testMap->spawnerInfo[i].x, testMap->spawnerCoords[i], testMap->spawnerInfo[i].y, testMap->spawnerInfo[i].z);
            //testMap->spawners++;
            spawnerList++;
        }
        */

        slog("testaaaa");
        slog("mapID: %i", testMap->mapID);
        slog("testooooo");
        if (testMap->mapID == 1)
        {

            shop = shop_new(vector2d(-100, -700));

            npc = npc_new(vector2d(-400, -260));

        testSpawner = spawner_new(testMap->spawnerInfo[3].x, testMap->spawnerCoords[3], testMap->spawnerInfo[3].y, testMap->spawnerInfo[3].z);
        manSpawner = spawner_new(testMap->spawnerInfo[1].x, testMap->spawnerCoords[1], testMap->spawnerInfo[1].y, testMap->spawnerInfo[1].z);
        jumperSpawner = spawner_new(testMap->spawnerInfo[2].x, testMap->spawnerCoords[2], testMap->spawnerInfo[2].y, testMap->spawnerInfo[2].z);
        rollerSpawner = spawner_new(testMap->spawnerInfo[0].x, testMap->spawnerCoords[0], testMap->spawnerInfo[0].y, testMap->spawnerInfo[0].z);
        turretSpawner = spawner_new(testMap->spawnerInfo[4].x, testMap->spawnerCoords[4], testMap->spawnerInfo[4].y, testMap->spawnerInfo[4].z);
        }
        else if (testMap->mapID == 0)
        {

            shop = shop_new(vector2d(275, 700));

            npc = npc_new(vector2d(800, 700));


            testSpawner = spawner_new(1, vector2d(-100, -100), 0, 999999);
            manSpawner = spawner_new(1, vector2d(-100, -100), 0, 999999);
            jumperSpawner = spawner_new(1, vector2d(-100, -100), 0, 999999);
            rollerSpawner = spawner_new(1, vector2d(-100, -100), 0, 999999);
            turretSpawner = spawner_new(1, vector2d(-100, -100), 0, 999999);
        }
        else if(testMap->mapID == 2)
        {
            testSpawner = spawner_new(1, vector2d(-100, -100), 0, 999999);
            manSpawner = spawner_new(1, vector2d(-100, -100), 0, 999999);
            jumperSpawner = spawner_new(1, vector2d(-100, -100), 0, 999999);
            rollerSpawner = spawner_new(1, vector2d(-100, -100), 0, 999999);
            turretSpawner = spawner_new(1, vector2d(-100, -100), 0, 999999);


            shop = shop_new(vector2d(-100, -700));

            npc = npc_new(vector2d(-400, -260));
        }
        else
        {
            testSpawner = spawner_new(1, vector2d(-100, -100), 0, 999999);
            manSpawner = spawner_new(1, vector2d(-100, -100), 0, 999999);
            jumperSpawner = spawner_new(1, vector2d(-100, -100), 0, 999999);
            rollerSpawner = spawner_new(1, vector2d(-100, -100), 0, 999999);
            turretSpawner = spawner_new(1, vector2d(-100, -100), 0, 999999);


            shop = shop_new(vector2d(-100, -700));

            npc = npc_new(vector2d(-400, -260));
        }
 
    int experiencePercent;
    int testBoy = 25;
    for (int i = 0; i < 20; i++)
        slog("");
   




    // ============================ MENU INIT TESTING ============================================




    // ============================ MENU INIT TESTING ============================================


    SDL_Rect play = { 400, 390, 465, 135 };
    SDL_Rect levelEditor = { 415, 565, 485, 130 };

    Vector4D debugColor = { 240, 30, 30, 255 };

    Sprite* characterSelect = gf2d_sprite_load_image("images/characterSelect.png");
    Sprite* arrowRight = gf2d_sprite_load_image("images/arrowRight.png");
    Sprite* arrowLeft = gf2d_sprite_load_image("images/arrowLeft.png");
    int currentBackground = 1;

    SDL_Rect moveLeft = {0,0,64,32};
    SDL_Rect moveRight = {1200-64,0,64,32};

    SDL_Rect thorSelect = { 75, 300, 175, 275 };
    SDL_Rect lokiSelect = { 300, 300, 175, 275 };
    SDL_Rect odinSelect = { 530, 300, 175, 275 };
    SDL_Rect helaSelect = { 758, 300, 175, 275 };
    SDL_Rect fenrirSelect = { 970, 300, 175, 275 };

    int selecting = 0;

    Sprite* pauseMenu = gf2d_sprite_load_image("images/pause.png");
    SDL_Rect continuebutton = {257, 386, 317,143};
    SDL_Rect quitButton = {689, 394, 317, 143};


    while (test_player->gameState == 0)
    {

        SDL_PumpEvents();   // update SDL's internal event structures
        keys = SDL_GetKeyboardState(NULL); // get the keyboard state for this frame
        /*update things here*/

       // gfc_input_update();
        SDL_GetMouseState(&mx, &my);
        mf += 0.1;
        if (mf >= 16.0)mf = 0;

        SDL_Rect mouseRect = { mx, my, 2, 2 };


        gf2d_graphics_clear_screen();// clears drawing buffers
        // all drawing should happen betweem clear_screen and next_frame
            //backgrounds drawn first



        gf2d_sprite_draw_image(mainMenu, vector2d(0, 0));

       // gf2d_draw_rect(play, debugColor);
        //gf2d_draw_rect(levelEditor, debugColor);
       // gf2d_draw_rect(mouseRect, debugColor);


        gf2d_sprite_draw(
            mouse,
            vector2d(mx, my),
            NULL,
            NULL,
            NULL,
            NULL,
            &mouseColor,
            (int)mf);
        Sprite* editorMenu = gf2d_sprite_load_image("images/editorMenu.png");
        SDL_Rect editDemo1 = {525, 260, 200,60};
        SDL_Rect editDemo2 = { 525, 320, 200,60 };
        SDL_Rect editDemo3 = { 525, 380, 200,60 };

        int changingMap = 0;
        int editing = 0;
        int drawing = 0;
        Vector2D startPoint, endPoint;
        int startLevelEditor = 0;
        int addedPlatCount = 0;
        int currentSprite = 0;
        if (SDL_GetMouseState(&mx, &my) == 1 && SDL_HasIntersection(&mouseRect, &levelEditor))
        {
            startLevelEditor = 1;
            while (startLevelEditor == 1)
            {
                SDL_PumpEvents();
                keys = SDL_GetKeyboardState(NULL);
                SDL_GetMouseState(&mx, &my);
                mf += 0.1;
                if (mf >= 16.0)mf = 0;

                SDL_Rect mouseRect = { mx, my, 2, 2 };
                gf2d_graphics_clear_screen();


                gf2d_sprite_draw_image(editorMenu, vector2d(525, 260));
                if (SDL_HasIntersection(&mouseRect, &editDemo1))
                {
                    gf2d_draw_rect(editDemo1, vector4d(255,0,0,255));
                }
                if (SDL_HasIntersection(&mouseRect, &editDemo2))
                {
                    gf2d_draw_rect(editDemo2, vector4d(255, 0, 0, 255));
                }
                if (SDL_HasIntersection(&mouseRect, &editDemo3))
                {
                    gf2d_draw_rect(editDemo3, vector4d(255, 0, 0, 255));
                }
                if(SDL_GetMouseState(&mx, &my) == 1 && SDL_HasIntersection(&mouseRect, &editDemo2))
                {
                    editing = 1;
                    
                    SJson* editMap;
                    Vector4D* platList;
                    Sprite* editBackgroundSprite;
                    int platformCount;
                    int tempCoord1, tempCoord2, tempCoord3, tempCoord4;
                    platList = (Vector4D*)gfc_allocate_array(sizeof(Vector4D), 20);

                    editMap = sj_load("maps/testTown.json");
                    if (!editMap) slog("Failed to load map to edit");

                    char* backgroundSpriteName = sj_get_string_value(sj_object_get_value(editMap, "background"));
                    if (!backgroundSpriteName) slog("Failed to get background sprite name");

                    editBackgroundSprite = gf2d_sprite_load_image(backgroundSpriteName);
                    platformCount = sj_array_get_count(sj_object_get_value(editMap, "platforms"));
                    slog("num platforms: %i", platformCount);
                    for (int i = 0; i < platformCount; i++)
                    {
                        sj_get_integer_value (sj_array_get_nth(sj_array_get_nth(sj_object_get_value(editMap, "platforms"), i), 0), &tempCoord1);
                        //slog("Wild test1: %i", tempCoord1);
                        sj_get_integer_value(sj_array_get_nth(sj_array_get_nth(sj_object_get_value(editMap, "platforms"), i), 1), &tempCoord2);
                        //slog("Wild test2: %i", tempCoord2);
                        sj_get_integer_value(sj_array_get_nth(sj_array_get_nth(sj_object_get_value(editMap, "platforms"), i), 2), &tempCoord3);
                        //slog("Wild test3: %i", tempCoord3);
                        sj_get_integer_value(sj_array_get_nth(sj_array_get_nth(sj_object_get_value(editMap, "platforms"), i), 3), &tempCoord4);
                        //slog("Wild test4: %i", tempCoord4);

                        platList[i].x = tempCoord1;
                        platList[i].y = tempCoord2;
                        platList[i].z = tempCoord3;
                        platList[i].w = tempCoord4;

                    }
                   
                    //load json stuff here
                    //save into variables
                    //free json
                    //sj_free(editMap);
                    while (editing == 1)
                    {
                        //draw background
                        //handle user input to edit
                        //draw platforms
                        //give them a button to escape
                        SDL_PumpEvents();
                        keys = SDL_GetKeyboardState(NULL);
                        SDL_GetMouseState(&mx, &my);
                        mf += 0.1;
                        if (mf >= 16.0)mf = 0;

                        SDL_Rect mouseRect = { mx, my, 2, 2 };
                        gf2d_graphics_clear_screen();
                        gf2d_sprite_draw_image(editBackgroundSprite, vector2d(0, 0));
                        gf2d_sprite_draw_image(arrowRight, vector2d(1200-64, 0));
                        gf2d_sprite_draw_image(arrowLeft, vector2d(0, 0));
                       // gf2d_draw_rect(moveLeft, vector4d(255, 0, 0, 255));
                       // gf2d_draw_rect(moveRight, vector4d(255, 0, 0, 255));

                        //draw plats
                        for (int i = 0; i < platformCount + addedPlatCount+ 1; i++)
                        {
                           
                           // if (!&platList[i])continue;
                            gf2d_draw_line(vector2d(platList[i].x,platList[i].y), vector2d(platList[i].z, platList[i].w), vector4d(255, 0, 0, 255));
                        }

                        
                        if (SDL_GetMouseState(&mx, &my) == 1 && drawing == 0)
                        {
                            drawing = 1;
                            startPoint.x = mx;
                            startPoint.y = my;
                        }
                       // slog("Mouse State: %i", SDL_GetMouseState(&mx, &my));
                        if (SDL_GetMouseState(&mx, &my) == 4)
                        {
                            
                            //slog("trying to erase");
                            for (int i = 0; i < platformCount + addedPlatCount+1; i++)
                            {
                                if (mx > platList[i].x && mx < platList[i].z && my == platList[i].y)
                                {
                                    platList[i].x = -1;
                                    platList[i].y = -1;
                                    platList[i].z = -1;
                                    platList[i].w = -1;

                                }
                            }
                        }
                        if (drawing == 1)
                        {
                            
                            gf2d_draw_line(startPoint, vector2d(mx, startPoint.y), vector4d(255, 0, 0, 255));
                            if (SDL_GetMouseState(&mx, &my) != 1)
                            {
                                drawing = 0;
                                //save platform here
                                endPoint.x = mx;
                                endPoint.y = startPoint.y;
                                if (abs(endPoint.x - startPoint.x) < 15) continue;

                                addedPlatCount++;
                                platList[platformCount + addedPlatCount].x = startPoint.x;
                                platList[platformCount + addedPlatCount].y = startPoint.y;
                                platList[platformCount + addedPlatCount].z = endPoint.x;
                                platList[platformCount + addedPlatCount].w = endPoint.y;

                                slog("Count: %i", platformCount + addedPlatCount);
                                /*
                              SJson* arrayTest = sj_array_new();

                              sj_array_append(arrayTest,sj_new_float(platList[platformCount + addedPlatCount].x));
                              sj_array_append(arrayTest, sj_new_float(platList[platformCount + addedPlatCount].y));
                              sj_array_append(arrayTest, sj_new_float(platList[platformCount + addedPlatCount].z));
                              sj_array_append(arrayTest, sj_new_float(platList[platformCount + addedPlatCount].w));


                              sj_array_append(sj_object_get_value(editMap, "platforms"), arrayTest);
                              
                              sj_save(editMap, "maps/testTown.json");

                             */


                        
                            }
                        }



                        gf2d_sprite_draw(
                            mouse,
                            vector2d(mx, my),
                            NULL,
                            NULL,
                            NULL,
                            NULL,
                            &mouseColor,
                            (int)mf);
                        if ((SDL_GetMouseState(&mx, &my) == 1)  && (SDL_HasIntersection(&mouseRect, &moveRight)) && (currentBackground <= 3) && changingMap == 0)
                        {
                            slog("entered");
                            changingMap = 1;
                            currentBackground++;

                            switch (currentBackground)
                            {
                            case 1:
                                editBackgroundSprite = gf2d_sprite_load_image("images/backgrounds/town.png");
                                break;
                            case 2:
                                editBackgroundSprite = gf2d_sprite_load_image("images/backgrounds/crayonBackground.png");
                                break;
                            case 3:
                                editBackgroundSprite = gf2d_sprite_load_image("images/backgrounds/demo.png");

                                break;
                            case 4:
                                editBackgroundSprite = gf2d_sprite_load_image("images/backgrounds/town2.png");

                                break;
                          
                            }

                        }
                        if ((SDL_GetMouseState(&mx, &my) == 1) && (SDL_HasIntersection(&mouseRect, &moveLeft)) && (currentBackground >= 2) && changingMap == 0)
                        {
                            slog("entered");
                            changingMap = 1;
                            currentBackground--;

                            switch (currentBackground)
                            {
                            case 1:
                                editBackgroundSprite = gf2d_sprite_load_image("images/backgrounds/town.png");
                                break;
                            case 2:
                                editBackgroundSprite = gf2d_sprite_load_image("images/backgrounds/crayonBackground.png");
                                break;
                            case 3:
                                editBackgroundSprite = gf2d_sprite_load_image("images/backgrounds/demo.png");

                                break;
                            case 4:
                                editBackgroundSprite = gf2d_sprite_load_image("images/backgrounds/town2.png");

                                break;

                            }

                        }
                        if (changingMap == 1 && SDL_GetMouseState(&mx, &my) != 1)changingMap = 0;

                        gf2d_grahics_next_frame();
                        
                        if (keys[SDL_SCANCODE_ESCAPE] == 1)
                        {
                            editing = 0;
                            done = 0;
                            startLevelEditor = 0;
                           /*
                            int tempCount = sj_array_get_count(sj_object_get_value(editMap, "platforms"));
                            slog("file count: %i, platCount: %i", tempCount, platformCount);
                           //slog("ending count: %i", sj_array_get_count(sj_object_get_value(editMap, "platforms")));
                            for (int i = 0; i < tempCount; i++)
                            {
                                int tempx, tempy, tempz, tempw;
                                
                                sj_array_get_nth(sj_object_get_value(editMap, "platforms"), i);
                                sj_get_integer_value(sj_array_get_nth(sj_array_get_nth(sj_object_get_value(editMap, "platforms"), i), 0), &tempx);
                                sj_get_integer_value(sj_array_get_nth(sj_array_get_nth(sj_object_get_value(editMap, "platforms"), i), 1), &tempy);
                                sj_get_integer_value(sj_array_get_nth(sj_array_get_nth(sj_object_get_value(editMap, "platforms"), i), 2), &tempz);
                                sj_get_integer_value(sj_array_get_nth(sj_array_get_nth(sj_object_get_value(editMap, "platforms"), i), 3), &tempw);
                                

                                slog("FileCoord: [%i, %i, %i, %i]", tempx, tempy, tempz, tempw);
                                slog("platListCoords: [%i, %i, %i, %i]", (int)platList[i+1].x, (int)platList[i+1].y, (int)platList[i+1].z, (int)platList[i+1].w);

                                if ((int)platList[i + 1].x == -1 && (int)platList[i + 1].y == -1 && (int)platList[i + 1].z == -1 && (int)platList[i + 1].w == -1)
                                {
                                    slog("Found bad plat");
                                }

                            }
                            */


                            // ========================== SAVE TESTING ========================================
                            
                           SJson* arrayTest = sj_array_new();

                            //sj_array_append(arrayTest, sj_new_float(platList[platformCount + addedPlatCount].x));
                            //sj_array_append(arrayTest, sj_new_float(platList[platformCount + addedPlatCount].y));
                            //sj_array_append(arrayTest, sj_new_float(platList[platformCount + addedPlatCount].z));
                            //sj_array_append(arrayTest, sj_new_float(platList[platformCount + addedPlatCount].w));
                         
                            for (int i = 0; i < addedPlatCount; i++)
                            {
                                //slog("maybe? [%f], [%f], [%f], [%f]", platList[platformCount + i + 1].x, platList[platformCount + i + 1].y, platList[platformCount + i + 1].z, platList[platformCount + i + 1].w);
                                if (platList[platformCount + i + 1].x == -1)continue;
                                sj_array_append(arrayTest, sj_new_float(platList[platformCount + i + 1].x));
                                sj_array_append(arrayTest, sj_new_float(platList[platformCount + i + 1].y));
                                sj_array_append(arrayTest, sj_new_float(platList[platformCount + i + 1].z));
                                sj_array_append(arrayTest, sj_new_float(platList[platformCount + i + 1].w));

                                sj_array_append(sj_object_get_value(editMap, "platforms"), arrayTest);

                                arrayTest = NULL;
                                arrayTest = sj_array_new();

                            }
                            //sj_array_append(sj_object_get_value(editMap, "platforms"), arrayTest);

                            //SJson *temp = sj_object_get_value(editMap, "background");
                           // temp = sj_new_str("AAAAAAAAA");
                           // sj_echo(editMap);
                           // sj_echo(temp);
                            //sj_object_get_value(editMap, "background") = temp;
                            //sj_object_insert(editMap, "background", temp);
                           // sj_echo(testingSprite);
                          ////  testingSprite = sj_new_str("aaa");
                           // sj_echo(testingSprite);
                           // sj_save(testingSprite, "maps/testTown.json");
                            
                            //sj_object_delete_key(sj_object_get_value(editMap, "background"), "background");
                            
                            //sj_object_insert(testingSprite, "background", sj_new_str("aaaa"));
                            //sj_array_append(sj_object_get_value(editMap, "background"), testingSprite);
                           // sj_object_insert(editMap,"background", NULL);
                            
                          

                           sj_save(editMap, "maps/testTown.json");


                          
                            
                            // ========================== SAVE TESTING ========================================


                        }
                    }
                }
                gf2d_sprite_draw(
                    mouse,
                    vector2d(mx, my),
                    NULL,
                    NULL,
                    NULL,
                    NULL,
                    &mouseColor,
                    (int)mf);

                gf2d_grahics_next_frame();
            }

        }
        //C:\Users\bdwul\NJIT\Spring22\IT276\Game2D\maps
        if (SDL_GetMouseState(&mx, &my) == 1 && SDL_HasIntersection(&mouseRect, &play))
        {
            slog("enter game");

            for (int i = 255; i > 0; i -= 2)
            {
                gf2d_graphics_clear_screen();

                gf2d_sprite_draw_image(mainMenu, vector2d(0, 0));

                SDL_SetTextureColorMod(
                    mainMenu->texture,
                    i,
                    i,
                    i);
                SDL_SetTextureAlphaMod(
                    mainMenu->texture,
                    i);
                SDL_SetTextureColorMod(
                    test_player->sprite->texture,
                    i,
                    i,
                    i);
                SDL_SetTextureAlphaMod(
                    test_player->sprite->texture,
                    i);
                gf2d_grahics_next_frame();

            }

            

            for (int i = 0; i < 255; i += 2)
            {
                gf2d_graphics_clear_screen();

                gf2d_sprite_draw_image(characterSelect, vector2d(0, 0));

                //entity_draw(test_player);

                SDL_SetTextureColorMod(
                    characterSelect->texture,
                    i,
                    i,
                    i);
                SDL_SetTextureAlphaMod(
                    characterSelect->texture,
                    i);
/*
                SDL_SetTextureColorMod(
                    test_player->sprite->texture,
                    i,
                    i,
                    i);
                SDL_SetTextureAlphaMod(
                    test_player->sprite->texture,
                    i);
                    */
               
                selecting = 1;
                    gf2d_grahics_next_frame();

            }
            //test_player->gameState = 1;
        }
        while (selecting == 1)
        {
            SDL_PumpEvents();   // update SDL's internal event structures
            keys = SDL_GetKeyboardState(NULL); // get the keyboard state for this frame
            /*update things here*/

           // gfc_input_update();
            SDL_GetMouseState(&mx, &my);
            mf += 0.1;
            if (mf >= 16.0)mf = 0;

            SDL_Rect mouseRect = { mx, my, 2, 2 };


            gf2d_graphics_clear_screen();// clears drawing buffers
            // all drawing should happen betweem clear_screen and next_frame
                //backgrounds drawn first



            gf2d_sprite_draw_image(characterSelect, vector2d(0, 0));

            // gf2d_draw_rect(play, debugColor);
             //gf2d_draw_rect(levelEditor, debugColor);
            // gf2d_draw_rect(mouseRect, debugColor);
            //gf2d_draw_rect(thorSelect, vector4d(245, 10, 245, 255));
            //gf2d_draw_rect(lokiSelect, vector4d(245, 10, 245, 255));
            //gf2d_draw_rect(odinSelect, vector4d(245, 10, 245, 255));
           // gf2d_draw_rect(helaSelect, vector4d(245, 10, 245, 255));
           // gf2d_draw_rect(fenrirSelect, vector4d(245, 10, 245, 255));

            gf2d_sprite_draw(
                mouse,
                vector2d(mx, my),
                NULL,
                NULL,
                NULL,
                NULL,
                &mouseColor,
                (int)mf);


            // ================== begin class select shiz =======================
            if (SDL_GetMouseState(&mx, &my) == 1 && SDL_HasIntersection(&mouseRect, &thorSelect))
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
                for (int i = 255; i > 0; i -= 2)
                {
                    gf2d_graphics_clear_screen();

                    gf2d_sprite_draw_image(characterSelect, vector2d(0, 0));

                    SDL_SetTextureColorMod(
                        characterSelect->texture,
                        i,
                        i,
                        i);
                    SDL_SetTextureAlphaMod(
                        characterSelect->texture,
                        i);
                    SDL_SetTextureColorMod(
                        test_player->sprite->texture,
                        i,
                        i,
                        i);
                    SDL_SetTextureAlphaMod(
                        test_player->sprite->texture,
                        i);
                    gf2d_grahics_next_frame();

                }

                for (int i = 0; i < 255; i += 2)
                {
                    gf2d_graphics_clear_screen();

                    gf2d_sprite_draw_image(sprite, vector2d(0, 0));

                    entity_draw(test_player);

                    SDL_SetTextureColorMod(
                        sprite->texture,
                        i,
                        i,
                        i);
                    SDL_SetTextureAlphaMod(
                        sprite->texture,
                        i);

                    SDL_SetTextureColorMod(
                        test_player->sprite->texture,
                        i,
                        i,
                        i);
                    SDL_SetTextureAlphaMod(
                        test_player->sprite->texture,
                        i);


                    gf2d_grahics_next_frame();

                }
                selecting = 0;
                test_player->gameState = 1;
            }
            if (SDL_GetMouseState(&mx, &my) == 1 && SDL_HasIntersection(&mouseRect, &lokiSelect))
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
                for (int i = 255; i > 0; i -= 2)
                {
                    gf2d_graphics_clear_screen();

                    gf2d_sprite_draw_image(characterSelect, vector2d(0, 0));

                    SDL_SetTextureColorMod(
                        characterSelect->texture,
                        i,
                        i,
                        i);
                    SDL_SetTextureAlphaMod(
                        characterSelect->texture,
                        i);
                    SDL_SetTextureColorMod(
                        test_player->sprite->texture,
                        i,
                        i,
                        i);
                    SDL_SetTextureAlphaMod(
                        test_player->sprite->texture,
                        i);
                    gf2d_grahics_next_frame();

                }

                for (int i = 0; i < 255; i += 2)
                {
                    gf2d_graphics_clear_screen();

                    gf2d_sprite_draw_image(sprite, vector2d(0, 0));

                    entity_draw(test_player);

                    SDL_SetTextureColorMod(
                        sprite->texture,
                        i,
                        i,
                        i);
                    SDL_SetTextureAlphaMod(
                        sprite->texture,
                        i);

                    SDL_SetTextureColorMod(
                        test_player->sprite->texture,
                        i,
                        i,
                        i);
                    SDL_SetTextureAlphaMod(
                        test_player->sprite->texture,
                        i);


                    gf2d_grahics_next_frame();

                }
                selecting = 0;
                test_player->gameState = 1;
            }
            if (SDL_GetMouseState(&mx, &my) == 1 && SDL_HasIntersection(&mouseRect, &odinSelect))
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
                for (int i = 255; i > 0; i -= 2)
                {
                    gf2d_graphics_clear_screen();

                    gf2d_sprite_draw_image(characterSelect, vector2d(0, 0));

                    SDL_SetTextureColorMod(
                        characterSelect->texture,
                        i,
                        i,
                        i);
                    SDL_SetTextureAlphaMod(
                        characterSelect->texture,
                        i);
                    SDL_SetTextureColorMod(
                        test_player->sprite->texture,
                        i,
                        i,
                        i);
                    SDL_SetTextureAlphaMod(
                        test_player->sprite->texture,
                        i);
                    gf2d_grahics_next_frame();

                }

                for (int i = 0; i < 255; i += 2)
                {
                    gf2d_graphics_clear_screen();

                    gf2d_sprite_draw_image(sprite, vector2d(0, 0));

                    entity_draw(test_player);

                    SDL_SetTextureColorMod(
                        sprite->texture,
                        i,
                        i,
                        i);
                    SDL_SetTextureAlphaMod(
                        sprite->texture,
                        i);

                    SDL_SetTextureColorMod(
                        test_player->sprite->texture,
                        i,
                        i,
                        i);
                    SDL_SetTextureAlphaMod(
                        test_player->sprite->texture,
                        i);


                    gf2d_grahics_next_frame();

                }
                selecting = 0;
                test_player->gameState = 1;
            }
            if (SDL_GetMouseState(&mx, &my) == 1 && SDL_HasIntersection(&mouseRect, &helaSelect))
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
                for (int i = 255; i > 0; i -= 2)
                {
                    gf2d_graphics_clear_screen();

                    gf2d_sprite_draw_image(characterSelect, vector2d(0, 0));

                    SDL_SetTextureColorMod(
                        characterSelect->texture,
                        i,
                        i,
                        i);
                    SDL_SetTextureAlphaMod(
                        characterSelect->texture,
                        i);
                    SDL_SetTextureColorMod(
                        test_player->sprite->texture,
                        i,
                        i,
                        i);
                    SDL_SetTextureAlphaMod(
                        test_player->sprite->texture,
                        i);
                    gf2d_grahics_next_frame();

                }

                for (int i = 0; i < 255; i += 2)
                {
                    gf2d_graphics_clear_screen();

                    gf2d_sprite_draw_image(sprite, vector2d(0, 0));

                    entity_draw(test_player);

                    SDL_SetTextureColorMod(
                        sprite->texture,
                        i,
                        i,
                        i);
                    SDL_SetTextureAlphaMod(
                        sprite->texture,
                        i);

                    SDL_SetTextureColorMod(
                        test_player->sprite->texture,
                        i,
                        i,
                        i);
                    SDL_SetTextureAlphaMod(
                        test_player->sprite->texture,
                        i);


                    gf2d_grahics_next_frame();

                }
                selecting = 0;
                test_player->gameState = 1;
            }
            if (SDL_GetMouseState(&mx, &my) == 1 && SDL_HasIntersection(&mouseRect, &fenrirSelect))
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

                for (int i = 255; i > 0; i -= 2)
                {
                    gf2d_graphics_clear_screen();

                    gf2d_sprite_draw_image(characterSelect, vector2d(0, 0));

                    SDL_SetTextureColorMod(
                        characterSelect->texture,
                        i,
                        i,
                        i);
                    SDL_SetTextureAlphaMod(
                        characterSelect->texture,
                        i);
                    SDL_SetTextureColorMod(
                        test_player->sprite->texture,
                        i,
                        i,
                        i);
                    SDL_SetTextureAlphaMod(
                        test_player->sprite->texture,
                        i);
                    gf2d_grahics_next_frame();

                }

                for (int i = 0; i < 255; i += 2)
                {
                    gf2d_graphics_clear_screen();

                    gf2d_sprite_draw_image(sprite, vector2d(0, 0));

                    entity_draw(test_player);

                    SDL_SetTextureColorMod(
                        sprite->texture,
                        i,
                        i,
                        i);
                    SDL_SetTextureAlphaMod(
                        sprite->texture,
                        i);
                    
                    SDL_SetTextureColorMod(
                                        test_player->sprite->texture,
                                        i,
                                        i,
                                        i);
                     SDL_SetTextureAlphaMod(
                                        test_player->sprite->texture,
                                        i);
                                        

                    gf2d_grahics_next_frame();

                }

                selecting = 0;
                test_player->gameState = 1;
            }

               

            // ================== end class select shiz   =======================
            gf2d_grahics_next_frame();

        }

        gf2d_grahics_next_frame();// render current draw frame and skip to the next frame
    }
    
    //Entity* itemTest = NewItem(vector2d(100, 100), 1);
    
    Sprite* mirrorSprite = gf2d_sprite_load_image("images/items/mirrorShield.png");
    Sprite*  BFSSprite = gf2d_sprite_load_image("images/items/BFS.png");
    Sprite*  sneakersSprite= gf2d_sprite_load_image("images/items/sneakers.png");
    Sprite* regenBraceletSprite = gf2d_sprite_load_image("images/items/regenBracelet.png");
    Sprite* fireCapeSprite = gf2d_sprite_load_image("images/items/fireCape.png");
    Sprite* healingSprite = gf2d_sprite_load_image("images/healing.png");

    int regenTimer = 0;
    int reflectTimer = 0;


    // =============== object shenanigans ====================

    Sprite* grassSprite = gf2d_sprite_load_image("images/grass.png");
    Sprite* explosiveBarrelSprite = gf2d_sprite_load_image("images/explosiveBarrel.png");
    Sprite* healingPotSprite = gf2d_sprite_load_image("images/healthBarrel.png");
    Sprite* treasureChestSprite = gf2d_sprite_load_image("images/treasureChest.png");
    Sprite* mimicHiddenSprite = gf2d_sprite_load_image("images/mimicHidden.png");
    Sprite* explosion = gf2d_sprite_load_image("images/explosion.png");
    Sprite* healthExplosion = gf2d_sprite_load_image("images/healingExplosion.png");



    Entity* grass = NewGrass(vector2d(-300, - 300));
    Entity* explode = NewExplosiveBarrel(vector2d(-300, -300));
    Entity* healthBarrel = NewExplosiveBarrel(vector2d(-300, -300));
    Entity* treasureChest = NewTreasureChest(vector2d(-300, -300));
    Entity* mimicChest = NewMimicChest(vector2d(-300, -300));


    int explosionTimer = 120;
    int healingTimer = 120;

    //levelup stuff

    Sprite* upgradeMenu = gf2d_sprite_load_image("images/levelUp.png");
    SDL_Rect healthUp = { 365,135, 493, 67 };
    SDL_Rect damageUp = { 383,220, 459, 64 };
    SDL_Rect healthPotUp = { 379, 301, 471, 67 };
    SDL_Rect moveSpeedUp = {400, 395, 443, 50};
    SDL_Rect dodgeUp = { 394, 480, 456, 69 };

    //quest sprites
    Sprite* quest1 = gf2d_sprite_load_image("images/quest1.png");
    Sprite* quest2 = gf2d_sprite_load_image("images/quest2.png");
    Sprite* quest3 = gf2d_sprite_load_image("images/quest3.png");
    Sprite* quest4 = gf2d_sprite_load_image("images/quest4.png");
    Sprite* quest5 = gf2d_sprite_load_image("images/quest5.png");
    Sprite* questSuccess = gf2d_sprite_load_image("images/questSuccess.png");


    //vectormap_free("maps/testTown.json");
    testMap = vectormap_load("maps/testTown.json");

    //ServerInit();
    switch (currentBackground)
    {
    case 1:
        sprite = gf2d_sprite_load_image("images/backgrounds/town.png");
        break;
    case 2:
        sprite = gf2d_sprite_load_image("images/backgrounds/crayonBackground.png");
        break;
    case 3:
        sprite = gf2d_sprite_load_image("images/backgrounds/demo.png");

        break;
    case 4:
        sprite = gf2d_sprite_load_image("images/backgrounds/town2.png");

        break;

    }
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
        Mix_VolumeMusic(15);
        if (Mix_PlayingMusic() == 0)
        {
            //Play the music
            if (Mix_PlayMusic(music, -1) == -1)
            {
                return 1;
            }
        }
        
            gf2d_sprite_draw_image(sprite,vector2d(0,0));

           // slog("================= %i", test_player->playerCanTeleportToMapID);


           
            if (test_player->teleporting == 1)
            {
                for (int i = 255; i > 0; i -= 2)
                {
                    gf2d_graphics_clear_screen();
                    //vector2d(test_player->hitBox.x, test_player->hitBox.y-100)
                    //gf2d_sprite_draw_image(test_player->sprite, test_player->position);
                    entity_draw(test_player);

                    gf2d_sprite_draw_image(sprite, vector2d(0, 0));


                    SDL_SetTextureColorMod(
                        sprite->texture,
                        i,
                        i,
                        i);
                    SDL_SetTextureAlphaMod(
                        sprite->texture,
                        i);
                    SDL_SetTextureColorMod(
                        test_player->sprite->texture,
                        i,
                        i,
                        i);
                    SDL_SetTextureAlphaMod(
                        test_player->sprite->texture,
                        i);
                    gf2d_grahics_next_frame();

                }
                vectormap_free(testMap);
                entity_free(testSpawner);
                entity_free(manSpawner);
                entity_free(jumperSpawner);
                entity_free(rollerSpawner);
                entity_free(turretSpawner);
                entity_free(shop);
                entity_free(npc);
                entity_free(portalLeft);
                entity_free(portalRight);
                entity_free(grass);
                entity_free(explode);
                entity_free(healthBarrel);
                entity_free(treasureChest);
                entity_free(mimicChest);

                FreeCurrentMobs();
                
              



                


                if (test_player->teleporting == 1) 
                {
                    if (portalLeft)entity_free(portalLeft);
                    if (portalRight)entity_free(portalRight);

                    //slog("teleporting to map ID %i", test_player->playerCanTeleportToMapID);
                    switch (test_player->playerCanTeleportToMapID)
                    {
                    case 0:

                        if (testMap->mapID == 2)
                        {
                            test_player->position = vector2d(100, 650);
                        }
                        else
                        {
                            test_player->position = vector2d(1100, 650);

                        }

                        testMap = vectormap_load("maps/testTown.json");
                        //sprite = gf2d_sprite_load_image(testMap->testTest);
                        switch (currentBackground)
                        {
                        case 1:
                            sprite = gf2d_sprite_load_image("images/backgrounds/town.png");
                            break;
                        case 2:
                            sprite = gf2d_sprite_load_image("images/backgrounds/crayonBackground.png");
                            break;
                        case 3:
                            sprite = gf2d_sprite_load_image("images/backgrounds/demo.png");

                            break;
                        case 4:
                            sprite = gf2d_sprite_load_image("images/backgrounds/town2.png");
                            
                            break;
                        default:
                            sprite = gf2d_sprite_load_image("images/backgrounds/town.png");

                            break;
                        }
                        shop = shop_new(vector2d(275, 700));

                        npc = npc_new(vector2d(800, 700));

                        portalLeft = portal_new(vector2d(100, 675), 0, 2);
                        portalRight = portal_new(vector2d(1100, 675), 0, 1);

                        testSpawner = spawner_new(1, vector2d(-100, -100), 0, 999999);
                        manSpawner = spawner_new(1, vector2d(-100, -100), 0, 999999);
                        jumperSpawner = spawner_new(1, vector2d(-100, -100), 0, 999999);
                        rollerSpawner = spawner_new(1, vector2d(-100, -100), 0, 999999);
                        turretSpawner = spawner_new(1, vector2d(-100, -100), 0, 999999);

                        

                        test_player->teleporting = 0;

                        break;
                    case 1:
                        testMap = vectormap_load("maps/test.json");

                        sprite = gf2d_sprite_load_image(testMap->testTest);

                        shop = shop_new(vector2d(-100, -700));

                        npc = npc_new(vector2d(-400, -260));

                        portalLeft = portal_new(vector2d(100, 675), 1, 0);

                        testSpawner = spawner_new(testMap->spawnerInfo[3].x, testMap->spawnerCoords[3], testMap->spawnerInfo[3].y, testMap->spawnerInfo[3].z);
                        manSpawner = spawner_new(testMap->spawnerInfo[1].x, testMap->spawnerCoords[1], testMap->spawnerInfo[1].y, testMap->spawnerInfo[1].z);
                        jumperSpawner = spawner_new(testMap->spawnerInfo[2].x, testMap->spawnerCoords[2], testMap->spawnerInfo[2].y, testMap->spawnerInfo[2].z);
                        rollerSpawner = spawner_new(testMap->spawnerInfo[0].x, testMap->spawnerCoords[0], testMap->spawnerInfo[0].y, testMap->spawnerInfo[0].z);
                        turretSpawner = spawner_new(testMap->spawnerInfo[4].x, testMap->spawnerCoords[4], testMap->spawnerInfo[4].y, testMap->spawnerInfo[4].z);

                        test_player->position = vector2d(100, 650);

                        test_player->teleporting = 0;
                        break;
                    case 2:
                        testMap = vectormap_load("maps/demoMap.json");
                        sprite = gf2d_sprite_load_image("images/backgrounds/demo.png");


                        shop = shop_new(vector2d(-100, -700));

                        npc = npc_new(vector2d(-400, -260));
                        grass = NewGrass(vector2d(1000, 675));
                        portalRight = portal_new(vector2d(1100, 675), 2, 0);

                        testSpawner = spawner_new(1, vector2d(-100, -100), 0, 999999);
                        manSpawner = spawner_new(1, vector2d(-100, -100), 0, 999999);
                        jumperSpawner = spawner_new(1, vector2d(-100, -100), 0, 999999);
                        rollerSpawner = spawner_new(1, vector2d(-100, -100), 0, 999999);
                        turretSpawner = spawner_new(1, vector2d(-100, -100), 0, 999999);

                        test_player->position = vector2d(1100, 650);

                        test_player->teleporting = 0;

                        break;
                    case -1:
                        testMap = vectormap_load("maps/demoMap.json");
                        sprite = gf2d_sprite_load_image("images/backgrounds/demo.png");


                        shop = shop_new(vector2d(-100, -700));

                        npc = npc_new(vector2d(-400, -260));
                        grass = NewGrass(vector2d(850, 640));
                        explode = NewExplosiveBarrel(vector2d(650, 640));
                        healthBarrel = NewHealthBarrel(vector2d(450, 640));
                        treasureChest = NewTreasureChest(vector2d(250, 640));
                        mimicChest = NewMimicChest(vector2d(50, 640));


                        portalRight = portal_new(vector2d(1100, 700), 2, 0);

                        testSpawner = spawner_new(1, vector2d(-100, -100), 0, 999999);
                        manSpawner = spawner_new(1, vector2d(-100, -100), 0, 999999);
                        jumperSpawner = spawner_new(1, vector2d(-100, -100), 0, 999999);
                        rollerSpawner = spawner_new(1, vector2d(-100, -100), 0, 999999);
                        turretSpawner = spawner_new(1, vector2d(-100, -100), 0, 999999);

                        test_player->position = vector2d(1100, 650);

                        test_player->teleporting = 0;
                        break;

                    }
                }
                for (int i = 0; i < 255; i += 2)
                {
                    gf2d_graphics_clear_screen();

                    gf2d_sprite_draw_image(sprite, vector2d(0, 0));

                    entity_draw(test_player);

                    //gf2d_sprite_draw_image(sprite, vector2d(0, 0));

                    SDL_SetTextureColorMod(
                        sprite->texture,
                        i,
                        i,
                        i);
                    SDL_SetTextureAlphaMod(
                        sprite->texture,
                        i);


                    SDL_SetTextureColorMod(
                        test_player->sprite->texture,
                        i,
                        i,
                        i);
                    SDL_SetTextureAlphaMod(
                        test_player->sprite->texture,
                        i);
                    gf2d_grahics_next_frame();

                }
            }

            //TODO
            //npc/entity drawing should not be done individually

            entity_draw(shop);
            shop_think(shop);

            entity_draw(npc);
            npc_think(npc);


            //TODO
            //allow for passive skills to be combined with active skills

            //TODO
            //change controls from wasd to arrow keys
            entity_draw(portalRight);
            entity_draw(portalLeft);
            portal_think(portalRight, testMap);
            portal_think(portalLeft, testMap);
            entity_draw(test_player);

            if (grass) entity_draw(grass);
            if (grass) GrassThink(grass);

            if (explode) entity_draw(explode);
            if (explode) ExplosiveBarrelThink(explode);

            if (healthBarrel) entity_draw(healthBarrel);
            if (healthBarrel) HealthBarrelThink(healthBarrel);

            if (treasureChest) entity_draw(treasureChest);
            if (treasureChest) TreasureChestThink(treasureChest);

            if (mimicChest) entity_draw(mimicChest);
            if (mimicChest) MimicChestThink(mimicChest);


            SimplePlatformCollision(test_player, testMap);
            BoundingBoxCollision(test_player, testMap);
            DoPlayerGravity(test_player);
            DoSkills(test_player);
            SkillThink(test_player, test_player->activeSkill, test_player->skillOnePosition);
       
            if (test_player->hasFireCape == 1)
            {
                BurnNearby();
            }
            if (test_player->hasRegenBracelet == 1)
            {
                regenTimer++;

                if (regenTimer >= 540)
                {
                    gf2d_sprite_draw_image(healingSprite, vector2d(test_player->hitBox.x+16, test_player->hitBox.y-80));
                    if (regenTimer >= 600)
                    {
                        test_player->health += 250;
                        if (test_player->health > test_player->maxHealth) test_player->health = test_player->maxHealth;
                        regenTimer = 0;
                    }
                }
            }
            if (test_player->isReflecting)
            {
                Vector2D tempVector;
                reflectTimer++;
                if (reflectTimer == 1)
                {
                    //tempVector = { test_player->position.x + gfc_crandom() * 200,test_player->position.y + gfc_crandom() * 200 };
                    tempVector.x = test_player->position.x + gfc_random() * 400;
                    tempVector.y = test_player->position.y + gfc_crandom() * 400;
                }
                if (reflectTimer > 60)
                {
                    reflectTimer = 0;
                    test_player->isReflecting = 0;
                }
                gf2d_draw_line(test_player->position, tempVector, vector4d(250, 15, 15, 255));
            }
            //TODO 
            //Spawner/Npc/mob thinking should not be called individually

            
            if (test_player->showExplosion == 1 && explosionTimer > 0)
            {
                gf2d_sprite_draw_image(explosion, vector2d(600, 600));
                explosionTimer--;
            }
            if (test_player->showHealing == 1 && healingTimer > 0)
            {
                gf2d_sprite_draw_image(healthExplosion, vector2d(450, 600));
                healingTimer--;

            }

          
                testSpawner->spawnCount = test_player->spawnBugCount;
                SpawnerThink(testSpawner, bugSpawnList, testMap);

                manSpawner->spawnCount = test_player->spawnManCount;
                SpawnerThink(manSpawner, manSpawnList, testMap);

                jumperSpawner->spawnCount = test_player->spawnJumperCount;
                SpawnerThink(jumperSpawner, jumperSpawnList, testMap);

                rollerSpawner->spawnCount = test_player->spawnRollerCount;
                SpawnerThink(rollerSpawner, rollerSpawnList, testMap);

                turretSpawner->spawnCount = test_player->spawnTurretCount;
                SpawnerThink(turretSpawner, turretSpawnList, testMap);
            
            vectormap_draw(testMap);

            //TODO
            //add actual window system because this is garbage
            healthPercent = (int)(((float)test_player->health / (float)test_player->maxHealth) * 512);
            experiencePercent = (int)(((float)test_player->experience / (float)50) * 512);

            for (int i = 0; i < healthPercent; i++)
            {
                Vector2D p1 = { (i + 344), 10 };
                Vector2D p2 = { (i + 344), 30 };

                gf2d_draw_line(p1, p2, vector4d(255, 20, 20, 255));
            }
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
            //entity_draw(itemTest);

            //quest here
            if (test_player->hasBFS && test_player->activeQuest == 4)
            {
                test_player->activeQuest = 5;
            }
            if (test_player->questOpen == 1)
            {
                switch (test_player->activeQuest)
                {
                case 1:
                    gf2d_sprite_draw_image(quest1, vector2d(350, 235));
                    break;
                case 2:
                    gf2d_sprite_draw_image(quest2, vector2d(350, 235));
                    break;
                case 3:
                    gf2d_sprite_draw_image(quest3, vector2d(350, 235));

                    break;
                case 4:
                    gf2d_sprite_draw_image(quest4, vector2d(350, 235));

                    break;
                case 5:
                    gf2d_sprite_draw_image(quest5, vector2d(350, 235));

                    break;
                case 6:
                    gf2d_sprite_draw_image(questSuccess, vector2d(350, 235));

                    break;
                default:
                    // gf2d_sprite_draw_image(questSuccess, vector2d(690, 10));

                    break;
                }
            }
            //TODO
            //again, garbage need menu system

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



            if (test_player->isMapOpen == 1)
            {
                gf2d_sprite_draw_image(map, vector2d(100, 110));

               if(test_player->hasMirrorShield) gf2d_sprite_draw_image(mirrorSprite, vector2d(1017, 125));
               if (test_player->hasBFS) gf2d_sprite_draw_image(BFSSprite, vector2d(1017, 189));
               if (test_player->hasSneakers) gf2d_sprite_draw_image(sneakersSprite, vector2d(1017, 253));
               if (test_player->hasRegenBracelet) gf2d_sprite_draw_image(regenBraceletSprite, vector2d(1017, 317));
               if (test_player->hasFireCape) gf2d_sprite_draw_image(fireCapeSprite, vector2d(1017, 381));

               gf2d_sprite_draw(
                   mouse,
                   vector2d(mx, my),
                   NULL,
                   NULL,
                   NULL,
                   NULL,
                   &mouseColor,
                   (int)mf);
            }

           
            while (test_player->canUpgrade == 1 && test_player->level <= 5)
            {

                SDL_PumpEvents();   // update SDL's internal event structures
                keys = SDL_GetKeyboardState(NULL); // get the keyboard state for this frame
                /*update things here*/

               // gfc_input_update();
                SDL_GetMouseState(&mx, &my);
                mf += 0.1;
                if (mf >= 16.0)mf = 0;
                gf2d_graphics_clear_screen();
                //vector2d(test_player->hitBox.x, test_player->hitBox.y-100)
                //gf2d_sprite_draw_image(test_player->sprite, test_player->position);

                gf2d_sprite_draw_image(sprite, vector2d(0, 0));

                entity_draw(test_player);

                gf2d_sprite_draw_image(upgradeMenu, vector2d(100, 110));

               // gf2d_draw_rect(healthUp, vector4d(240, 10, 240, 255));
               // gf2d_draw_rect(damageUp, vector4d(240, 10, 240, 255));
               // gf2d_draw_rect(healthPotUp, vector4d(240, 10, 240, 255));
                //gf2d_draw_rect(moveSpeedUp, vector4d(240, 10, 240, 255));
               // gf2d_draw_rect(dodgeUp, vector4d(240, 10, 240, 255));


                gf2d_sprite_draw(
                    mouse,
                    vector2d(mx, my),
                    NULL,
                    NULL,
                    NULL,
                    NULL,
                    &mouseColor,
                    (int)mf);
                SDL_Rect mouseRect = { mx, my, 2, 2 };
                gf2d_draw_rect(mouseRect, vector4d(240, 10, 240, 255));

                gf2d_grahics_next_frame();

                if (SDL_GetMouseState(&mx, &my) == 1 && SDL_HasIntersection(&mouseRect, &healthUp))
                {
                    test_player->canUpgrade = 0;
                    test_player->maxHealth += 100;
                }
                else if (SDL_GetMouseState(&mx, &my) == 1 && SDL_HasIntersection(&mouseRect, &damageUp))
                {
                    test_player->canUpgrade = 0;
                    test_player->damageBonus += 10;

                }
                else if (SDL_GetMouseState(&mx, &my) == 1 && SDL_HasIntersection(&mouseRect, &healthPotUp))
                {
                    test_player->canUpgrade = 0;
                    test_player->healthSlot += 1;

                }
                else if (SDL_GetMouseState(&mx, &my) == 1 && SDL_HasIntersection(&mouseRect, &moveSpeedUp))
                {
                    test_player->canUpgrade = 0;
                    test_player->moveSpeedBonus += 1;

                }
                else if (SDL_GetMouseState(&mx, &my) == 1 && SDL_HasIntersection(&mouseRect, &dodgeUp))
                {
                    test_player->canUpgrade = 0;
                    test_player->dodgeBonus += 1;

                }

                test_player->health = test_player->maxHealth;
             
            }
         
            // ===================== MENU TESTING ============================

            if (test_player->canWin == 1 && test_player->position.x < 100 && test_player->position.y < 600)
            {
                cueGameWin = 1;
                if (Mix_PlayChannel(-1, test_player->winNoise, 0) == -1)
                {
                    //return 1;
                }
            }

            if (cueGameWin == 1)
            {
                gf2d_sprite_draw_image(wonGame, vector2d(100, 110));
            }
            while (test_player->pause == 1)
            {
                SDL_PumpEvents();   // update SDL's internal event structures
                keys = SDL_GetKeyboardState(NULL); // get the keyboard state for this frame
                /*update things here*/

               // gfc_input_update();
                SDL_GetMouseState(&mx, &my);
                mf += 0.1;
                if (mf >= 16.0)mf = 0;
                SDL_Rect mouseRect = { mx, my, 2, 2 };

                gf2d_graphics_clear_screen();
                //vector2d(test_player->hitBox.x, test_player->hitBox.y-100)
                //gf2d_sprite_draw_image(test_player->sprite, test_player->position);

                gf2d_sprite_draw_image(sprite, vector2d(0, 0));

                entity_draw(test_player);

                gf2d_sprite_draw_image(pauseMenu, vector2d(100, 110));
                gf2d_draw_rect(mouseRect, vector4d(240, 10, 240, 255));

                //gf2d_draw_rect(continuebutton, vector4d(240, 10, 240, 255));
                //gf2d_draw_rect(quitButton, vector4d(240, 10, 240, 255));
            


                gf2d_sprite_draw(
                    mouse,
                    vector2d(mx, my),
                    NULL,
                    NULL,
                    NULL,
                    NULL,
                    &mouseColor,
                    (int)mf);
                gf2d_draw_rect(mouseRect, vector4d(240, 10, 240, 255));
                if (SDL_GetMouseState(&mx, &my) == 1 && SDL_HasIntersection(&mouseRect, &continuebutton))
                {
                    test_player->pause = 0;
                }
                else if (SDL_GetMouseState(&mx, &my) == 1 && SDL_HasIntersection(&mouseRect, &quitButton))
                {
                    test_player->pause = 0;
                    done = 1;

                }
                gf2d_grahics_next_frame();
            }

            // ===================== MENU TESTING ============================

        gf2d_grahics_next_frame();// render current draw frame and skip to the next frame
         
        entity_update_all();
        entity_draw_all();
    

        //TODO
        //add in command.c that will handle command inputs to hide this uglyness
        if (keys[SDL_SCANCODE_LEFTBRACKET]) test_player->level -= 1;
        if (keys[SDL_SCANCODE_RIGHTBRACKET]) test_player->level += 1;

        if (keys[SDL_SCANCODE_0])
        {
            //slog("000000000000000000000000000");

            vectormap_free(testMap);
            entity_free(testSpawner);
            entity_free(manSpawner);
            entity_free(jumperSpawner);
            entity_free(rollerSpawner);
            entity_free(turretSpawner);
            entity_free(shop);
            entity_free(npc);

            FreeCurrentMobs();

            


        }
        if (keys[SDL_SCANCODE_9])
        {
            //slog("99999999999999999999999999999999999");
            vectormap_free(testMap);
            entity_free(testSpawner);
            entity_free(manSpawner);
            entity_free(jumperSpawner);
            entity_free(rollerSpawner);
            entity_free(turretSpawner);

            entity_free(bugSpawnList);
            entity_free(manSpawnList);
            entity_free(rollerSpawnList);
            entity_free(jumperSpawnList);
            entity_free(turretSpawnList);

            FreeCurrentMobs();

            

        }
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

        if (keys[SDL_SCANCODE_LSHIFT])done = 1; // exit condition
        

       //slog("Rendering at %f FPS", gf2d_graphics_get_frames_per_second());
    }
   
    slog("---==== END ====---");
    return 0;
}
/*eol@eof*/
