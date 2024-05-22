/*
** EPITECH PROJECT, 2024
** B-MUL-200-LYN-2-1-myrpg-mallory.scotton
** File description:
** debug
*/

///////////////////////////////////////////////////////////////////////////////
// Headers
///////////////////////////////////////////////////////////////////////////////
#include "rpg.h"


///////////////////////////////////////////////////////////////////////////////
/// \brief Once animation is done, stop drawing.
///
///////////////////////////////////////////////////////////////////////////////
static void termination(void)
{
    if (!Player.ref->done || !Player.ref->draw)
        return;
    if (Player.ref->damaged){
        Player.ref->damaged = !Player.ref->damaged;
        Player.ref->invincible = !Player.ref->invincible;
        return;
    }
    Player.ref->draw = !Player.ref->draw;
}

///////////////////////////////////////////////////////////////////////////////
void check_player_health(void)
{
    actor_t *act = Player.ref;

    if (act->damaged){
        if (!actor_set_anim(act, "damage"))
            act->done = true;
    }
    if (act->health <= 0 && !act->dead && !act->damaged) {
        act->dead = true;
        actor_set_anim(act, "death");
    }
    if (act->dead || act->damaged)
        termination();
}
