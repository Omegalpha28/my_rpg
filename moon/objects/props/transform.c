/*
** EPITECH PROJECT, 2024
** B-MUL-200-LYN-2-1-myrpg-mallory.scotton
** File description:
** transform
*/

///////////////////////////////////////////////////////////////////////////////
// Headers
///////////////////////////////////////////////////////////////////////////////
#include "moon.h"

///////////////////////////////////////////////////////////////////////////////
void prop_set_transform(prop_t *prop)
{
    sfSprite_setScale(prop->sprite, prop->scale);
    sfSprite_setPosition(prop->sprite, prop->position);
    sfSprite_setRotation(prop->sprite, prop->rotation);
}

///////////////////////////////////////////////////////////////////////////////
void prop_move(prop_t *prop, v2f_t offset)
{
    if (prop == NULL)
        return;
    prop->position.x += offset.x;
    prop->position.y += offset.y;
    prop_set_transform(prop);
}

///////////////////////////////////////////////////////////////////////////////
void prop_rotate(prop_t *prop, float angle)
{
    if (prop == NULL)
        return;
    prop->rotation += angle;
    prop_set_transform(prop);
}

///////////////////////////////////////////////////////////////////////////////
void prop_scale(prop_t *prop, v2f_t factors)
{
    if (prop == NULL)
        return;
    prop->scale.x += factors.x;
    prop->scale.y += factors.y;
    prop_set_transform(prop);
}
