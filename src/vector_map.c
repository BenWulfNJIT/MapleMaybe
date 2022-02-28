#include "simple_logger.h"

#include "simple_json.h"

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
    SJson *json, *rows, *columns;
    VectorMap* map;

    int platformCount, columnCount, rowCount;



    if (!filename)return NULL;
    json = sj_load(filename);
    if (!json)return NULL;

    map = vectormap_new();



    map->testTest = sj_get_string_value(sj_object_get_value(json, "background"));
    
    rows = sj_object_get_value(json, "plat1");
    columns = sj_array_get_nth(rows, 0);

    columnCount = sj_array_get_count(columns);
    rowCount = sj_array_get_count(rows);

    platformCount = rowCount / 2;


    slog("Rows: %i", rowCount);
    slog("Columns: %i", columnCount);
    slog("Number of Platforms: %i", platformCount);

    
    //remember to free the json
    //also need to add json platform data into an array, and also clear up this code a bit
    // will probably be easiest to draw 1px wide rects instead of vectors? we'll see
    //will need to possibly change format for map files
    


}

void vectormap_free()
{

}

void vectormap_draw()
{

}
