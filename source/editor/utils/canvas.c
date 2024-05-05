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
void editor_clear(void)
{
    editor_hide_context();
    for (uint_t i = 0; i < Editor.bCount; i++) {
        if (Editor.bProps[i]->sprite)
            sfSprite_destroy(Editor.bProps[i]->sprite);
        FREE(Editor.bProps[i]);
    }
    FREE(Editor.bProps);
    Editor.bCount = 0;
    for (uint_t i = 0; i < Editor.fCount; i++) {
        if (Editor.fProps[i]->sprite)
            sfSprite_destroy(Editor.fProps[i]->sprite);
        FREE(Editor.fProps[i]);
    }
    FREE(Editor.fProps);
    Editor.fCount = 0;
    Editor.focus = NULL;
    Editor.dragging = false;
}

///////////////////////////////////////////////////////////////////////////////
void editor_to_origin(void)
{
    editor_hide_context();
    Win.viewWidth = DEFAULT_VIEW_WIDTH;
    Win.viewHeight = (float)((float)(DEFAULT_VIEW_WIDTH /
        (float)Win.width)) * Win.height;
    sfView_setSize(Win.view, V2F(Win.viewWidth, Win.viewHeight));
    sfView_setCenter(Win.view, V2F1(0.0f));
    sfRenderWindow_setView(Win.self, Win.view);
}

///////////////////////////////////////////////////////////////////////////////
void editor_reset(void)
{
    editor_clear();
    editor_to_origin();
    Editor.bDisplay = true;
    Editor.bDisplay = true;
    for (uint_t i = 0; i < 4; i++)
        Editor.camera[i] = 0;
    Editor.copy = NULL;
    Editor.hover = false;
    for (uint_t i = 0; i < Editor.inputCount; i++)
        destroy_input(Editor.inputs[i]);
    FREE(Editor.inputs);
    Editor.inputs = NULL;
    Editor.inputCount = 0;
    Editor.inputFocused = NULL;
}

///////////////////////////////////////////////////////////////////////////////
static void editor_zoom(float factor)
{
    float currentZoom = Win.viewWidth / DEFAULT_VIEW_WIDTH;
    v2f_t newSize = V2F1(0.0f);

    if ((currentZoom >= 1000.0f && factor > 1.0f) ||
        (currentZoom <= 0.1f && factor < 1.0f))
        return;
    sfView_zoom(Win.view, factor);
    newSize = sfView_getSize(Win.view);
    Win.viewWidth = newSize.x;
    Win.viewHeight = newSize.y;
    sfRenderWindow_setView(Win.self, Win.view);
}

///////////////////////////////////////////////////////////////////////////////
void editor_zoom_in(void)
{
    editor_zoom(0.9f);
}

///////////////////////////////////////////////////////////////////////////////
void editor_zoom_out(void)
{
    editor_zoom(1.1f);
}
