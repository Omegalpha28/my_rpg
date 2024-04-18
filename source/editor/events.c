/*
** EPITECH PROJECT, 2024
** B-MUL-200-LYN-2-1-myrpg-mallory.scotton
** File description:
** events
*/

///////////////////////////////////////////////////////////////////////////////
// Headers
///////////////////////////////////////////////////////////////////////////////
#include "rpg.h"

///////////////////////////////////////////////////////////////////////////////
static recti_t get_prop_bound(prop_t *prop)
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
static bool_t search_in_props(bool_t isDisplayed,
    uint_t propCount, prop_t **props)
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
static void search_for_focus(sfMouseButtonEvent evt)
{
    if (search_in_props(Editor.fDisplay, Editor.fCount, Editor.fProps) ||
        search_in_props(Editor.bDisplay, Editor.bCount, Editor.bProps))
        return;
    (evt) = (evt);
    Editor.focus = NULL;
}

///////////////////////////////////////////////////////////////////////////////
static void handle_editor_mouse_button(sfMouseButtonEvent evt)
{
    recti_t bound = get_prop_bound(Editor.focus);
    v2f_t mouse = Editor.crtMouse;

    if ((evt.type == sfEvtMouseButtonPressed && Editor.focus != NULL) &&
        ((mouse.x >= bound.left && mouse.x <= bound.left + bound.width) &&
        (mouse.y >= bound.top && mouse.y <= bound.top + bound.height))) {
        Editor.dragging = true;
        return;
    }
    if (evt.type == sfEvtMouseButtonPressed)
        search_for_focus(evt);
    if (evt.type == sfEvtMouseButtonReleased) {
        Editor.dragging = false;
        if (Editor.focus) {
            Editor.focus->position.x = floorf(Editor.focus->position.x);
            Editor.focus->position.y = floorf(Editor.focus->position.y);
            prop_set_transform(Editor.focus);
        }
    }
}

///////////////////////////////////////////////////////////////////////////////
static void handle_editor_zoom(sfMouseWheelScrollEvent evt)
{
    float zoomFactor = evt.delta < 0 ? 1.1f : 0.9f;
    v2f_t worldMouse = Editor.crtMouse;
    v2f_t newWorldMouse = {0.0f, 0.0f};
    v2f_t offset = {0.0f, 0.0f};

    sfView_zoom(Win.view, zoomFactor);
    newWorldMouse = sfRenderWindow_mapPixelToCoords(Win.self,
        sfMouse_getPositionRenderWindow(Win.self), Win.view);
    offset.x = (worldMouse.x - newWorldMouse.x);
    offset.y = (worldMouse.y - newWorldMouse.y);
    sfView_move(Win.view, offset);
}

///////////////////////////////////////////////////////////////////////////////
static void handle_editor_move(sfMouseWheelScrollEvent evt)
{
    v2f_t offset = {0.0f, 0.0f};
    bool_t ctrl = (PRESSED(sfKeyRControl) || PRESSED(sfKeyLControl));

    if ((ctrl && evt.wheel == 0) || (!ctrl && evt.wheel == 1))
        offset.x = evt.delta * -10;
    else
        offset.y = evt.delta * -10;
    sfView_move(Win.view, offset);
}

///////////////////////////////////////////////////////////////////////////////
static void handle_editor_mouse_scroll(sfMouseWheelScrollEvent evt)
{
    bool_t alt = PRESSED(sfKeyLAlt) || PRESSED(sfKeyRAlt);
    v2f_t newViewSize = {0.0f, 0.0f};

    if (alt)
        handle_editor_zoom(evt);
    else
        handle_editor_move(evt);
    sfRenderWindow_setView(Win.self, Win.view);
    newViewSize = sfView_getSize(Win.view);
    Win.viewWidth = newViewSize.x;
    Win.viewHeight = newViewSize.y;
}

///////////////////////////////////////////////////////////////////////////////
static void handle_editor_key_pressed(sfKeyEvent evt)
{
    if (Editor.focus != NULL && evt.code == sfKeyUp)
        Editor.focus->position.y -= 1;
    if (Editor.focus != NULL && evt.code == sfKeyDown)
        Editor.focus->position.y += 1;
    if (Editor.focus != NULL && evt.code == sfKeyLeft)
        Editor.focus->position.x -= 1;
    if (Editor.focus != NULL && evt.code == sfKeyRight)
        Editor.focus->position.x += 1;
    if (Editor.focus != NULL &&
        (evt.code >= sfKeyLeft && evt.code <= sfKeyDown))
        prop_set_transform(Editor.focus);
}

///////////////////////////////////////////////////////////////////////////////
static void handle_mouse_move(void)
{
    if (Editor.focus == NULL)
        return;
    Editor.focus->position.x += (Editor.crtMouse.x - Editor.oldMouse.x);
    Editor.focus->position.y += (Editor.crtMouse.y - Editor.oldMouse.y);
    Editor.oldMouse = Editor.crtMouse;
    prop_set_transform(Editor.focus);
}

///////////////////////////////////////////////////////////////////////////////
void handle_editor_events(sfEvent evt)
{
    if (evt.type == sfEvtClosed)
        sfRenderWindow_close(Win.self);
    if (evt.type == sfEvtMouseButtonPressed ||
        evt.type == sfEvtMouseButtonReleased)
        handle_editor_mouse_button(evt.mouseButton);
    if (evt.type == sfEvtMouseWheelScrolled)
        handle_editor_mouse_scroll(evt.mouseWheelScroll);
    if (evt.type == sfEvtKeyPressed)
        handle_editor_key_pressed(evt.key);
    if (evt.type == sfEvtMouseMoved && Editor.dragging)
        handle_mouse_move();
}
