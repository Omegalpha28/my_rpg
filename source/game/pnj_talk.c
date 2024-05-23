/*
** EPITECH PROJECT, 2024
** myrpg
** File description:
** pnj_talk
*/

///////////////////////////////////////////////////////////////////////////////
// Headers
///////////////////////////////////////////////////////////////////////////////
#include "rpg.h"

///////////////////////////////////////////////////////////////////////////////
void draw_interact(void)
{
    v2f_t scale = {Win.width / Win.viewWidth, Win.height / Win.viewHeight};
    sfSprite *bac = sfSprite_create();
    string_t butt = conv(Setting.interact.code + 'a');

    sfSprite_setTexture(bac, Assets.ui[UI_KEY]->self, false);
    sfSprite_setOrigin(bac, V2F(5.5f, 6.0f));
    sfSprite_setPosition(bac, PX_TO_MAPF(V2F(Win.width / 2 + 16 * scale.x,
        Win.height / 4 * 3 + 4 * scale.y)));
    sfRenderWindow_drawSprite(Win.self, bac, false);
    sfSprite_destroy(bac);
    draw_text_center(butt, V2F(Win.width / 2 + 16 * scale.x,
        Win.height / 4 * 3), 0.3f, sfColor_fromRGB(124, 137, 138));
    free(butt);
    draw_text_center("Interact", V2F(Win.width / 2 - 16 * scale.x,
        Win.height / 4 * 3), 0.35f, sfWhite);
}

///////////////////////////////////////////////////////////////////////////////
void pnj_talk(cstring_t text, cstring_t name)
{
    sfSprite *pnj = sfSprite_create();
    v2f_t scale = {Win.width / Win.viewWidth, Win.height / Win.viewHeight};

    sfSprite_setTexture(pnj, Assets.ui[UI_KEY]->self, false);
    sfSprite_setScale(pnj, V2F1(0.75f));
    sfSprite_setOrigin(pnj, V2F(64.5f, 115.0f));
    sfSprite_setPosition(pnj, PX_TO_MAPF(V2F(Win.width / 4 - scale.x * 16.0f,
        Win.height)));
    draw_shadow();
    sfRenderWindow_drawSprite(Win.self, pnj, false);
    draw_text(name, PX_TO_MAPF(V2F(Win.width / 3 + scale.x * 16,
        Win.height / 5 * 3.5f)), 0.45f, sfWhite);
    draw_text(text, PX_TO_MAPF(V2F(Win.width / 3 + scale.x * 6,
        Win.height / 5 * 3.5f + 16.0f * scale.y)), 0.35f, sfWhite);
    sfSprite_destroy(pnj);
}
