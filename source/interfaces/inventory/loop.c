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
    draw_text_center("inventaire", (V2F1(300.0f)), 0.45f, sfWhite);
    draw_cursor();
}
