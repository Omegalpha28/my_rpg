/*
** EPITECH PROJECT, 2024
** B-MUL-200-LYN-2-1-myrpg-mallory.scotton
** File description:
** move
*/

///////////////////////////////////////////////////////////////////////////////
// Headers
///////////////////////////////////////////////////////////////////////////////
#include "rpg.h"

///////////////////////////////////////////////////////////////////////////////
void editor_move_down(void)
{
    uint_t idx = 0;
    prop_t **arr;
    prop_t *tmp;

    if (!Editor.focus)
        return;
    arr = find_prop_stack(Editor.focus, &idx);
    if (arr == NULL || idx == 0)
        return;
    tmp = arr[idx - 1];
    arr[idx - 1] = arr[idx];
    arr[idx] = tmp;
}

///////////////////////////////////////////////////////////////////////////////
void editor_move_up(void)
{
    uint_t idx = 0;
    prop_t **arr;
    prop_t *tmp;
    uint_t max = 0;

    if (!Editor.focus)
        return;
    arr = find_prop_stack(Editor.focus, &idx);
    max = (arr == Editor.fProps) ? Editor.fCount : Editor.bCount;
    if (arr == NULL || (idx + 1) == max)
        return;
    tmp = arr[idx + 1];
    arr[idx + 1] = arr[idx];
    arr[idx] = tmp;
}

///////////////////////////////////////////////////////////////////////////////
void editor_all_up(void)
{
    uint_t idx = 0;
    prop_t **arr;
    uint_t max = 0;

    if (!Editor.focus)
        return;
    arr = find_prop_stack(Editor.focus, &idx);
    max = (arr == Editor.fProps) ? Editor.fCount : Editor.bCount;
    if (arr == NULL || (idx + 1) == max)
        return;
    for (; (idx + 1) != max; idx++)
        editor_move_up();
}

///////////////////////////////////////////////////////////////////////////////
void editor_all_down(void)
{
    uint_t idx = 0;
    prop_t **arr;

    if (!Editor.focus)
        return;
    arr = find_prop_stack(Editor.focus, &idx);
    if (arr == NULL || idx == 0)
        return;
    for (; idx != 0; idx--)
        editor_move_down();
}
