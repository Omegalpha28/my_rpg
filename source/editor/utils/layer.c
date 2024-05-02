/*
** EPITECH PROJECT, 2024
** B-MUL-200-LYN-2-1-myrpg-mallory.scotton
** File description:
** layer
*/

///////////////////////////////////////////////////////////////////////////////
// Headers
///////////////////////////////////////////////////////////////////////////////
#include "rpg.h"

///////////////////////////////////////////////////////////////////////////////
static void move_prop_layer(prop_t ***from, prop_t ***to, prop_t *prop)
{
    uint_t *nFrom = (*from == Editor.fProps) ? &Editor.fCount : &Editor.bCount;
    uint_t *nTo = (*to == Editor.fProps) ? &Editor.fCount : &Editor.bCount;
    prop_t **tmp = malloc(sizeof(prop_t *) * ((*nFrom) - 1));
    uint_t j = 0;

    for (uint_t i = 0; i < (*nFrom); i++) {
        if ((*from)[i] == prop)
            continue;
        tmp[j] = (*from)[i];
        j++;
    }
    (*nFrom)--;
    FREE((*from));
    (*from) = tmp;
    (*nTo)++;
    (*to) = REALLOC((*to), sizeof(prop_t *), (*nTo));
    (*to)[(*nTo) - 1] = prop;
}

///////////////////////////////////////////////////////////////////////////////
void editor_to_foreground(void)
{
    prop_t **arr = NULL;
    uint_t idx = 0;

    if (!Editor.focus)
        return;
    arr = find_prop_stack(Editor.focus, &idx);
    if (arr == NULL || arr == Editor.fProps)
        return;
    move_prop_layer(&(Editor.bProps), &(Editor.fProps), Editor.focus);
    Editor.layer = EDITOR_LAYER_FOREGROUND;
}

///////////////////////////////////////////////////////////////////////////////
void editor_to_background(void)
{
    prop_t **arr = NULL;
    uint_t idx = 0;

    if (!Editor.focus)
        return;
    arr = find_prop_stack(Editor.focus, &idx);
    if (arr == NULL || arr == Editor.bProps)
        return;
    move_prop_layer(&(Editor.fProps), &(Editor.bProps), Editor.focus);
    Editor.layer = EDITOR_LAYER_BACKGROUND;
}
