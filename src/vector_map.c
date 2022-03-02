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
        slog("failed to allocate memory for a new tilemap");
        return NULL;
    }
    memset(map, 0, sizeof(VectorMap));
    return map;
}

VectorMap *vectormap_load(char *filename)
{
    const char* backgroundFile = NULL;
    SJson *json, *platforms, *columns, *element;
    VectorMap* map;
    int platformArraySize;
    int tempArray[12];
    int tempFirstNum;
    int i, r, c, e;

    if (!filename)return NULL;
    json = sj_load(filename);
    if (!json)return NULL;

    map = vectormap_new();

    map->testTest = sj_get_string_value(sj_object_get_value(json, "background"));
    // rows = platforms
    // columns = columns
    platforms = sj_object_get_value(json, "platforms");
    map->platformCount = sj_array_get_count(platforms);
    platformArraySize = sj_array_get_count(platforms) * 4;
    
    columns = sj_array_get_nth(platforms, 0);
    
   // slog("Rows: %i Columns: %i", sj_array_get_count(platforms),sj_array_get_count(columns) );

    //slog("plats: %i, arraycount: %i",  map->platformCount, platformArraySize);


    map->platformCoords = (Uint32*)gfc_allocate_array(sizeof(Uint32), platformArraySize);
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
        if (!columns)continue;
        for (c = 0; c < sj_array_get_count(columns); c++)
        {
            element = sj_array_get_nth(columns, c);
            if (!element)continue;
            sj_get_integer_value(element, &e);
            map->platformCoords[i++] = e;
        }
    }

    //for (int p = 0; p < platformArraySize; p++)
    //{
    //    slog("Idk: %i", map->platformCoords[p]);
    //}
    //slog("Idk: %i", map->platformCoords[0])
    sj_free(json);
    return map;


    

    //total array space is gonna be platformCount * 4
    //remember to free the json
    // 4d vector for each platform?? hmmmmmmmmm??
    //also need to add json platform data into an array, and also clear up this code a bit
    // will probably be easiest to draw 1px wide rects instead of vectors? we'll see
    //will need to possibly change format for map files
    


}

void vectormap_free()
{

}

void vectormap_draw(VectorMap* mapToDraw)
{

    //This is ugly im sorry
    // Wanted to put mapToDraw->platformCoords as Vector4D but instead its a huge array of coordinates repeating
    int x1 = 0;
    int y1 = 1;
    int x2 = 2;
    int y2 = 3;
    Vector4D pinkColor = { 255, 105, 190, 255 };


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

}
