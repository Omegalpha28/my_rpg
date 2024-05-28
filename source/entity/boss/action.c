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
    actor_set_sheet(boss->actor, "idle");
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
        crab->wanted_position = crab->actor->position;
    }
    spinning_movement(crab);
    collision_hit(crab);
    if ((int)crab->bounce >= 9){
        crab->bounce = 0;
        crab->status = Dazed;
        actor_set_sheet(crab->actor, "fizzy");
        actor_set_anim(crab->actor, "spin_transition");
        crab->last_action = Time.currentTime;
        return;
    }
}

static void bubble_expansion(entity_t *crab)
{
    if (crab->actor->shield_health == 120) {
        if (!crab->is_attack && !is_effect("crab_middle_bubble")){
            effect("crab_small_bubble_creation", crab->actor->position, 0);
            crab->is_attack = true;
        }
        if (crab->is_attack && !is_effect("crab_small_bubble_creation") &&
            !is_effect("crab_middle_bubble")){
            effect("crab_middle_bubble", crab->actor->position, 0);
        }
        return;
    }
}

///////////////////////////////////////////////////////////////////////////////
static void bubble_defense(entity_t *crab)
{
    v2f_t save = crab->actor->position;
    v2f_t target_pos;
    int random_x = rand() % 150;
    int random_y = ((rand() % 200) * -1) - 50;

    bubble_expansion(crab);
    if ((Time.currentTime - crab->last_action < (crab->firerate / 4)))
        return;
    random_x = rand() % 2 ? random_x : random_x * -1;
    crab->actor->position = (v2f_t){random_x, random_y};
    target_pos = add2f(crab->actor->position, V2F(0.0f, 50.0f));
    create_bullet(crab->actor, target_pos, crab->weapon);
    crab->actor->position = save;
    crab->last_action = Time.currentTime;
    if (crab->actor->done)
        actor_set_anim(crab->actor, crab->actor->shield_health <= 0 ?
        "outa_shield" : "in_shield");
    return;
}

///////////////////////////////////////////////////////////////////////////////
static void daze_check(entity_t *crab)
{
    if (CMP(crab->actor->self->sheets[crab->actor->sheetId]->name, "fizzy") &&
        crab->actor->done)
        actor_set_anim(crab->actor, "fizzy");
    if (Time.currentTime - crab->last_action < crab->dizzy)
        return;
    if (!CMP(crab->actor->self->sheets[crab->actor->sheetId]->name, "walk"))
        actor_set_sheet(crab->actor, "unspin");
    if (crab->actor->done){
        actor_set_sheet(crab->actor, "walk");
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
