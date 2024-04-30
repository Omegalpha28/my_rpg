/*
** EPITECH PROJECT, 2024
** B-MUL-200-LYN-2-1-myrpg-mallory.scotton
** File description:
** init
*/

///////////////////////////////////////////////////////////////////////////////
// Headers
///////////////////////////////////////////////////////////////////////////////
#include "rpg.h"

///////////////////////////////////////////////////////////////////////////////
static void handle_coord_input(input_t *input)
{
    float value = 0.0f;

    if (!Editor.focus)
        return;
    if (input->content != NULL)
        value = atof(input->content);
    if (value > 65536.0f || value < -65536.0f) {
        value = clampf(value, -65536.0f, 65536.0f);
        input_updatef(input, value);
    }
    if (input == Editor.inputs[EDITOR_INPUT_X])
        Editor.focus->position.x = value;
    if (input == Editor.inputs[EDITOR_INPUT_Y])
        Editor.focus->position.y = value;
    prop_set_transform(Editor.focus);
}

///////////////////////////////////////////////////////////////////////////////
static void handle_checkbox_input(input_t *input)
{
    if (!Editor.focus)
        return;
    if (input == Editor.inputs[EDITOR_INPUT_COLLISION])
        Editor.focus->collision = input->checked;
    if (input == Editor.inputs[EDITOR_INPUT_FLIP])
        Editor.focus->scale.x *= -1.0f;
    if (input == Editor.inputs[EDITOR_INPUT_FRAME])
        Editor.focus->data[0] = !Editor.focus->data[0];
}

///////////////////////////////////////////////////////////////////////////////
static void update_focused_frame(int addition)
{
    Editor.focus->data[1] += addition;
    Editor.focus->frame = Editor.focus->data[1];
}

///////////////////////////////////////////////////////////////////////////////
static void handle_button_input(input_t *input)
{
    if (!Editor.focus)
        return;
    if (input == Editor.inputs[EDITOR_INPUT_FORE])
        return (editor_to_foreground());
    if (input == Editor.inputs[EDITOR_INPUT_BACK])
        return (editor_to_background());
    if (input == Editor.inputs[EDITOR_INPUT_DOWN])
        return (editor_move_down());
    if (input == Editor.inputs[EDITOR_INPUT_UP])
        return (editor_move_up());
    if (input == Editor.inputs[EDITOR_INPUT_ADOWN])
        return (editor_all_down());
    if (input == Editor.inputs[EDITOR_INPUT_AUP])
        return (editor_all_up());
    if (input == Editor.inputs[EDITOR_INPUT_PREVIOUS])
        return (update_focused_frame(-1));
    if (input == Editor.inputs[EDITOR_INPUT_NEXT])
        return (update_focused_frame(1));
}

///////////////////////////////////////////////////////////////////////////////
static void editor_set_button_styling(void)
{
    Editor.inputs[EDITOR_INPUT_FORE]->cActive = RGBA(255, 204, 0, 155);
    Editor.inputs[EDITOR_INPUT_BACK]->cActive = RGBA(0, 153, 204, 155);
    Editor.inputs[EDITOR_INPUT_DOWN]->cActive = RGBA(102, 51, 153, 155);
    Editor.inputs[EDITOR_INPUT_UP]->cActive = RGBA(204, 204, 0, 155);
    Editor.inputs[EDITOR_INPUT_ADOWN]->cActive = RGBA(153, 0, 0, 155);
    Editor.inputs[EDITOR_INPUT_AUP]->cActive = RGBA(0, 204, 102, 155);
    for (uint_t i = EDITOR_INPUT_FORE; i <= EDITOR_INPUT_AUP; i++) {
        Editor.inputs[i]->onInput = &handle_button_input;
        Editor.inputs[i]->cHover = Editor.inputs[i]->cActive;
        Editor.inputs[i]->cHover.a = 255;
    }
}

///////////////////////////////////////////////////////////////////////////////
static void editor_settings_init_buttons(v2f_t pos)
{
    create_input(INPUT_BUTTON, pos, V2F(230.0f, 42.0f), "To foreground");
    create_input(INPUT_BUTTON, add2f(pos, V2F(0.0f, 52.0f * 1)),
        V2F(230.0f, 42.0f), "To background");
    create_input(INPUT_BUTTON, add2f(pos, V2F(0.0f, 52.0f * 2)),
        V2F(230.0f, 42.0f), "Move down");
    create_input(INPUT_BUTTON, add2f(pos, V2F(0.0f, 52.0f * 3)),
        V2F(230.0f, 42.0f), "Move up");
    create_input(INPUT_BUTTON, add2f(pos, V2F(0.0f, 52.0f * 4)),
        V2F(230.0f, 42.0f), "Move all down");
    create_input(INPUT_BUTTON, add2f(pos, V2F(0.0f, 52.0f * 5)),
        V2F(230.0f, 42.0f), "Move all up");
    editor_set_button_styling();
}

///////////////////////////////////////////////////////////////////////////////
static void editor_settings_init_frame(v2f_t pos)
{
    create_input(INPUT_CHECKBOX, add2f(pos, V2F(198.0f, 42.0f)),
        V2F(42.0f, 42.0f), NULL);
    Editor.inputs[EDITOR_INPUT_FRAME]->onInput = &handle_checkbox_input;
    create_input(INPUT_BUTTON, add2f(pos, V2F(10.0f, 92.0f)),
        V2F(230.0f, 42.0f), "Previous");
    create_input(INPUT_BUTTON, add2f(pos, V2F(10.0f, 142.0f)),
        V2F(230.0f, 42.0f), "Next");
    Editor.inputs[EDITOR_INPUT_PREVIOUS]->onInput = &handle_button_input;
    Editor.inputs[EDITOR_INPUT_PREVIOUS]->cActive = RGBA(255, 102, 0, 155);
    Editor.inputs[EDITOR_INPUT_PREVIOUS]->cActive = RGBA(255, 102, 0, 255);
    Editor.inputs[EDITOR_INPUT_NEXT]->onInput = &handle_button_input;
    Editor.inputs[EDITOR_INPUT_NEXT]->cActive = RGBA(0, 156, 0, 155);
    Editor.inputs[EDITOR_INPUT_NEXT]->cActive = RGBA(0, 156, 0, 255);
}

///////////////////////////////////////////////////////////////////////////////
void editor_settings_init_input(v2f_t pos)
{
    create_input(INPUT_INTEGER, add2f(pos, V2F(40.0f, 170.0f)),
        V2F(200.0f, 42.0f), "Coordinate X");
    Editor.inputs[EDITOR_INPUT_X]->onInput = &handle_coord_input;
    create_input(INPUT_INTEGER, add2f(pos, V2F(40.0f, 222.0f)),
        V2F(200.0f, 42.0f), "Coordinate Y");
    Editor.inputs[EDITOR_INPUT_Y]->onInput = &handle_coord_input;
    create_input(INPUT_CHECKBOX, add2f(pos, V2F(198.0f, 274.0f)),
        V2F(42.0f, 42.0f), NULL);
    Editor.inputs[EDITOR_INPUT_COLLISION]->onInput = &handle_checkbox_input;
    create_input(INPUT_CHECKBOX, add2f(pos, V2F(198.0f, 326.0f)),
        V2F(42.0f, 42.0f), NULL);
    Editor.inputs[EDITOR_INPUT_FLIP]->onInput = &handle_checkbox_input;
    editor_settings_init_buttons(add2f(pos, V2F(10.0f, 460.0f)));
    editor_settings_init_frame(add2f(pos, V2F(0.0f, 800.0f)));
}
