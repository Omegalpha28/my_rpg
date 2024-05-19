/*
** EPITECH PROJECT, 2024
** myrpg
** File description:
** loop
*/

///////////////////////////////////////////////////////////////////////////////
// Headers
///////////////////////////////////////////////////////////////////////////////
#include "rpg.h"

bool_t key_rel(sfEvent evt)
{
    return (evt.type == sfEvtKeyReleased);
}

bool_t click_rel(sfEvent evt)
{
    return (evt.type == sfEvtMouseButtonReleased &&
        evt.mouseButton.button == Setting.shoot);
}

static void draw_discovered(uint_t index)
{
    index = index;
}

static void draw_slots(void)
{
    sfSprite *slot = sfSprite_create();
    v2f_t size = {16.0f, 16.0f};
    float change = size.x * Win.width / Win.viewWidth * 1.5f;
    float move = size.y * Win.height / Win.viewHeight / 10 * 1.5f * 1.5f;

    sfSprite_setTexture(slot, Assets.ui[UI_LOCKED_AXO]->self, false);
    for (int i = 0; i < AXO_COUNT; i++) {
        sfSprite_setPosition(slot, PX_TO_MAPF(V2F(change * 1.5 + change *
            (i % 9), Win.height / 2 - move * 24 + move * (i - i % 9))));
        if (Assets.axolotl[i]->is_egg || Assets.axolotl[i]->is_baby ||
            Assets.axolotl[i]->is_teen || Assets.axolotl[i]->is_adult)
            draw_discovered(i);
        else
            sfRenderWindow_drawSprite(Win.self, slot, false);
    }
    sfSprite_destroy(slot);
}

void inventory_loop(void)
{
    sfEvent evt;

    while (sfRenderWindow_pollEvent(Win.self, &evt)) {
        if (evt.type == sfEvtClosed)
            sfRenderWindow_close(Win.self);
        CLICK_REL = click_rel(evt);
        if (evt.type == sfEvtKeyReleased &&
            (evt.key.code == Setting.inventory.code ||
            evt.key.code == Setting.pause.code))
            Engine.scene = SCENE_GAME;
    }
    Setting.hover = false;
    draw();
    draw_shadow();
    draw_slots();
    draw_cursor();
}
