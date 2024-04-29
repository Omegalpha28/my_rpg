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
void editor_draw_input(input_t *input)
{
    bool_t hover = cursor_inbound(input->position, input->size) ||
        Editor.inputFocused == input;

    draw_rect(input->size, input->position, hover ? EDITOR_HOVER :
        EDITOR_BUTTON);
    if (hover && MPRESSED(sfMouseLeft) && !input->disabled)
        Editor.inputFocused = input;
    if (Editor.inputFocused == input && !input->disabled)
        editor_draw_input_carret(input);
    if (input->content == NULL || input->length == 1) {
        draw_text(input->placeholder, PX_TO_MAPF(add2f(input->position, V2F(
            5.0f, (input->size.y - 20.0f) / 2.0f))), FACTORS(V2F1(20.0f)).x,
            RGBA(255, 255, 255, 150));
        return;
    }
    draw_text(input->content, PX_TO_MAPF(add2f(input->position, V2F(5.0f,
        (input->size.y - 20.0f) / 2.0f))), FACTORS(V2F1(20.0f)).x,
            input->disabled ? RGBA(255, 255, 255, 200) : sfWhite);
}
