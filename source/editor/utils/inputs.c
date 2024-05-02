/*
** EPITECH PROJECT, 2024
** B-MUL-200-LYN-2-1-myrpg-mallory.scotton
** File description:
** inputs
*/

///////////////////////////////////////////////////////////////////////////////
// Headers
///////////////////////////////////////////////////////////////////////////////
#include "rpg.h"

///////////////////////////////////////////////////////////////////////////////
void input_updatef(input_t *input, float value)
{
    FREE(input->content);
    input->content = malloc(sizeof(char) * input->maxLength);
    input->length = (uint_t)snprintf(input->content, input->maxLength,
        "%.0f", value) + 1;
}

///////////////////////////////////////////////////////////////////////////////
void input_clear(input_t *input)
{
    FREE(input->content);
    input->length = 0;
}

///////////////////////////////////////////////////////////////////////////////
void open_save_popup(void)
{
    Editor.popupOpen = true;
    Editor.popupType = POPUP_SAVE;
    editor_hide_context();
    Editor.inputFocused = Editor.inputs[EDITOR_INPUT_PATH];
}

///////////////////////////////////////////////////////////////////////////////
void open_open_popup(void)
{
    Editor.popupOpen = true;
    Editor.popupType = POPUP_OPEN;
    editor_hide_context();
    Editor.inputFocused = Editor.inputs[EDITOR_INPUT_PATH];
}
