/*
** EPITECH PROJECT, 2024
** B-MUL-200-LYN-2-1-myrpg-mallory.scotton
** File description:
** props
*/

///////////////////////////////////////////////////////////////////////////////
// Headers
///////////////////////////////////////////////////////////////////////////////
#include "rpg.h"

///////////////////////////////////////////////////////////////////////////////
void add_prop(sheet_t *sheet, prop_t ***array, uint_t *count)
{
    prop_t *prop = prop_create(sheet, (v2f_t){0.0f, 0.0f},
        (v2f_t){1.0f, 1.0f}, 0);

    if (!prop)
        return;
    (*count)++;
    (*array) = REALLOC((*array), sizeof(prop_t *), (*count));
    (*array)[(*count) - 1] = prop;
}

///////////////////////////////////////////////////////////////////////////////
void remove_prop(prop_t *prop, prop_t ***array, uint_t *count)
{
    prop_t **tmp = NULL;
    uint_t j = 0;
    bool_t found = false;

    for (uint_t i = 0; prop && i < (*count); i++)
        found = (*array)[i] == prop ? true : found;
    if (!found)
        return;
    tmp = malloc(sizeof(prop_t *) * ((*count) - 1));
    for (uint_t i = 0; i < (*count); i++) {
        if ((*array)[i] == prop)
            continue;
        tmp[j] = (*array)[i];
        j++;
    }
    (*count)--;
    FREE((*array));
    (*array) = tmp;
    prop_destroy(prop);
}

///////////////////////////////////////////////////////////////////////////////
prop_t **find_prop_stack(prop_t *prop, uint_t *idx)
{
    for (uint_t i = 0; i < Editor.fCount; i++) {
        if (Editor.fProps[i] != prop)
            continue;
        (*idx) = i;
        return (Editor.fProps);
    }
    for (uint_t i = 0; i < Editor.bCount; i++) {
        if (Editor.bProps[i] != prop)
            continue;
        (*idx) = i;
        return (Editor.bProps);
    }
    return (NULL);
}
