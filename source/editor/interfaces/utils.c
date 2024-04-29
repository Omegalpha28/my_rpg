/*
** EPITECH PROJECT, 2024
** B-MUL-200-LYN-2-1-myrpg-mallory.scotton
** File description:
** utils
*/

///////////////////////////////////////////////////////////////////////////////
// Headers
///////////////////////////////////////////////////////////////////////////////
#include "rpg.h"

///////////////////////////////////////////////////////////////////////////////
static uint_t get_character_atlas_index(char ch)
{
    if (my_isdigit(ch))
        return (52 + (ch - '0'));
    if (my_islower(ch))
        return (26 + (ch - 'a'));
    if (my_isupper(ch))
        return ((ch - 'A'));
    if (ch == '.')
        return (62);
    if (ch == '-')
        return (63);
    return (0);
}

///////////////////////////////////////////////////////////////////////////////
void draw_text(cstring_t str, v2f_t pos, float scale, sfColor color)
{
    sfSprite *font = sfSprite_create();
    recti_t mask = {0, 0, 20, 20};
    uint_t index = 0;
    float size = 16.0f * scale;

    sfSprite_setTexture(font, Assets.ui[UI_FONT_ATLAS]->self, false);
    sfSprite_setColor(font, color);
    sfSprite_setScale(font, V2F1(scale));
    for (ulong_t i = 0; str[i]; i++) {
        if (!my_isalnum(str[i]) && str[i] != '.' && str[i] != '-')
            continue;
        index = get_character_atlas_index(str[i]);
        sfSprite_setPosition(font, V2F(pos.x + (size - 2 * scale) * i, pos.y +
            (my_strchr(FONT_LOWERED_CHAR, str[i]) ? 1 * scale : 0)));
        mask.top = (index / 8) * 20.0f;
        mask.left = (index % 8) * 20.0f;
        sfSprite_setTextureRect(font, mask);
        sfRenderWindow_drawSprite(Win.self, font, NULL);
    }
    sfSprite_destroy(font);
}

void draw_text_right(cstring_t str, v2f_t pos, float scale, sfColor color)
{
    pos.x -= (strlen(str) * 16.0f * scale * Win.width / Win.viewWidth);
    draw_text(str, PX_TO_MAPF(pos), scale, color);
}

void draw_text_center(cstring_t str, v2f_t pos, float scale, sfColor color)
{
    pos.x -= (strlen(str) / 2.0f) * 16.0f * scale * Win.width / Win.viewWidth;
    draw_text(str, PX_TO_MAPF(pos), scale, color);
}

///////////////////////////////////////////////////////////////////////////////
void draw_rect(v2f_t size, v2f_t pos, sfColor color)
{
    sfRectangleShape *rect = sfRectangleShape_create();

    sfRectangleShape_setFillColor(rect, color);
    sfRectangleShape_setSize(rect, size);
    sfRectangleShape_setScale(rect, FACTORS(size));
    sfRectangleShape_setPosition(rect, PX_TO_MAPF(pos));
    sfRenderWindow_drawRectangleShape(Win.self, rect, NULL);
    sfRectangleShape_destroy(rect);
}

///////////////////////////////////////////////////////////////////////////////
bool_t cursor_inbound(v2f_t position, v2f_t size)
{
    v2i_t cursor = sfMouse_getPositionRenderWindow(Win.self);

    if ((cursor.x >= position.x && cursor.x <= position.x + size.x) &&
        (cursor.y >= position.y && cursor.y <= position.y + size.y))
        return (true);
    return (false);
}

///////////////////////////////////////////////////////////////////////////////
input_t *create_input(input_type_t type, v2f_t position, v2f_t size,
    cstring_t text)
{
    input_t *in = (input_t *)malloc(sizeof(input_t));

    in->checked = false;
    in->content = NULL;
    in->focused = false;
    in->length = 0;
    in->maxLength = 16;
    in->placeholder = my_strdup(text);
    in->position = position;
    in->onInput = NULL;
    in->range[0] = 0;
    in->range[1] = 0;
    in->size = size;
    in->type = type;
    in->disabled = false;
    Editor.inputCount++;
    Editor.inputs = REALLOC(Editor.inputs, sizeof(input_t *),
        Editor.inputCount);
    Editor.inputs[Editor.inputCount - 1] = in;
    return (in);
}

///////////////////////////////////////////////////////////////////////////////
void destroy_input(input_t *input)
{
    input_t **arr = NULL;
    uint_t j = 0;

    if (input == NULL)
        return;
    FREE(input->content);
    FREE(input->placeholder);
    arr = malloc(sizeof(input_t *) * (Editor.inputCount - 1));
    for (uint_t i = 0; i < Editor.inputCount; i++) {
        if (Editor.inputs[i] == input)
            continue;
        arr[j] = Editor.inputs[i];
        j++;
    }
    Editor.inputCount--;
    FREE(Editor.inputs);
    Editor.inputs = arr;
    FREE(input);
}
