/*
** EPITECH PROJECT, 2024
** my_rpg
** File description:
** action
*/

///////////////////////////////////////////////////////////////////////////////
// Headers
///////////////////////////////////////////////////////////////////////////////
#include "rpg.h"


///////////////////////////////////////////////////////////////////////////////
static void mouth_blast(entity_t *boss)
{
    if ((Time.currentTime - boss->last_action) < boss->firerate)
        return;
    boss->is_attack = true;
    actor_set_sheet(boss->actor, boss->curr_phase == 0 ? "bubble_attack" :
        "knife_attack");
    if (boss->firerate == Stats[boss->actor->self->id].firerate){
        firing(boss, boss->ball_count, 15);
        boss->firerate /= 4;
    } else {
        firing(boss, boss->ball_count - 4, 15);
        boss->firerate *= 4;
        boss->is_attack = false;
    }
    boss->last_action = Time.currentTime;
}

///////////////////////////////////////////////////////////////////////////////
static void spin_dash(entity_t *crab)
{
    if (equal2f((v2f_t){fabs(crab->vector.x), fabs(crab->vector.y)},
        V2F(5.0f, 0.0f))){
        crab->vector = (v2f_t){rand() % 2 ? -5.0f : 5.0f, 5.0f};
        crab->actor->position.x += (crab->vector.x * 2);
        crab->wanted_position = crab->actor->position;
        crab->bounce = 0;
    }
    crab->actor->invincible = true;
    spinning_movement(crab);
    dash_collision_hit(crab);
    if (crab->bounce >= 9){
        crab->bounce = 0;
        crab->status = Dazed;
        actor_set_sheet(crab->actor, crab->curr_phase == 0 ? "fizzy" :
            "rage_fizzy");
        actor_set_anim(crab->actor, "spin_transition");
        crab->last_action = Time.currentTime;
        crab->actor->invincible = false;
        return;
    }
}

///////////////////////////////////////////////////////////////////////////////
static void bubble_defense(entity_t *crab)
{
    v2f_t save = crab->actor->position;
    v2f_t target_pos;
    int random_x = rand() % 150 * (rand() % 2 ? 1 : -1);
    int random_y = ((rand() % 200) * -1) - 50;

    domain_expansion(crab);
    if (crab->actor->shield == 13 && crab->curr_phase == 0){
        enrage(crab);
        return;
    }
    if ((Time.currentTime - crab->last_action < (crab->firerate / 4)))
        return;
    crab->actor->position = (v2f_t){random_x, random_y};
    target_pos = add2f(crab->actor->position, V2F(0.0f, 50.0f));
    create_bullet(crab->actor, target_pos, crab->weapon);
    crab->actor->position = save;
    crab->last_action = Time.currentTime;
    if (crab->actor->done)
        actor_set_anim(crab->actor, crab->actor->shield == 13 ?
        "outa_shield" : "in_shield");
}

///////////////////////////////////////////////////////////////////////////////
static void daze_check(entity_t *crab)
{
    if ((CMP(crab->actor->self->sheets[crab->actor->sheetId]->name, "fizzy") ||
        CMP(crab->actor->self->sheets[crab->actor->sheetId]->name,
        "rage_fizzy")) &&
        crab->actor->done)
        actor_set_anim(crab->actor, "fizzy");
    if (Time.currentTime - crab->last_action < crab->dizzy)
        return;
    if (!CMP(crab->actor->self->sheets[crab->actor->sheetId]->name, "walk") ||
        !CMP(crab->actor->self->sheets[crab->actor->sheetId]->name,
            "rage_walk"))
        actor_set_sheet(crab->actor, crab->curr_phase == 0 ?
            "unspin" : "rage_unspin");
    if (crab->actor->done){
        actor_set_sheet(crab->actor, crab->curr_phase == 0 ? "walk" :
            "rage_walk");
        crab->status = ranger;
        crab->vector = (v2f_t){5.0f, 0.0f};
    }
}

///////////////////////////////////////////////////////////////////////////////
static void crab_attack(entity_t *crab)
{
    if (crab->status == Patrol)
        mouth_blast(crab);
    if (crab->status == Dazed)
        daze_check(crab);
    if (crab->status == Agressive)
        spin_dash(crab);
    if (crab->status == Fear)
        bubble_defense(crab);
}

///////////////////////////////////////////////////////////////////////////////
void boss_action(entity_t *boss)
{
    if (!boss->can_attack || !boss->attack_started)
        return;
    if (boss->actor->self->id == CREATURE_CRAB_BOSS)
        crab_attack(boss);
    return;
}
