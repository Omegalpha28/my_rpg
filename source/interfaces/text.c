/*
** EPITECH PROJECT, 2024
** B-MUL-200-LYN-2-1-myrpg-mallory.scotton
** File description:
** text
*/

///////////////////////////////////////////////////////////////////////////////
// Headers
///////////////////////////////////////////////////////////////////////////////
#include "rpg.h"

///////////////////////////////////////////////////////////////////////////////
void draw_text_right(cstring_t str, v2f_t pos, float scale, sfColor color)
{
    pos.x -= (strlen(str) * 16.0f * scale * Win.width / Win.viewWidth);
    draw_text(str, PX_TO_MAPF(pos), scale, color);
}

///////////////////////////////////////////////////////////////////////////////
void draw_text_center(cstring_t str, v2f_t pos, float scale, sfColor color)
{
    pos.x -= (strlen(str) / 2.0f) * 16.0f * scale * Win.width / Win.viewWidth;
    draw_text(str, PX_TO_MAPF(pos), scale, color);
}

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
