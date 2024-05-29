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

void draw_hp_bar(entity_t *evil)
{
    sfRectangleShape *hp = sfRectangleShape_create();
    sfRectangleShape *square = sfRectangleShape_create();
    v2f_t pos = {Win.width / 2, Win.height / 18};

    draw_text_center("Dartacrab", V2F(pos.x, 10.0f), 0.45f, sfWhite);
    sfRectangleShape_setPosition(square, PX_TO_MAPF(pos));
    sfRectangleShape_setPosition(hp, PX_TO_MAPF(pos));
    sfRectangleShape_setOrigin(square, V2F(90.0f, 5.0f));
    sfRectangleShape_setOrigin(hp, V2F(90.0f, 5.0f));
    sfRectangleShape_setSize(square, V2F(180.0f, 10.0f));
    sfRectangleShape_setSize(hp, V2F((float)(evil->actor->health) /
        (float)(Stats[evil->actor->self->id].health) * 180.0f, 10.0f));
    sfRectangleShape_setOutlineColor(square, sfWhite);
    sfRectangleShape_setFillColor(square, RGB(87, 39, 36));
    sfRectangleShape_setFillColor(hp, RGB(248, 80, 84));
    sfRectangleShape_setOutlineThickness(square, 1.0f);
    sfRenderWindow_drawRectangleShape(Win.self, square, false);
    sfRenderWindow_drawRectangleShape(Win.self, hp, false);
    sfRectangleShape_destroy(square);
    sfRectangleShape_destroy(hp);
}

///////////////////////////////////////////////////////////////////////////////
static void termination(void)
{
    if (!Player.ref->done || !Player.ref->draw)
        return;
    if (Player.ref->damaged){
        Player.ref->damaged = !Player.ref->damaged;
        Player.ref->invincible = false;
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
    Player.weapon = Player.inventor[0];
    Player.inventor[1] = WEAPON_NO;
    Player.max_bullet = 0;
    Player.mag[1] = 0;
    Player.mag[0] = WEAPON_STATS[Player.weapon].ammoPerMag;
    Player.shaking = false;
    Player.ref->charges = 0;
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
