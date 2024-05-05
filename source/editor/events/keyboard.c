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
static void handle_editor_key_layer(sfKeyEvent evt)
{
    bool_t shift = PRESSED(sfKeyLShift) || PRESSED(sfKeyRShift);

    if (!shift && evt.code == ALT_DOWN)
        editor_move_down();
    if (shift && evt.code == ALT_DOWN)
        editor_all_down();
    if (!shift && evt.code == ALT_UP)
        editor_move_up();
    if (shift && evt.code == ALT_UP)
        editor_all_up();
}

///////////////////////////////////////////////////////////////////////////////
static void handle_editor_key_prop_movement(sfKeyEvent evt)
{
    bool_t ctrl = PRESSED(sfKeyLControl) || PRESSED(sfKeyRControl);

    if (Editor.focus && (evt.code == ALT_UP || evt.code == ALT_DOWN)) {
        if (ctrl)
            return (handle_editor_key_layer(evt));
        Editor.focus->position.y += evt.code == sfKeyUp ? -1 : +1;
    }
    if (Editor.focus && (evt.code == ALT_LEFT || evt.code == ALT_RIGHT))
        Editor.focus->position.x += evt.code == sfKeyLeft ? -1 : +1;
    if (Editor.focus && (evt.code >= sfKeyLeft && evt.code <= sfKeyDown)) {
        prop_set_transform(Editor.focus);
        input_focus_update();
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
    if (evt.code == sfKeyS && (Editor.fCount + Editor.bCount) > 0)
        open_save_popup();
    if (evt.code == sfKeyO)
        open_open_popup();
}

///////////////////////////////////////////////////////////////////////////////
static void handle_editor_single_key(sfKeyEvent evt)
{
    if (evt.code == sfKeyF)
        Editor.layer = EDITOR_LAYER_FOREGROUND;
    if (evt.code == sfKeyB)
        Editor.layer = EDITOR_LAYER_BACKGROUND;
    if (evt.code == sfKeyO)
        editor_to_origin();
    if (Editor.focus && evt.code == sfKeySpace)
        prop_animate(Editor.focus);
}

///////////////////////////////////////////////////////////////////////////////
static void handle_editor_input_enter(void)
{
    if (Editor.inputFocused->type == INPUT_CHECKBOX)
        Editor.inputFocused->checked = !Editor.inputFocused->checked;
    if (Editor.inputFocused->type == INPUT_TEXT ||
        Editor.inputFocused->type == INPUT_FLOAT ||
        Editor.inputFocused->type == INPUT_INTEGER)
        Editor.inputFocused = NULL;
}

///////////////////////////////////////////////////////////////////////////////
static void handle_editor_camera_key(sfKeyEvent evt)
{
    if (evt.code == sfKeyNumpad8 && !PRESSED(sfKeyLControl))
        Editor.camera[2]++;
    if (evt.code == sfKeyNumpad8 && PRESSED(sfKeyLControl))
        Editor.camera[2]--;
    if (evt.code == sfKeyNumpad5 && !PRESSED(sfKeyLControl))
        Editor.camera[3]++;
    if (evt.code == sfKeyNumpad5 && PRESSED(sfKeyLControl))
        Editor.camera[3]--;
    if (evt.code == sfKeyNumpad4 && !PRESSED(sfKeyLControl))
        Editor.camera[0]++;
    if (evt.code == sfKeyNumpad4 && PRESSED(sfKeyLControl))
        Editor.camera[0]--;
    if (evt.code == sfKeyNumpad6 && !PRESSED(sfKeyLControl))
        Editor.camera[1]++;
    if (evt.code == sfKeyNumpad6 && PRESSED(sfKeyLControl))
        Editor.camera[1]--;
}

///////////////////////////////////////////////////////////////////////////////
void handle_editor_key_pressed(sfKeyEvent evt)
{
    handle_editor_key_prop_movement(evt);
    handle_editor_key_copy_paste(evt);
    handle_editor_single_key(evt);
    if (Editor.inputFocused && evt.code == sfKeyEnter)
        handle_editor_input_enter();
    handle_editor_camera_key(evt);
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
