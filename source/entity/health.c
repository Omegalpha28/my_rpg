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
        evil->actor->invincible = false;
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
static void boss_exclusive(entity_t *boss)
{
    if (boss->curr_phase == 0 && boss->actor->health <=
        (int)Stats[boss->actor->self->id].health / 2 && boss->status != Fear){
        actor_set_sheet(boss->actor, "shield_attack");
        actor_set_anim(boss->actor, "into_bubble");
        boss->actor->shield = 0;
        boss->movement = Time.currentTime;
        boss->status = Fear;
    }
    if (boss->actor->damaged){
        effect("crab_blood", add2f(boss->actor->position,
            (v2f_t){0.0f, 10.0f}), 0);
            boss->actor->done = true;
    }
}

///////////////////////////////////////////////////////////////////////////////
void health_examination(entity_t *evil)
{
    actor_t *act = evil->actor;

    if (act->damaged)
        if (!actor_set_anim(act, "damage") && !actor_set_sheet(act, "damage")
            && evil->actor->self->id != CREATURE_CRAB_BOSS)
            evil->actor->done = true;
    if (act->health <= 0 && !act->dead && !act->damaged) {
        sfx(SFX_ENEMY_DEATH);
        act->dead = true;
        if (actor_set_sheet(act, "death") && evil->attack_types != Boss)
            act->position.x +=
            (act->self->sheets[act->sheetId]->image->mask.width / 4) *
            ((act->scale.x) < 0 ? 1 : -1);
        actor_set_anim(act, "death");
    }
    if (evil->attack_types == Boss)
        boss_exclusive(evil);
    if (act->dead || act->damaged)
        termination(evil);
}
