/*
** EPITECH PROJECT, 2024
** csfml-engine
** File description:
** zones
*/

///////////////////////////////////////////////////////////////////////////////
// Headers
///////////////////////////////////////////////////////////////////////////////
#include "moon.h"

///////////////////////////////////////////////////////////////////////////////
static bool_t init_zone(cstring_t path)
{
    warray_t content = my_dircontent(path);
    zone_t *zone;
    bool_t success = true;

    if (content == NULL)
        return (false);
    sort_warray(content);
    zone = (zone_t *)malloc(sizeof(zone_t));
    zone->categoryCount = 0;
    zone->loaded = false;
    zone->categories = NULL;
    zone->name = my_strdup(my_basename(path));
    Assets.zoneCount++;
    Assets.zones = REALLOC(Assets.zones, sizeof(zone_t *), Assets.zoneCount);
    Assets.zones[Assets.zoneCount - 1] = zone;
    for (uint_t i = 0; success && content[i]; i++) {
        if (my_isdir(content[i]) == false)
            continue;
        success = init_assets_category(zone, content[i]);
    }
    return (success);
}

///////////////////////////////////////////////////////////////////////////////
bool_t init_assets_zones(void)
{
    warray_t content = my_dircontent(DIR_ZONES);
    bool_t success = true;

    if (content == NULL)
        return (my_error(ERR_FD_ZONES));
    for (uint_t i = 0; success && content[i]; i++) {
        if (my_isdir(content[i]) == false)
            continue;
        success = init_zone(content[i]);
    }
    my_watroy(content);
    return (true);
}

///////////////////////////////////////////////////////////////////////////////
void destroy_assets_zones(void)
{
    if (Assets.zoneCount == 0 || Assets.zones == NULL)
        return;
    for (uint_t i = 0; i < Assets.zoneCount; i++) {
        for (uint_t j = 0; j < Assets.zones[i]->categoryCount; j++)
            destroy_assets_category(Assets.zones[i]->categories[j]);
        FREE(Assets.zones[i]->categories);
        FREE(Assets.zones[i]->name);
        FREE(Assets.zones[i]);
    }
    FREE(Assets.zones);
    Assets.zoneCount = 0;
    Assets.zones = NULL;
    return;
}

///////////////////////////////////////////////////////////////////////////////
static void unload_all_zones(void)
{
    for (uint_t i = 0; i < Assets.zoneCount; i++)
        if (Assets.zones[i]->loaded)
            unload_zone(Assets.zones[i]->name);
}

///////////////////////////////////////////////////////////////////////////////
bool_t load_zone(cstring_t name)
{
    zone_t *zone;

    for (uint_t i = 0; i < Assets.zoneCount; i++) {
        if (!CMP(Assets.zones[i]->name, name))
            continue;
        unload_all_zones();
        zone = Assets.zones[i];
        zone->loaded = true;
        for (uint_t j = 0; j < zone->categoryCount; j++)
            load_category(zone->categories[j]);
        return (true);
    }
    return (false);
}

///////////////////////////////////////////////////////////////////////////////
bool_t unload_zone(cstring_t name)
{
    zone_t *zone;

    for (uint_t i = 0; i < Assets.zoneCount; i++) {
        if (!CMP(Assets.zones[i]->name, name))
            continue;
        zone = Assets.zones[i];
        zone->loaded = false;
        for (uint_t j = 0; j < zone->categoryCount; j++)
            unload_category(zone->categories[i]);
        return (true);
    }
    return (false);
}
