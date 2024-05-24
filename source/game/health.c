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
void draw_oupsi(void)
{
    sfSprite *oupsi = sfSprite_create();
    sfIntRect rect = {322, 0, 150, 43};

    sfSprite_setTexture(oupsi, Assets.ui[UI_REPORT]->self, false);
    sfSprite_setTextureRect(oupsi, rect);
    sfSprite_setPosition(oupsi, PX_TO_MAPF(V2F(Win.width / 2,
        Win.height / 2)));
    sfSprite_setOrigin(oupsi, V2F(64.5f, 22.5f));
    sfSprite_setScale(oupsi, V2F1(0.75f));
    sfRenderWindow_drawSprite(Win.self, oupsi, false);
    sfSprite_destroy(oupsi);
}

///////////////////////////////////////////////////////////////////////////////
static void death_change(void)
{
    Engine.level = Engine.level < 10 ? 1 : 0;
    Player.ref->health = Assets.axolotl[Player.ref->variantId]->maxHealth;
    Player.ref->shield = Assets.axolotl[Player.ref->variantId]->shields;
    switch_level();
    Player.ref->dead = false;
    Player.ref->draw = true;
    actor_set_anim(Player.ref, "regenerate");
    Player.blocked = true;
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
    if (act->dead && Player.ref->done && Engine.level != 0)
        death_change();
}
