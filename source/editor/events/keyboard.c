/*
** EPITECH PROJECT, 2024
** B-MUL-200-LYN-2-1-myrpg-mallory.scotton
** File description:
** keyboard
*/

///////////////////////////////////////////////////////////////////////////////
// Headers
///////////////////////////////////////////////////////////////////////////////
#include "rpg.h"

///////////////////////////////////////////////////////////////////////////////
static void handle_editor_key_prop_movement(sfKeyEvent evt)
{
    if (Editor.focus && (evt.code == ALT_UP || evt.code == ALT_DOWN))
        Editor.focus->position.y += evt.code == sfKeyUp ? -1 : +1;
    if (Editor.focus && (evt.code == sfKeyLeft || evt.code == sfKeyRight))
        Editor.focus->position.x += evt.code == sfKeyLeft ? -1 : +1;
    if (Editor.focus && (evt.code >= sfKeyLeft && evt.code <= sfKeyDown)) {
        prop_set_transform(Editor.focus);
        input_updatef(Editor.inputs[EDITOR_INPUT_X], Editor.focus->position.x);
        input_updatef(Editor.inputs[EDITOR_INPUT_Y], Editor.focus->position.y);
    }
}

///////////////////////////////////////////////////////////////////////////////
static void handle_editor_key_copy_paste(sfKeyEvent evt)
{
    if (evt.code == sfKeyDelete)
        editor_delete();
    if (!(PRESSED(sfKeyLControl) || PRESSED(sfKeyRControl)))
        return;
    if (evt.code == sfKeyC)
        editor_copy();
    if (evt.code == sfKeyV)
        editor_paste();
    if (evt.code == sfKeyD)
        editor_duplicate();
    if (evt.code == sfKeyX)
        editor_cut();
}

///////////////////////////////////////////////////////////////////////////////
static void handle_editor_key_animation(sfKeyEvent evt)
{
    if (Editor.focus && evt.code == sfKeySpace)
        prop_animate(Editor.focus);
}

///////////////////////////////////////////////////////////////////////////////
static void handle_editor_key_canvas(sfKeyEvent evt)
{
    if (evt.code == sfKeyO)
        editor_to_origin();
}

///////////////////////////////////////////////////////////////////////////////
static void handle_editor_key_layers(sfKeyEvent evt)
{
    if (evt.code == sfKeyF)
        Editor.layer = EDITOR_LAYER_FOREGROUND;
    if (evt.code == sfKeyB)
        Editor.layer = EDITOR_LAYER_BACKGROUND;
}

///////////////////////////////////////////////////////////////////////////////
void handle_editor_key_pressed(sfKeyEvent evt)
{
    handle_editor_key_prop_movement(evt);
    handle_editor_key_copy_paste(evt);
    handle_editor_key_animation(evt);
    handle_editor_key_canvas(evt);
    handle_editor_key_layers(evt);
}

///////////////////////////////////////////////////////////////////////////////
static void input_add_char(char c)
{
    if (Editor.inputFocused->length == Editor.inputFocused->maxLength)
        return;
    Editor.inputFocused->length++;
    Editor.inputFocused->content = REALLOC(Editor.inputFocused->content, 1,
        Editor.inputFocused->length);
    if (Editor.inputFocused->length == 1) {
        Editor.inputFocused->content[0] = '\0';
        return (input_add_char(c));
    }
    Editor.inputFocused->content[Editor.inputFocused->length - 2] = c;
    Editor.inputFocused->content[Editor.inputFocused->length - 1] = '\0';
    if (Editor.inputFocused->onInput)
        Editor.inputFocused->onInput(Editor.inputFocused);
}

///////////////////////////////////////////////////////////////////////////////
static void input_remove_char(void)
{
    if (Editor.inputFocused->length == 1)
        return;
    Editor.inputFocused->length--;
    Editor.inputFocused->content = REALLOC(Editor.inputFocused->content, 1,
        Editor.inputFocused->length);
    Editor.inputFocused->content[Editor.inputFocused->length - 1] = '\0';
    if (Editor.inputFocused->onInput)
        Editor.inputFocused->onInput(Editor.inputFocused);
}

///////////////////////////////////////////////////////////////////////////////
void handle_editor_key_input(sfKeyEvent evt)
{
    bool_t shift = PRESSED(sfKeyLShift) || PRESSED(sfKeyRShift);
    bool_t ctrl = PRESSED(sfKeyLControl) || PRESSED(sfKeyRControl);
    input_type_t type = Editor.inputFocused->type;

    if ((evt.code >= sfKeyA && evt.code <= sfKeyZ) && type == INPUT_TEXT)
        input_add_char(shift ? evt.code - sfKeyA + 'A' :
            evt.code - sfKeyA + 'a');
    if (evt.code >= sfKeyNum0 && evt.code <= sfKeyNum9)
        input_add_char(evt.code - sfKeyNum0 + '0');
    if (evt.code >= sfKeyNumpad0 && evt.code <= sfKeyNumpad9)
        input_add_char(evt.code - sfKeyNumpad0 + '0');
    if (evt.code == sfKeySemiColon && shift && type != INPUT_INTEGER)
        input_add_char('.');
    if (evt.code == sfKeyBackspace)
        do {
            input_remove_char();
        } while (ctrl && Editor.inputFocused->length != 1);
    if ((evt.code == sfKeySubtract || (evt.code == sfKeyNum6 && !shift)) &&
        Editor.inputFocused->length <= 1)
        input_add_char('-');
}
