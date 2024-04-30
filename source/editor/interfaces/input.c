/*
** EPITECH PROJECT, 2024
** B-MUL-200-LYN-2-1-myrpg-mallory.scotton
** File description:
** input
*/

///////////////////////////////////////////////////////////////////////////////
// Headers
///////////////////////////////////////////////////////////////////////////////
#include "rpg.h"

///////////////////////////////////////////////////////////////////////////////
static void editor_draw_input_carret(input_t *input)
{
    float offsetX = 15.0f * ((float)(input->length) - 1.0f);

    if (offsetX < 0.0f)
        offsetX = 0.0f;
    if (fmodf((float)Time.currentTime / 1000.0f, 1.0f) < 0.50f)
        draw_rect(V2F(3.0f, 20.0f), add2f(input->position, V2F(5.0f + offsetX,
            (input->size.y - 20.0f) / 2.0f)), sfWhite);
}

///////////////////////////////////////////////////////////////////////////////
static void editor_input_checkbox(input_t *input)
{
    v2f_t pos = add2f(input->position, V2F(6.0f, (input->size.y - 30.0f) /
        2.0f));
    float fact = FACTORS(V2F1(20.0f)).x * 1.5f;

    if (input->checked == false || input->disabled)
        return;
    draw_text("X", PX_TO_MAPF(pos), fact, RGB(52, 130, 246));
}

///////////////////////////////////////////////////////////////////////////////
static void editor_input_content(input_t *input)
{
    v2f_t pos = add2f(input->position, V2F(5.0f, (input->size.y - 20.0f) /
        2.0f));
    float fact = FACTORS(V2F1(20.0f)).x;

    if (Editor.inputFocused == input && !input->disabled)
        editor_draw_input_carret(input);
    if (input->content == NULL || input->length == 1) {
        if (!input->placeholder)
            return;
        return (draw_text(input->placeholder, PX_TO_MAPF(pos), fact,
            RGBA(255, 255, 255, 150)));
    }
    draw_text(input->content, PX_TO_MAPF(pos), fact, input->disabled ?
        RGBA(255, 255, 255, 200) : sfWhite);
}

///////////////////////////////////////////////////////////////////////////////
static void editor_input_button(input_t *input)
{
    v2f_t pos = add2f(input->position, V2F(6.0f, (input->size.y - 30.0f) /
        2.0f));
    float fact = FACTORS(V2F1(20.0f)).x;

    draw_text(input->placeholder, PX_TO_MAPF(pos), fact, input->disabled ?
        RGBA(255, 255, 255, 200) : WHITE);
}

///////////////////////////////////////////////////////////////////////////////
static void draw_input_base(input_t *input, bool_t hover)
{
    sfColor clr = input->cActive;

    if (hover || Editor.inputFocused == input)
        clr = input->cHover;
    if (input->disabled)
        clr = input->cDisabled;
    draw_rect(input->size, input->position, clr);
}

///////////////////////////////////////////////////////////////////////////////
void editor_draw_input(input_t *input)
{
    bool_t hover = cursor_inbound(input->position, input->size) ||
        Editor.inputFocused == input;

    draw_input_base(input, hover);
    if (hover && MPRESSED(sfMouseLeft) && !input->disabled &&
        Editor.released) {
        if (input->type != INPUT_CHECKBOX && input->type != INPUT_BUTTON)
            Editor.inputFocused = input;
        else {
            input->checked = !input->checked;
            input->onInput(input);
        }
        Editor.released = false;
    }
    if (input->type == INPUT_CHECKBOX)
        return (editor_input_checkbox(input));
    if (input->type == INPUT_BUTTON)
        return (editor_input_button(input));
    editor_input_content(input);
}
