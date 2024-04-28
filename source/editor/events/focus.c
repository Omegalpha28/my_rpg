/*
** EPITECH PROJECT, 2024
** B-MUL-200-LYN-2-1-myrpg-mallory.scotton
** File description:
** focus
*/

///////////////////////////////////////////////////////////////////////////////
// Headers
///////////////////////////////////////////////////////////////////////////////
#include "rpg.h"

///////////////////////////////////////////////////////////////////////////////
recti_t get_prop_bound(prop_t *prop)
{
    recti_t bound;

    if (prop == NULL || prop->self == NULL || prop->self->image == NULL)
        return ((recti_t){0, 0, 0, 0});
    bound.width = prop->self->image->mask.width;
    bound.height = prop->self->image->mask.height;
    bound.top = (prop->position.y - (bound.height / 2.0f));
    bound.left = (prop->position.x - (bound.width / 2.0f));
    return (bound);
}

///////////////////////////////////////////////////////////////////////////////
bool_t search_in_props(bool_t isDisplayed, uint_t propCount, prop_t **props)
{
    recti_t bound;
    v2f_t mouse = Editor.crtMouse;

    for (int i = (int)(propCount - 1); isDisplayed && i >= 0; i--) {
        bound = get_prop_bound(props[i]);
        if (bound.width == 0 || bound.height == 0)
            continue;
        if ((mouse.x >= bound.left && mouse.x <= bound.left + bound.width) &&
            (mouse.y >= bound.top && mouse.y <= bound.top + bound.height)) {
            Editor.focus = props[i];
            Editor.dragging = true;
            return (true);
        }
    }
    return (false);
}

///////////////////////////////////////////////////////////////////////////////
void search_for_focus(void)
{
    if (search_in_props(Editor.fDisplay, Editor.fCount, Editor.fProps) ||
        search_in_props(Editor.bDisplay, Editor.bCount, Editor.bProps))
        return;
    Editor.focus = NULL;
}
