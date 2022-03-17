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

int main(int argc, char * argv[])
{
    /*variable declarations*/
    int done = 0;
    const Uint8 * keys;
    Sprite *sprite;
    
    int mx,my;
    float mf = 0;
    Sprite *mouse;
    Vector4D mouseColor = {255,100,255,200};
    VectorMap *testMap;
    Entity* bug, *test_player;


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
    mouse = gf2d_sprite_load_all("images/pointer.png",32,32,16);
    /*main game loop*/

    bug = bug_new(vector2d(100, 100), vector2d(gfc_crandom(), gfc_crandom()));

    Vector2D p1 = { 20, 670 };
    Vector2D p2 = { 1180, 670 };
    Vector4D pinkColor = { 255, 105, 190, 255 };

    testMap = vectormap_load("maps/test.json");
  
    test_player = player_new(vector2d(100, 100));

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
            
            entity_draw(bug);
            SimplePlatformCollision(bug, testMap);
            BoundingBoxCollision(bug, testMap);

            entity_draw(test_player);
            SimplePlatformCollision(test_player, testMap);
            BoundingBoxCollision(test_player, testMap);

            
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

           
            

           //gf2d_draw_line(p1, p2, pinkColor);
           // gf2d_draw_line();

            vectormap_draw(testMap);

        gf2d_grahics_next_frame();// render current draw frame and skip to the next frame
        
        entity_update_all();
        entity_draw_all();
        //entity_update(bug);
    

        if (keys[SDL_SCANCODE_ESCAPE])done = 1; // exit condition
        //slog("Rendering at %f FPS",gf2d_graphics_get_frames_per_second());
    }
    slog("---==== END ====---");
    return 0;
}
/*eol@eof*/
