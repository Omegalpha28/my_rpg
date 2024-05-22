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
static void draw_fade(void)
{
    sfRectangleShape *fade = NULL;
    float elapsed = (Time.currentTime - Engine.fadeStart) / 1e3f;
    float alpha = 0.0f;
    float duration = 0.75f;

    if (elapsed > duration)
        return;
    alpha = 1.0f - ((elapsed - (duration / 2.0f)) / (duration / 2.0f));
    alpha = clampf(alpha, 0.0f, 1.0f);
    fade = sfRectangleShape_create();
    sfRectangleShape_setSize(fade, V2F(Win.viewWidth, Win.viewHeight));
    sfRectangleShape_setPosition(fade, PX_TO_MAPF(V2F1(0.0f)));
    sfRectangleShape_setFillColor(fade, RGBA(0, 0, 0, (255 * alpha)));
    sfRenderWindow_drawRectangleShape(Win.self, fade, NULL);
    sfRectangleShape_destroy(fade);
}

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

static void death_change(void)
{
    Engine.level = Engine.level < 10 ? 1 : 0;
    Player.ref->health = Assets.axolotl[Player.ref->variantId]->maxHealth;
    Player.ref->shield = Assets.axolotl[Player.ref->variantId]->shields;
    draw_fade();
    switch_level();
    Player.ref->dead = false;
    Player.ref->draw = true;
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
