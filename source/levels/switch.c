/*
** EPITECH PROJECT, 2024
** B-MUL-200-LYN-2-1-myrpg-mallory.scotton
** File description:
** switch
*/

///////////////////////////////////////////////////////////////////////////////
// Headers
///////////////////////////////////////////////////////////////////////////////
#include "rpg.h"

///////////////////////////////////////////////////////////////////////////////
static void clear_entities(void)
{
    for (int i = 0; i < Entities.count; i++) {
        actor_destroy(Entities.array[i]->actor);
        FREE(Entities.array[i]);
    }
    for (uint_t i = 0; i < ENTITY_REMOVE; i++)
        Entities.toRemove[i] = NULL;
    FREE(Entities.array);
    Entities.count = 0;
    Entities.array = NULL;
}

///////////////////////////////////////////////////////////////////////////////
static void reset_player_behavior(void)
{
    Player.ref->position = V2F1(0.0f);
    Player.velocity = V2F1(0.0f);
    sfMusic_stop(find_music("blingblangblang"));
    DANCE = false;
    DASH = false;
    sfView_setCenter(Win.view, V2F1(0.0f));
    sfRenderWindow_setView(Win.self, Win.view);
}

///////////////////////////////////////////////////////////////////////////////
void switch_level(void)
{
    Engine.fadeStart = Time.currentTime;
    reset_player_behavior();
    clear_entities();
    level_tutorial();
    level_hub();
}
