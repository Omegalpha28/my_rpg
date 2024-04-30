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
    if (input == Editor.inputs[EDITOR_INPUT_COLLISION] && Editor.focus)
        Editor.focus->collision = input->checked;
}

///////////////////////////////////////////////////////////////////////////////
void editor_settings_init_input(v2f_t pos)
{
    create_input(INPUT_INTEGER, add2f(pos, V2F(40.0f, 140.0f)),
        V2F(200.0f, 42.0f), "Coordinate X");
    Editor.inputs[EDITOR_INPUT_X]->onInput = &handle_coord_input;
    create_input(INPUT_INTEGER, add2f(pos, V2F(40.0f, 192.0f)),
        V2F(200.0f, 42.0f), "Coordinate Y");
    Editor.inputs[EDITOR_INPUT_Y]->onInput = &handle_coord_input;
    create_input(INPUT_CHECKBOX, add2f(pos, V2F(160.0f, 244.0f)),
        V2F(42.0f, 42.0f), NULL);
    Editor.inputs[EDITOR_INPUT_COLLISION]->onInput = &handle_checkbox_input;
}
