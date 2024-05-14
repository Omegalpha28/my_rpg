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

bool_t click_rel(sfEvent evt)
{
    return (evt.type == sfEvtMouseButtonReleased &&
        evt.mouseButton.button == Setting.shoot);
}

static void draw_slots(void)
{
    sfSprite *slot = sfSprite_create();
    v2f_t size = {24.5f, 28.0f};
    float change = size.x * 2 * Win.width / Win.viewWidth;
    float move = size.y * 0.55f * Win.height / Win.viewHeight;

    sfSprite_setTexture(slot, Assets.ui[UI_INV_SLOT]->self, false);
    sfSprite_setScale(slot, V2F1(0.75f));
    sfSprite_setOrigin(slot, size);
    for (int i = 0; i < 15; i++) {
        sfSprite_setPosition(slot, PX_TO_MAPF(V2F(Win.width / 8 * 5 + change +
            change * (i % 3), Win.height / 2 - move * (6 - (i - i % 3)))));
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
    draw_text_center("inventaire", (V2F1(300.0f)), 0.45f, sfWhite);
    draw_cursor();
}
