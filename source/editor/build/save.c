/*
** EPITECH PROJECT, 2024
** B-MUL-200-LYN-2-1-myrpg-mallory.scotton
** File description:
** save
*/

///////////////////////////////////////////////////////////////////////////////
// Headers
///////////////////////////////////////////////////////////////////////////////
#include "rpg.h"

///////////////////////////////////////////////////////////////////////////////
static void find_ids(prop_t *prop, uint_t *catId, uint_t *shtId)
{
    sheet_t *needle = prop->self;
    zone_t *haystack = Editor.zone;
    uint_t s = 0;

    for (uint_t c = 0; c < haystack->categoryCount; c++) {
        for (s = 0; s < haystack->categories[c]->sheetCount &&
            haystack->categories[c]->sheets[s] != needle; s++);
        if (haystack->categories[c]->sheets[s] == needle) {
            (*catId) = c;
            (*shtId) = s;
            return;
        }
    }
}

///////////////////////////////////////////////////////////////////////////////
//
// CATEGORY_ID SHEET_ID POS_X POS_Y INVERT COLLIDE DATA
//     (2)       (2)     (3)   (3)    (1)    (1)    (4)   = 16 byte/tile
//
///////////////////////////////////////////////////////////////////////////////
static void save_prop(prop_t *prop, buffer_t *buff)
{
    uint_t catId = 0;
    uint_t shtId = 0;

    find_ids(prop, &catId, &shtId);
    my_buffint(buff, catId, 2);
    my_buffint(buff, shtId, 2);
    my_buffchar(buff, prop->position.x < 0.0 ? 1 : 0);
    my_buffint(buff, abs(((int)prop->position.x)), 2);
    my_buffchar(buff, prop->position.y < 0.0 ? 1 : 0);
    my_buffint(buff, abs(((int)prop->position.y)), 2);
    my_buffchar(buff, prop->scale.x > 0 ? 0 : 1);
    my_buffchar(buff, prop->collision ? 1 : 0);
    for (uint_t i = 0; i < 4; i++)
        my_buffchar(buff, prop->data[i]);
}

///////////////////////////////////////////////////////////////////////////////
bool_t level_save(cstring_t filepath)
{
    buffer_t *buff = my_buffinit();

    my_buffstr(buff, Editor.zone->name);
    my_buffchar(buff, 0);
    my_buffint(buff, (int)(Editor.fCount), 3);
    for (uint_t i = 0; i < Editor.fCount; i++)
        save_prop(Editor.fProps[i], buff);
    my_buffint(buff, (int)Editor.bCount, 3);
    for (uint_t i = 0; i < Editor.bCount; i++)
        save_prop(Editor.bProps[i], buff);
    my_fbuff(buff, filepath);
    my_bufftroy(buff);
    return (true);
}