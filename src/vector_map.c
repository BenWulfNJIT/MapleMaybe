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
    SJson *json, *platforms, *columns, *element1, * element2, * element3, * element4, *bbRow, *bbColumn, *spawnRow, *spawnColumn, *spawn1, *spawn2;
    VectorMap* map;
    Vector2D tempSpawnVec;
    int i, r, c, e1, e2, e3, e4, bbx, bby, sx, sy;

    if (!filename)return NULL;
    json = sj_load(filename);
    if (!json)return NULL;

    map = vectormap_new();

    map->testTest = sj_get_string_value(sj_object_get_value(json, "background"));
    platforms = sj_object_get_value(json, "platforms");
    map->platformCount = sj_array_get_count(platforms);
    
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
        //slog("Big test coords: [ %f, %f, %f, %f ]", map->platformCoords[p].x, map->platformCoords[p].y, map->platformCoords[p].z, map->platformCoords[p].w);
       
    }

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

    SDL_Rect tempRect = { 0, 0, bbx, bby };
    map->boundingBox = tempRect;



    //    map->spawnerCoords = (Vector2D*)gfc_allocate_array(sizeof(Vector2D), 7);

    //some ugly stuff to get the spawnpoints into the vector map whatever its 2am
    spawnRow = sj_object_get_value(json, "spawnPoints");
    map->spawnerCoords = (Vector2D*)gfc_allocate_array(sizeof(Vector2D), sj_array_get_count(spawnRow));
    for (i = 0; i < sj_array_get_count(spawnRow); i++)
    {


    
        spawnColumn = sj_array_get_nth(spawnRow, i);
        
        spawn1 = sj_array_get_nth(spawnColumn, 0);
        sj_get_integer_value(spawn1, &sx);

        spawn2 = sj_array_get_nth(spawnColumn, 1);
        sj_get_integer_value(spawn2, &sy);

        //slog("TEST %i, %i", sx, sy);

        tempSpawnVec.x = sx;
        tempSpawnVec.y = sy;

        map->spawnerCoords[i] = tempSpawnVec;




    }

    slog("TEST %f, %f", map->spawnerCoords[0].x, map->spawnerCoords[0].y);
    slog("TEST %f, %f", map->spawnerCoords[1].x, map->spawnerCoords[1].y);



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
    Vector4D pinkColor = { 255, 105, 190, 255 };
    Vector4D greenColor = { 105, 255, 190, 255 };

    for (int i = 0; i < mapToDraw->platformCount; i++)
    {
        Vector2D p1 = { mapToDraw->platformCoords[i].x,mapToDraw->platformCoords[i].y };
        Vector2D p2 = { mapToDraw->platformCoords[i].z,mapToDraw->platformCoords[i].w };

        gf2d_draw_line(p1, p2, pinkColor);
    }

    gf2d_draw_rect(mapToDraw->boundingBox, greenColor);

}
