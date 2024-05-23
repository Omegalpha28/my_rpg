/*
** EPITECH PROJECT, 2024
** csfml-engine
** File description:
** events
*/

///////////////////////////////////////////////////////////////////////////////
// Headers
///////////////////////////////////////////////////////////////////////////////
#include "rpg.h"

///////////////////////////////////////////////////////////////////////////////
void parse_events(sfEvent evt)
{
    if (evt.type == sfEvtClosed)
        sfRenderWindow_close(Win.self);
    if (evt.type == sfEvtKeyPressed || evt.type == sfEvtKeyReleased)
        parse_key_input(evt.key);
    if ((evt.type == sfEvtMouseWheelScrolled && evt.mouseWheelScroll.delta < 0
        ) || (evt.type == sfEvtKeyPressed && evt.key.code == sfKeyNum1)) {
        if (Player.weapon != Player.inventor[0])
            sfx(SFX_WEAPON_SWAP_HANDLING);
        Player.weapon = Player.inventor[0];
    }
    if (((evt.type == sfEvtMouseWheelScrolled && evt.mouseWheelScroll.delta >
        0) || (evt.type == sfEvtKeyPressed && evt.key.code == sfKeyNum2))
        && Player.inventor[1] != WEAPON_NO) {
        if (Player.weapon != Player.inventor[1])
            sfx(SFX_WEAPON_SWAP_HANDLING);
        Player.weapon = Player.inventor[1];
    }
}
