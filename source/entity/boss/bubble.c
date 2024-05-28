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
static void bubble_void(entity_t *crab, char *bubble_creation,
    char *bubble_constant, char *previous_bubble)
{
    v2f_t small_bubble = CMP(bubble_constant, "crab_small_bubble") ?
    (v2f_t){crab->actor->position.x, crab->actor->position.y + 15} :
    (v2f_t){crab->actor->position.x -4, crab->actor->position.y + 7};

    if (previous_bubble != NULL && is_effect(previous_bubble))
            crab->is_attack = false;
    if (!crab->is_attack && !is_effect(bubble_constant)){
        if (previous_bubble != NULL)
            search_and_destroy(previous_bubble);
        effect(bubble_creation, (v2f_t){crab->actor->position.x - 4,
            crab->actor->position.y + 7}, 0);
        crab->is_attack = true;
        crab->actor->invincible = true;
    }
    if (crab->is_attack && !is_effect(bubble_creation) &&
        !is_effect(bubble_constant)){
        effect(bubble_constant, small_bubble, 0);
        crab->actor->invincible = false;
    }
}

///////////////////////////////////////////////////////////////////////////////
static void domain_implosion(entity_t *crab)
{
    search_and_destroy("crab_big_bubble");
    effect("crab_bubble_death", (v2f_t){crab->actor->position.x - 4,
        crab->actor->position.y + 7}, 0);
    crab->actor->shield++;
    crab->status = Patrol;
    crab->movement = Time.currentTime;
    crab->last_action = Time.currentTime;
}

///////////////////////////////////////////////////////////////////////////////
void domain_expansion(entity_t *crab)
{
    if (crab->actor->shield == 12)
        domain_implosion(crab);
    if (crab->actor->shield > 7 && crab->actor->shield < 11)
        bubble_void(crab, "crab_middle_wiggle_transition", "crab_big_bubble",
        "crab_middle_bubble");
    if (crab->actor->shield > 3 && crab->actor->shield < 7)
        bubble_void(crab, "crab_small_wiggle_transition", "crab_middle_bubble",
        "crab_small_bubble");
    if (crab->actor->shield > 0 && crab->actor->shield < 3)
        bubble_void(crab, "crab_small_bubble_creation", "crab_small_bubble",
        NULL);
}
