/*
** EPITECH PROJECT, 2024
** B-MUL-200-LYN-2-1-myrpg-mallory.scotton
** File description:
** load
*/

///////////////////////////////////////////////////////////////////////////////
// Headers
///////////////////////////////////////////////////////////////////////////////
#include "rpg.h"

///////////////////////////////////////////////////////////////////////////////
static string_t readf(cstring_t filepath, ulong_t *readed)
{
    FILE *f = fopen(filepath, "rb");
    char *string;
    long fsize;

    fseek(f, 0, SEEK_END);
    fsize = ftell(f);
    fseek(f, 0, SEEK_SET);
    string = malloc(fsize + 1);
    fread(string, fsize, 1, f);
    fclose(f);
    string[fsize] = 0;
    (*readed) = (ulong_t)fsize;
    return (string);
}

///////////////////////////////////////////////////////////////////////////////
static int my_rbuffint(cstring_t buff, uint_t bytes, ulong_t *idx)
{
    int value = 0;

    for (uint_t i = 0; i < bytes; i++) {
        value <<= 8;
        value |= buff[(*idx)];
        (*idx)++;
    }
    return (value);
}

///////////////////////////////////////////////////////////////////////////////
static void load_prop(cstring_t buff, prop_t ***array, uint_t *count,
    ulong_t *idx)
{
    int catId = 0;
    int shtId = 0;
    prop_t *prop;

    catId = my_rbuffint(buff, 2, idx);
    shtId = my_rbuffint(buff, 2, idx);
    add_prop(Editor.zone->categories[catId]->sheets[shtId], array, count);
    prop = (*array)[(*count) - 1];
    prop->position.x = (buff[(*idx)]) ? -1.0f : 1.0f;
    (*idx)++;
    prop->position.x *= my_rbuffint(buff, 2, idx);
    prop->position.y = (buff[(*idx)]) ? -1.0f : 1.0f;
    (*idx)++;
    prop->position.y *= my_rbuffint(buff, 2, idx);
    prop->scale.x = (buff[(*idx)]) ? -1.0f : 1.0f;
    (*idx)++;
    prop->collision = (buff[(*idx)]) ? true : false;
    (*idx)++;
    (*idx) += 4;
    prop_set_transform(prop);
}

///////////////////////////////////////////////////////////////////////////////
static void load_information(cstring_t buff, ulong_t *idx)
{
    ulong_t length = my_strlen(buff);

    if (length == 0)
        return;
    if (!load_zone(buff))
        return;
    for (uint_t i = 0; i < Assets.zoneCount; i++) {
        if (Assets.zones[i]->loaded == false)
            continue;
        Editor.zone = Assets.zones[i];
        Editor.zoneId = i;
    }
    (*idx) = (length + 1);
}

///////////////////////////////////////////////////////////////////////////////
static void load_layer(prop_t ***array, uint_t *count, cstring_t buff,
    ulong_t *idx)
{
    int howMany = my_rbuffint(buff, 3, idx);

    for (uint_t i = 0; i < (uint_t)howMany; i++)
        load_prop(buff, array, count, idx);
}

///////////////////////////////////////////////////////////////////////////////
bool_t level_load(cstring_t filepath)
{
    ulong_t readed = 0;
    cstring_t buff = (cstring_t)readf(filepath, &readed);
    ulong_t idx = 0;

    if (buff == NULL)
        return (false);
    load_information(buff, &idx);
    load_layer(&(Editor.fProps), &(Editor.fCount), buff, &idx);
    load_layer(&(Editor.bProps), &(Editor.bCount), buff, &idx);
    return (true);
}