/*
** EPITECH PROJECT, 2024
** myrpg
** File description:
** hud
*/

///////////////////////////////////////////////////////////////////////////////
// Headers
///////////////////////////////////////////////////////////////////////////////
#include "rpg.h"

///////////////////////////////////////////////////////////////////////////////
static void draw_magazine(weapon_enum_t weap, v2f_t pos, float scale_y,
    bool_t prim)
{
    char nb[3];
    char max[4];

    snprintf(nb, 3, "%u", WEAPON_STATS[weap].ammoPerMag - Player.num_shoot);
    if (Player.max_bullet < WEAPON_STATS[weap].ammoPerMag && !prim)
        snprintf(nb, 3, "%u", Player.max_bullet - Player.num_shoot);
    draw_text_center(nb, pos, 0.30f, sfWhite);
    snprintf(max, 4, "%u", Player.max_bullet);
    if (prim)
        return (draw_text_center("inf", V2F(pos.x, pos.y + 24.0f * scale_y),
            0.30f, sfWhite));
    draw_text_center(max, V2F(pos.x, pos.y + 24.0f * scale_y), 0.30f, sfWhite);
}

///////////////////////////////////////////////////////////////////////////////
void draw_boxes(weapon_enum_t weap, v2f_t pos)
{
    sfSprite *box = sfSprite_create();
    sfIntRect rect = {38, 0, 38, 25};

    sfSprite_setTexture(box, Assets.ui[UI_WEAPON]->self, false);
    sfSprite_setTextureRect(box, rect);
    sfSprite_setPosition(box, PX_TO_MAPF(pos));
    sfSprite_setColor(box, RGBA(255, 255, 255, (Player.weapon == weap ?
        255 : 55)));
    sfRenderWindow_drawSprite(Win.self, box, false);
    if (Player.weapon == weap) {
        rect.left = 0;
        sfSprite_setTextureRect(box, rect);
        sfRenderWindow_drawSprite(Win.self, box, false);
    }
    sfSprite_destroy(box);
}

///////////////////////////////////////////////////////////////////////////////
static void draw_weapons(sfSprite *weap, sfIntRect rect, v2f_t scale,
    v2f_t pos)
{
    sfSprite_setColor(weap, RGBA(255, 255, 255, (Player.inventor[0] !=
        Player.weapon ? 55 : 255)));
    sfSprite_setPosition(weap, PX_TO_MAPF(V2F(pos.x - 42 * scale.x, pos.y)));
    draw_boxes(Player.inventor[0], V2F(Win.width - 84 * scale.x, pos.y));
    sfRenderWindow_drawSprite(Win.self, weap, false);
    draw_magazine(Player.inventor[0], V2F(Win.width - 64.75f * scale.x,
        pos.y - 4 * scale.y), scale.y, true);
    rect.left = Player.inventor[1] * 42;
    sfSprite_setTextureRect(weap, rect);
    sfSprite_setColor(weap, RGBA(255, 255, 255, (Player.inventor[1] !=
        Player.weapon ? 55 : 255)));
    sfSprite_setPosition(weap, PX_TO_MAPF(pos));
    draw_boxes(Player.inventor[1], pos);
    sfRenderWindow_drawSprite(Win.self, weap, false);
    draw_magazine(Player.inventor[1], V2F(Win.width - 22.75f * scale.x,
        Win.height - 34 * scale.y), scale.y, false);
    sfSprite_destroy(weap);
}

///////////////////////////////////////////////////////////////////////////////
void draw_weapon_only(void)
{
    sfSprite *weap = sfSprite_create();
    sfIntRect rect = {Player.inventor[0] * 42, 48, 42, 24};
    v2f_t scale = {Win.width / Win.viewWidth, Win.height / Win.viewHeight};
    v2f_t pos = {Win.width - 42 * scale.x, Win.height - 30 * scale.y};

    sfSprite_setTexture(weap, Assets.weapons->self, false);
    sfSprite_setTextureRect(weap, rect);
    if (Player.inventor[1] != WEAPON_NO)
        return (draw_weapons(weap, rect, scale, pos));
    sfSprite_setPosition(weap, PX_TO_MAPF(pos));
    draw_boxes(Player.inventor[0], pos);
    sfRenderWindow_drawSprite(Win.self, weap, false);
    draw_magazine(Player.inventor[0], V2F(Win.width - 22.75f * scale.x,
        Win.height - 34 * scale.y), scale.y, true);
    sfSprite_destroy(weap);
}

///////////////////////////////////////////////////////////////////////////////
void draw_charge(sfSprite *comp, sfIntRect rect)
{
    float charge = (float)Player.ref->charges;

    if (charge == 0)
        return;
    rect.left = 0;
    rect.top = charge < 5 ? (int)(161 - (charge * (23.0f / 5.0f))) : 138;
    rect.height = charge < 5 ? (int)(charge * (23.0f / 5.0f)) : 23;
    if (charge < 5)
        sfSprite_move(comp, V2F(0.0f, (5.0f - charge) * (23 / 5)));
    sfSprite_setTextureRect(comp, rect);
    sfRenderWindow_drawSprite(Win.self, comp, false);
}

///////////////////////////////////////////////////////////////////////////////
void draw_comp(void)
{
    sfSprite *comp = sfSprite_create();
    sfIntRect rect = {23, 138, 23, 23};
    v2f_t pos = {20.0f, 20.0f};

    sfSprite_setTexture(comp, Assets.ui[UI_ABILITIES]->self, false);
    sfSprite_setTextureRect(comp, rect);
    sfSprite_setPosition(comp, PX_TO_MAPF(pos));
    sfRenderWindow_drawSprite(Win.self, comp, false);
    draw_charge(comp, rect);
    sfSprite_destroy(comp);
}

///////////////////////////////////////////////////////////////////////////////
static void draw_health_relay(uint_t i, sfSprite *health)
{
    float scale_x = Win.width / Win.viewWidth;

    sfSprite_setPosition(health, PX_TO_MAPF(V2F(25.0f * scale_x + i *
            15.0f * scale_x, 30.0f)));
    sfRenderWindow_drawSprite(Win.self, health, false);
}

///////////////////////////////////////////////////////////////////////////////
void draw_health(void)
{
    axolotles_t *axo = Assets.axolotl[Player.ref->variantId];
    sfSprite *health = sfSprite_create();
    sfIntRect rect = {40, 0, 20, 19};
    uint_t i = 0;

    sfSprite_setTexture(health, Assets.ui[UI_HEALTH]->self, false);
    sfSprite_setTextureRect(health, rect);
    for (; (int)i < Player.ref->health; i++)
        draw_health_relay(i, health);
    rect.left = 100;
    sfSprite_setTextureRect(health, rect);
    for (; i < axo->maxHealth; i++)
        draw_health_relay(i, health);
    rect.left = 280;
    sfSprite_setTextureRect(health, rect);
    for (; i - axo->maxHealth < axo->shields; i++)
        draw_health_relay(i, health);
}
