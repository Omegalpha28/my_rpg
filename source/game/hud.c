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
