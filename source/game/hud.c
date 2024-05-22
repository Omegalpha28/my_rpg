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

static void draw_health_relay(uint_t i, sfSprite *health)
{
    float scale_x = Win.width / Win.viewWidth;

    sfSprite_setPosition(health, PX_TO_MAPF(V2F(25.0f * scale_x + i *
            20.0f * scale_x, 25.0f)));
    sfRenderWindow_drawSprite(Win.self, health, false);
}

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

void update_hud(void)
{
    draw_health();
}
