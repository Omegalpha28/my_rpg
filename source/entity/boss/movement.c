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


/*
random:
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
*/
///////////////////////////////////////////////////////////////////////////////
static int next_attack(entity_t *boss)
{
    int random = rand() % 7;

    boss->status = (random < 4) ? Patrol : Agressive;
    return 0;
}

///////////////////////////////////////////////////////////////////////////////
static void idle(entity_t *boss)
{
    if (boss->is_attack)
        return;
    if ((Time.currentTime - boss->movement) >= 6000)
        if (next_attack(boss))
            return;
    if (equal2f(V2F(floorf(boss->wanted_position.x),
        floorf(boss->wanted_position.y)), V2F(floorf(boss->actor->position.x),
        floorf(boss->actor->position.y))))
        get_wanted_position(boss);
    boss->actor->position = movetowards2f(boss->actor->position,
        boss->wanted_position, (boss->speed * Time.deltaTime) / 15);
    if (floorf(boss->actor->position.x) == 0.0f && (!boss->attack_started ||
        boss->status == Agressive)){
        boss->attack_started = true;
        boss->status = Agressive;
        boss->bounce = 0;
    }
    actor_set_sheet(boss->actor, boss->curr_phase == 0 ? "walk" : "rage_walk");
}

///////////////////////////////////////////////////////////////////////////////
static void reset_pos(entity_t *crab)
{
    int rand_x = (((rand() % 50) + 25) * ((rand() % 2) ? -1 : 1));

    if (crab->wanted_position.y != -160.0f)
        crab->wanted_position = V2F(rand_x, -160.0f);
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
void enrage(entity_t *crab)
{
    if (crab->actor->done && CMP(crab->actor->self->
        sheets[crab->actor->sheetId]->name, "shield_attack")){
        actor_set_sheet(crab->actor, "enrage");
        actor_set_anim(crab->actor, "enrage");
        crab->actor->invincible = true;
    }
    if (!crab->actor->done || !CMP(crab->actor->self->
        sheets[crab->actor->sheetId]->name, "enrage"))
        return;
    crab->curr_phase = 1;
    crab->movement = Time.currentTime;
    crab->last_action = Time.currentTime;
    crab->status = Patrol;
    crab->actor->invincible = false;
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
