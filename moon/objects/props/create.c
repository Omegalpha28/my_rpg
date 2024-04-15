/*
** EPITECH PROJECT, 2024
** B-MUL-200-LYN-2-1-myrpg-mallory.scotton
** File description:
** create
*/

///////////////////////////////////////////////////////////////////////////////
// Headers
///////////////////////////////////////////////////////////////////////////////
#include "moon.h"

///////////////////////////////////////////////////////////////////////////////
static void init_prop(prop_t *prop, sheet_t *sheet)
{
    prop->animated = sheet->animCount > 0 ? sheet->anims[0]->looped : false;
    prop->draw = true;
    prop->frame = 0;
    prop->done = false;
    prop->once = sheet->animCount > 0 && !sheet->anims[0]->looped ? 1 : 0;
    prop->self = sheet;
    prop->sprite = sfSprite_create();
    prop->time = Time.currentTime;
}

///////////////////////////////////////////////////////////////////////////////
static void init_prop_transform(prop_t *prop, v2f_t position, v2f_t scale,
    float rotation)
{
    prop->position = position;
    prop->rotation = rotation;
    prop->scale = scale;
    prop_set_transform(prop);
}

///////////////////////////////////////////////////////////////////////////////
prop_t *prop_create(sheet_t *sheet, v2f_t position, v2f_t scale,
    float rotation)
{
    prop_t *prop = (prop_t *)malloc(sizeof(prop_t));

    if (prop == NULL)
        return (NULL);
    init_prop(prop, sheet);
    init_prop_transform(prop, position, scale, rotation);
    Pool.propCount++;
    Pool.props = REALLOC(Pool.props, sizeof(prop_t *), Pool.propCount);
    Pool.props[Pool.propCount - 1] = prop;
    return (prop);
}

///////////////////////////////////////////////////////////////////////////////
void prop_destroy(prop_t *prop)
{
    prop_t **tmp = NULL;
    uint_t j = 0;

    if (prop == NULL)
        return;
    if (prop->sprite != NULL)
        sfSprite_destroy(prop->sprite);
    tmp = malloc(sizeof(prop_t *) * (Pool.propCount - 1));
    for (uint_t i = 0; i < Pool.propCount; i++) {
        if (Pool.props[i] == prop)
            continue;
        tmp[j] = Pool.props[i];
        j++;
    }
    Pool.propCount--;
    FREE(Pool.props);
    Pool.props = tmp;
    FREE(prop);
}
