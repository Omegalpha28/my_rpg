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
    if (equal2f(V2F(floorf(crab->wanted_position.x),
        floorf(crab->wanted_position.y)), V2F(floorf(crab->actor->position.x),
        floorf(crab->actor->position.y))))
        get_wanted_position(crab);
    crab->actor->position = movetowards2f(crab->actor->position,
        crab->wanted_position, (crab->speed * Time.deltaTime) / 2);
    if ((int)crab->bounce >= 9){
        crab->bounce = 0;
        crab->status = Dazed;
        actor_set_anim(crab->actor, "spin_transition");
        crab->last_action = Time.currentTime;
        return;
    }
    actor_set_sheet(crab->actor, "spin");
    actor_set_anim(crab->actor, "spin");
}

static void bubble_expansion(entity_t *crab)
{
    if (crab->shield_health <= 0){
        return;
    }
    if (crab->shield_health <= 40){
        return;
    }
    if (crab->shield_health <= 70){
        return;
    }
    if (crab->shield_health == 100){
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

    if ((Time.currentTime - crab->last_action < (crab->firerate / 4)))
        return;
    random_x = rand() % 2 ? random_x : random_x * -1;
    crab->actor->position = (v2f_t){random_x, random_y};
    target_pos = add2f(crab->actor->position, V2F(0.0f, 50.0f));
    create_bullet(crab->actor, target_pos, crab->weapon);
    crab->actor->position = save;
    crab->last_action = Time.currentTime;
    if (crab->actor->done)
        actor_set_anim(crab->actor, crab->shield_health <= 0 ? "outa_shield"
            : "in_shield");
    return;
}

///////////////////////////////////////////////////////////////////////////////
static void daze_check(entity_t *crab)
{
    if (CMP(crab->actor->self->sheets[crab->actor->sheetId]->name, "spin") &&
        crab->actor->done){
        actor_set_anim(crab->actor, "fizzy");
    }
    if (Time.currentTime - crab->last_action < crab->dizzy)
        return;
    if (!CMP(crab->actor->self->sheets[crab->actor->sheetId]->name, "walk")) {
        actor_set_sheet(crab->actor, "unspin");
        actor_set_anim(crab->actor, "unspin");
    }
    if (crab->actor->done){
        actor_set_sheet(crab->actor, "walk");
        actor_set_anim(crab->actor, "walk");
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
