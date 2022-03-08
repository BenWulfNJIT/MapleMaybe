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
    int i, r, c, e1, e2, e3, e4, bbx, bby;

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
        slog("Big test coords: [ %f, %f, %f, %f ]", map->platformCoords[p].x, map->platformCoords[p].y, map->platformCoords[p].z, map->platformCoords[p].w);
       
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
