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

    //need to add bounding box

    const char* backgroundFile = NULL;
    SJson *json, *platforms, *columns, *element, *bbRow, *bbColumn;
    VectorMap* map;
    int platformArraySize;
    int tempArray[12];
    int tempFirstNum;
    int i, r, c, e;
    int bbx, bby;


    if (!filename)return NULL;
    json = sj_load(filename);
    if (!json)return NULL;

    map = vectormap_new();

    map->testTest = sj_get_string_value(sj_object_get_value(json, "background"));
    platforms = sj_object_get_value(json, "platforms");
    map->platformCount = sj_array_get_count(platforms);
    platformArraySize = sj_array_get_count(platforms) * 4;
    
    columns = sj_array_get_nth(platforms, 0);
  

    map->platformCoords = (Uint32*)gfc_allocate_array(sizeof(Uint32), platformArraySize);
    //map->platformTEST = (Vector2D*)gfc_allocate_array(sizeof(Vector2D), platformArraySize);

    if (!map->platformCoords)
    {
        sj_free(json);
        return map;
    }

    //loop inserts all plat coords into gross array
    //formatted like: (x1, y1, x2, y2, 
    for (i = 0, r = 0; r < map->platformCount; r++)
    {
        columns = sj_array_get_nth(platforms, r);
        //if (!columns)continue;
        for (c = 0; c < sj_array_get_count(columns); c++)
        {
            element = sj_array_get_nth(columns, c);
            if (!element)continue;
            sj_get_integer_value(element, &e);
            map->platformCoords[i++] = e;

        }

    }

    //working??!!
    //need to change ^^ loop so that it adds into platformMaybe[i]
    //also change da variable names u fool.
    Vector2D TempVec = { 7,10 };
    map->platformsMaybe[0] = &TempVec;
    Vector2D printVec = *map->platformsMaybe[0];
    slog("map coord x: %f  map coord y: %f", map->platformsMaybe[0]->x, map->platformsMaybe[0]->y);
    slog("printVec.x: %f  printVec.y: %f", printVec.x, printVec.y);

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

    slog("TEST %i %i", bbx, bby);


    
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
        Vector2D p1 = { mapToDraw->platformCoords[x1],mapToDraw->platformCoords[y1] };
        Vector2D p2 = { mapToDraw->platformCoords[x2],mapToDraw->platformCoords[y2] };

        gf2d_draw_line(p1, p2, pinkColor);

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
