#include "simple_logger.h"

#include "simple_json.h"

#include "gf2d_draw.h"


#include "vector_map.h"


VectorMap *vectormap_new()
{
    VectorMap* map;
    map = (VectorMap*)malloc(sizeof(VectorMap));
    if (!map)
    {
        slog("Failed to allocate memory for a new Vector Map");
        return NULL;
    }
    memset(map, 0, sizeof(VectorMap));
    return map;
}

VectorMap *vectormap_load(char *filename)
{

    const char* backgroundFile = NULL;
    SJson *json, *platforms, *columns, *element1, * element2, * element3, * element4, *bbRow, *bbColumn;
    VectorMap* map;
    //int platformArraySize;
    //int tempArray[12];
    //int tempFirstNum;
    int i, r, c, e1, e2, e3, e4, bbx, bby;
  //  int bbx, bby;


    if (!filename)return NULL;
    json = sj_load(filename);
    if (!json)return NULL;

    map = vectormap_new();

    map->testTest = sj_get_string_value(sj_object_get_value(json, "background"));
    platforms = sj_object_get_value(json, "platforms");
    map->platformCount = sj_array_get_count(platforms);
    //platformArraySize = sj_array_get_count(platforms) * 4;
    
    columns = sj_array_get_nth(platforms, 0);
   
    map->platformCoords = (Vector4D*)gfc_allocate_array(sizeof(Vector4D), map->platformCount);

    if (!map->platformCoords)
    {
        sj_free(json);
        return map;
    }

    //this is the loop that will store properly in 4dvec
    //map->platformCoords[0] = {x1, y1, x2, y2}
    for (int p=0; p < map->platformCount; p++)
    {
        columns = sj_array_get_nth(platforms, p);
       
        element1 = sj_array_get_nth(columns, 0);
        sj_get_integer_value(element1, &e1);

        element2 = sj_array_get_nth(columns, 1);
        sj_get_integer_value(element2, &e2);

        element3 = sj_array_get_nth(columns, 2);
        sj_get_integer_value(element3, &e3);

        element4 = sj_array_get_nth(columns, 3);
        sj_get_integer_value(element4, &e4);


        //making a temporary vector cause setting them individually wasnt working
        Vector4D tempVec = { e1, e2, e3, e4 };

        //setting the important stuff
        map->platformCoords[p] = tempVec;

        //test print
        slog("Big test coords: [ %f, %f, %f, %f ]", map->platformCoords[p].x, map->platformCoords[p].y, map->platformCoords[p].z, map->platformCoords[p].w);
       
    }
    

    map->topLeftBound = (Uint32*)gfc_allocate_array(sizeof(Uint32), 2);
    map->topRightBound = (Uint32*)gfc_allocate_array(sizeof(Uint32), 2);
    map->bottomLeftBound = (Uint32*)gfc_allocate_array(sizeof(Uint32), 2);
    map->bottomRightBound = (Uint32*)gfc_allocate_array(sizeof(Uint32), 2);

    if (!map->platformCoords)
    {
        sj_free(json);
        return map;
    }

    bbRow = sj_object_get_value(json, "bounding_box");

    bbColumn = sj_array_get_nth(bbRow, 0);
    sj_get_integer_value(bbColumn, &bbx);

    bbColumn = sj_array_get_nth(bbRow, 1);
    sj_get_integer_value(bbColumn, &bby);

    //slog("TEST %i %i", bbx, bby);

    map->topLeftBound[0] = 0;
    map->topLeftBound[1] = 0;
    
    map->topRightBound[0] = bbx ;
    map->topRightBound[1] =  0;

    map->bottomLeftBound[0] = 0;
    map->bottomLeftBound[1] = bby;

    map->bottomRightBound[0] = bbx;
    map->bottomRightBound[1] = bby;

    sj_free(json);
    return map;

}

void vectormap_free(VectorMap* map)
{
    if (!map)return;
    free(map->platformCoords);
    free(map);
}

void vectormap_draw(VectorMap* mapToDraw)
{

    // This is ugly
    // Wanted to put mapToDraw->platformCoords as Vector4D
    // instead its a huge array of coordinates repeating
    int x1 = 0;
    int y1 = 1;
    int x2 = 2;
    int y2 = 3;
    Vector4D pinkColor = { 255, 105, 190, 255 };
    Vector4D greenColor = { 105, 255, 190, 255 };

   // Vector2D tl, tr, bl, br;

    for (int i = 0; i < mapToDraw->platformCount; i++)
    {
       // Vector2D p1 = { mapToDraw->platformCoords[x1],mapToDraw->platformCoords[y1] };
        //Vector2D p2 = { mapToDraw->platformCoords[x2],mapToDraw->platformCoords[y2] };

      //  gf2d_draw_line(p1, p2, pinkColor);

        x1 += 4;
        x2 += 4;
        y1 += 4;
        y2 += 4;
    }


    //slog("TEST: %i", mapToDraw->topLeftBound[0]);

    Vector2D tl = { mapToDraw->topLeftBound[0], mapToDraw->topLeftBound[1] };
    Vector2D  tr = {mapToDraw->topRightBound[0], mapToDraw->topRightBound[1]};
    Vector2D  bl = {mapToDraw->bottomLeftBound[0], mapToDraw->bottomLeftBound[1]};
    Vector2D   br = {mapToDraw->bottomRightBound[0], mapToDraw->bottomRightBound[1]};

   // slog("TEST: %i %i", mapToDraw->topLeftBound[0], mapToDraw->topLeftBound[1]);

    gf2d_draw_line(tl, tr, greenColor);
    gf2d_draw_line(tl, bl, greenColor);
    gf2d_draw_line(tr, br, greenColor);
    gf2d_draw_line(bl, br, greenColor);

  
   // gf2d_draw_line(*mapToDraw->topLeftBound, *mapToDraw->topLeftBound, pinkColor);

}
