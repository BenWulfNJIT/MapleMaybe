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
    SJson* json;
    VectorMap* map;

    if (!filename)return NULL;
    json = sj_load(filename);
    if (!json)return NULL;
    map = vectormap_new();

    backgroundFile = sj_get_string_value(sj_object_get_value(json, "background"));
    map->testTest = sj_get_string_value(sj_object_get_value(json, "background"));
    slog("Background Image: %s", map->testTest);
    //char * backgroundFile = sj_object_get_value(json, "background");
    //slog("Background file: ");
    //slog(&backgroundFile);


}

void vectormap_free()
{

}

void vectormap_draw()
{

}
