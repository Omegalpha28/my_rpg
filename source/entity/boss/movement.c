/*
** EPITECH PROJECT, 2024
** my_rpg
** File description:
** movement
*/

///////////////////////////////////////////////////////////////////////////////
// Headers
///////////////////////////////////////////////////////////////////////////////
#include "rpg.h"


///////////////////////////////////////////////////////////////////////////////
static void next_attack(entity_t *boss)
{
    int random = rand() % 7;

    if (boss->curr_phase == 0)
        boss->status = (random < 4) ? Patrol : Agressive;
    if (boss->curr_phase){
        if (random < 3)
            boss->status = Patrol;
        if (random < 6)
            boss->status = Agressive;
        if (random == 6)
            boss->status = Fear;
    }
    if (boss->status == Fear){
        actor_set_sheet(boss->actor, "shield_attack");
        actor_set_anim(boss->actor, "into_bubble");
        boss->actor->shield_health = Stats[boss->actor->self->id].shield_health;
    }
}

///////////////////////////////////////////////////////////////////////////////
static void idle(entity_t *boss)
{
    if (boss->is_attack)
        return;
    if ((Time.currentTime - boss->movement) >= 7000){
        boss->status = Fear;
        actor_set_sheet(boss->actor, "shield_attack");
        actor_set_anim(boss->actor, "into_bubble");
        boss->actor->shield_health = Stats[boss->actor->self->id].shield_health;
        return;
    }
    if (equal2f(V2F(floorf(boss->wanted_position.x),
        floorf(boss->wanted_position.y)), V2F(floorf(boss->actor->position.x),
        floorf(boss->actor->position.y))))
        get_wanted_position(boss);
    boss->actor->position = movetowards2f(boss->actor->position,
        boss->wanted_position, (boss->speed * Time.deltaTime) / 15);
    if (floorf(boss->actor->position.x) == 0.0f && !boss->attack_started){
        boss->attack_started = true;
        boss->status = Agressive;
    }
    actor_set_sheet(boss->actor, "walk");
}

///////////////////////////////////////////////////////////////////////////////
static void reset_pos(entity_t *crab)
{
    crab->wanted_position = V2F(75.0f, -120.0f);
    if (equal2f(V2F(floorf(crab->wanted_position.x),
        floorf(crab->wanted_position.y)), V2F(floorf(crab->actor->position.x),
        floorf(crab->actor->position.y)))){
        crab->status = Patrol;
        crab->last_action = Time.currentTime;
        crab->movement = Time.currentTime;
    }
    crab->actor->position = movetowards2f(crab->actor->position,
        crab->wanted_position, (crab->speed * Time.deltaTime) / 15);
}

///////////////////////////////////////////////////////////////////////////////
void crab_movement(entity_t *boss)
{
    if (boss->status != Patrol && boss->status != ranger)
        return;
    if (boss->status == ranger)
        reset_pos(boss);
    if (boss->status == Patrol)
        idle(boss);
    return;
}

///////////////////////////////////////////////////////////////////////////////
void boss_movement(entity_t *boss)
{
    if (boss->actor->self->id == CREATURE_CRAB_BOSS)
        crab_movement(boss);
    return;
}
