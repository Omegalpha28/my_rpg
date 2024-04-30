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
    bool_t focused = (Editor.focus != NULL);

    Editor.inputs[EDITOR_INPUT_X]->disabled = !focused;
    Editor.inputs[EDITOR_INPUT_Y]->disabled = !focused;
    Editor.inputs[EDITOR_INPUT_COLLISION]->disabled = !focused;
    Editor.inputs[EDITOR_INPUT_FLIP]->disabled = !focused;
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
        105.0f))), FACTORS(V2F1(20.0f)).x / 1.05f, WHITE);
}

///////////////////////////////////////////////////////////////////////////////
static void find_id_and_max(uint_t *idx, uint_t *max)
{
    for (uint_t i = 0; i < Editor.fCount; i++) {
        if (Editor.fProps[i] == Editor.focus) {
            *idx = i;
            *max = Editor.fCount;
            return;
        }
    }
    for (uint_t i = 0; i < Editor.bCount; i++) {
        if (Editor.bProps[i] == Editor.focus) {
            *idx = i;
            *max = Editor.bCount;
        }
    }
}

///////////////////////////////////////////////////////////////////////////////
static void draw_editor_settings_info(v2f_t pos, float fact)
{
    char zIndex[32];
    uint_t idx = 0;
    uint_t max = 0;

    draw_text("Index", PX_TO_MAPF(add2f(pos, V2F(10.0f, 136.0f))), fact,
        WHITE);
    if (!Editor.focus)
        return;
    draw_focused_prop(add2f(pos, V2F(75.0f, 0.0f)));
    find_id_and_max(&idx, &max);
    snprintf(zIndex, 32, "%u - %u", idx + 1, max);
    draw_text(zIndex, PX_TO_MAPF(add2f(pos, V2F(90.0f, 136.0f))), fact,
        RGB(200, 200, 0));
}

///////////////////////////////////////////////////////////////////////////////
static void draw_editor_settings_label(v2f_t pos, float fact)
{
    draw_text("X", PX_TO_MAPF(add2f(pos, V2F(10.0f, 181.0f))), fact, WHITE);
    draw_text("Y", PX_TO_MAPF(add2f(pos, V2F(10.0f, 233.0f))), fact, WHITE);
    draw_text("Collision", PX_TO_MAPF(add2f(pos, V2F(10.0f, 285.0f))), fact,
        WHITE);
    draw_text("Flip", PX_TO_MAPF(add2f(pos, V2F(10.0f, 337.0f))), fact, WHITE);
}

///////////////////////////////////////////////////////////////////////////////
void draw_editor_settings(void)
{
    v2f_t pos = {Win.width - EDITOR_PANEL_W, EDITOR_PANEL_H * 2.0f};
    float fact = FACTORS(V2F1(20.0f)).x;

    if (Editor.inputCount == 0)
        editor_settings_init_input(pos);
    settings_update_input_state();
    draw_rect(V2F(EDITOR_PANEL_W, Win.height - EDITOR_PANEL_H * 2), pos,
        EDITOR_WIDGET);
    draw_rect(V2F1(100.0f), add2f(pos, V2F(75.0f, 0.0f)), EDITOR_BUTTON);
    draw_editor_settings_info(pos, fact);
    draw_editor_settings_label(pos, fact);
}
