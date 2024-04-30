/*
** EPITECH PROJECT, 2024
** B-MUL-200-LYN-2-1-myrpg-mallory.scotton
** File description:
** settings
*/

///////////////////////////////////////////////////////////////////////////////
// Headers
///////////////////////////////////////////////////////////////////////////////
#include "rpg.h"

///////////////////////////////////////////////////////////////////////////////
static void settings_update_input_state(void)
{
    Editor.inputs[EDITOR_INPUT_X]->disabled = (Editor.focus == NULL);
    Editor.inputs[EDITOR_INPUT_Y]->disabled = (Editor.focus == NULL);
}

///////////////////////////////////////////////////////////////////////////////
static void draw_focused_prop(v2f_t pos)
{
    sfSprite *preview = sfSprite_create();
    recti_t mask = Editor.focus->self->image->mask;
    float maxDist = mask.width > mask.height ? mask.width : mask.height;
    float scale = 80.0f / maxDist;
    v2f_t size = V2F(mask.width * scale, mask.height * scale);
    v2f_t fact = multiply2f(FACTORS(size), V2F(scale, scale));

    sfSprite_setTexture(preview, Editor.focus->self->image->self, false);
    sfSprite_setTextureRect(preview, mask);
    sfSprite_setOrigin(preview, V2F(mask.width / 2.0f, mask.height / 2.0f));
    sfSprite_setScale(preview, fact);
    sfSprite_setPosition(preview, PX_TO_MAPF(add2f(pos, V2F1(50.0f))));
    sfRenderWindow_drawSprite(Win.self, preview, NULL);
    sfSprite_destroy(preview);
    draw_text(Editor.focus->self->name, PX_TO_MAPF(add2f(pos, V2F(-65.0f,
        105.0f))), FACTORS(V2F1(20.0f)).x / 1.05f, sfWhite);
}

///////////////////////////////////////////////////////////////////////////////
void draw_editor_settings(void)
{
    float fact = FACTORS(V2F1(20.0f)).x;
    v2f_t pos = {Win.width - EDITOR_PANEL_W, EDITOR_PANEL_H * 2.0f};

    if (Editor.inputCount == 0)
        editor_settings_init_input(pos);
    settings_update_input_state();
    draw_rect(V2F(EDITOR_PANEL_W, Win.height - EDITOR_PANEL_H * 2), pos,
        EDITOR_WIDGET);
    draw_rect(V2F1(100.0f), add2f(pos, V2F(75.0f, 0.0f)), EDITOR_BUTTON);
    if (Editor.focus)
        draw_focused_prop(add2f(pos, V2F(75.0f, 0.0f)));
    draw_text("X", PX_TO_MAPF(add2f(pos, V2F(10.0f, 151.0f))), fact, sfWhite);
    draw_text("Y", PX_TO_MAPF(add2f(pos, V2F(10.0f, 203.0f))), fact, sfWhite);
}
