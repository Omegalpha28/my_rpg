/*
** EPITECH PROJECT, 2024
** B-MUL-200-LYN-2-1-myrpg-mallory.scotton
** File description:
** canvas
*/

///////////////////////////////////////////////////////////////////////////////
// Headers
///////////////////////////////////////////////////////////////////////////////
#include "rpg.h"

///////////////////////////////////////////////////////////////////////////////
static void handle_editor_mouse_invertion(sfMouseButtonEvent evt)
{
    if (evt.button == sfMouseRight && Editor.focus)
        Editor.focus->scale.x *= -1.0f;
}

///////////////////////////////////////////////////////////////////////////////
void handle_editor_mouse_button(sfMouseButtonEvent evt)
{
    recti_t bound = get_prop_bound(Editor.focus);
    v2f_t mouse = Editor.crtMouse;

    if ((evt.type == sfEvtMouseButtonPressed && Editor.focus != NULL) &&
        ((mouse.x >= bound.left && mouse.x <= bound.left + bound.width) &&
        (mouse.y >= bound.top && mouse.y <= bound.top + bound.height))) {
        handle_editor_mouse_invertion(evt);
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
    v2f_t newWorldMouse = V2F1(0.0f);
    v2f_t offset = V2F1(0.0f);

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
    v2f_t offset = V2F1(0.0f);
    bool_t ctrl = (PRESSED(sfKeyRControl) || PRESSED(sfKeyLControl));

    if ((ctrl && evt.wheel == 0) || (!ctrl && evt.wheel == 1))
        offset.x = evt.delta * -10;
    else
        offset.y = evt.delta * -10;
    sfView_move(Win.view, offset);
}

///////////////////////////////////////////////////////////////////////////////
static void handle_editor_ui_scroll(sfMouseWheelScrollEvent evt)
{
    Editor.scrollingOffset += 10.0f * evt.delta;
    if (Editor.scrollingOffset > 0)
        Editor.scrollingOffset = 0;
}

///////////////////////////////////////////////////////////////////////////////
void handle_editor_mouse_scroll(sfMouseWheelScrollEvent evt)
{
    bool_t alt = PRESSED(sfKeyLAlt) || PRESSED(sfKeyRAlt);
    v2f_t newViewSize = V2F1(0.0f);
    v2i_t cr = sfMouse_getPositionRenderWindow(Win.self);

    if ((cr.x >= 0 && cr.x <= 250.0f && cr.y >= 84.0f))
        return (handle_editor_ui_scroll(evt));
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
void handle_mouse_move(void)
{
    if (Editor.focus == NULL || !Editor.dragging)
        return;
    Editor.focus->position.x += (Editor.crtMouse.x - Editor.oldMouse.x);
    Editor.focus->position.y += (Editor.crtMouse.y - Editor.oldMouse.y);
    Editor.oldMouse = Editor.crtMouse;
    prop_set_transform(Editor.focus);
}
