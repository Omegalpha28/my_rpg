/*
** EPITECH PROJECT, 2024
** myrpg
** File description:
** player_change
*/

///////////////////////////////////////////////////////////////////////////////
// Headers
///////////////////////////////////////////////////////////////////////////////
#include "rpg.h"

sfColor get_color(v2f_t pos, cstring_t axo_name, uint_t id)
{
    v2f_t mouse = PX_TO_MAPF(sfMouse_getPositionRenderWindow(Win.self));
    bool_t mouse_in = mouse.y >= (pos.y - 10) && mouse.y <= (pos.y + 15) &&
        mouse.x >= pos.x - 10 && mouse.x <= pos.x + 15;
    sfSprite *select;

    if (!mouse_in)
        return (sfWhite);
    select = sfSprite_create();
    sfSprite_setTexture(select, Assets.ui[UI_DUAL_MARK_SMALL]->self, false);
    sfSprite_setPosition(select, V2F(pos.x - 69.5f, pos.y - 8));
    sfRenderWindow_drawSprite(Win.self, select, NULL);
    sfSprite_destroy(select);
    if (CLICK_REL && mouse_in) {
        Player.ref->shield = Assets.axolotl[id]->shields;
        actor_set_variant(Player.ref, axo_name, id);
        Engine.scene = SCENE_GAME;
    }
    return (sfColor_fromRGB(243, 199, 77));
}

void change_player(cstring_t axo_name, uint_t id)
{
    float move = 16.0f * Win.height / Win.viewHeight / 10 * 1.5f * 1.5f;

    draw_text_center("Use", V2F(Win.width / 4 * 3, Win.height - move * 15),
        0.45f, get_color(PX_TO_MAPF(V2F(Win.width / 4 * 3,
        Win.height - move * 15)), axo_name, id));
}
