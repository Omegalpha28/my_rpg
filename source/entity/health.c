/*
** EPITECH PROJECT, 2024
** my_rpg
** File description:
** death
*/

///////////////////////////////////////////////////////////////////////////////
// Headers
///////////////////////////////////////////////////////////////////////////////
#include "rpg.h"

///////////////////////////////////////////////////////////////////////////////
/// \brief Once animation is done, stop drawing.
///
/// \param evil         taking damage.
///
///////////////////////////////////////////////////////////////////////////////
static void termination(entity_t *evil)
{
    if (!evil->actor->done || !evil->actor->draw)
        return;
    if (evil->actor->damaged){
        evil->actor->damaged = !evil->actor->damaged;
        evil->actor->invincible = !evil->actor->invincible;
        return;
    }
    evil->actor->draw = !evil->actor->draw;
    Player.ref->charges += Player.ref->charges < 5 ? 1 : 0;
    for (uint_t i = 0; i < ENTITY_REMOVE; i++) {
        if (Entities.toRemove[i] != NULL)
            continue;
        Entities.toRemove[i] = evil;
        break;
    }
}

///////////////////////////////////////////////////////////////////////////////
void health_examination(entity_t *evil)
{
    actor_t *act = evil->actor;

    if (act->damaged){
        if (!actor_set_anim(act, "damage") && !actor_set_sheet(act, "damage"))
            evil->actor->done = true;
    }
    if (act->health <= 0 && !act->dead && !act->damaged) {
        sfx(SFX_ENEMY_DEATH);
        act->dead = true;
        if (actor_set_sheet(act, "death"))
            act->position.x +=
            (act->self->sheets[act->sheetId]->image->mask.width / 4) *
            ((act->scale.x) < 0 ? 1 : -1);
        actor_set_anim(act, "death");
    }
    if (act->dead || act->damaged)
        termination(evil);
}
