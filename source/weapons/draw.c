/*
** EPITECH PROJECT, 2024
** my_rpg
** File description:
** draw bullet_sprite
*/
#include "rpg.h"

static void drawing_bullet(bullet_t *bullet)
{
    if (WEAPON_STATS[bullet->weapon_asset].type == WEAPON_TYPE_MELEE)
        return;
    if (bullet->base_visisble) {
        sfRenderWindow_drawSprite(Win.self, bullet->base, NULL);
        return;
    }
    if (bullet->destroyed_visisble) {
        sfRenderWindow_drawSprite(Win.self, bullet->disappear, NULL);
        return;
    }
    if (bullet->impact_player_visisble) {
        sfRenderWindow_drawSprite(Win.self, bullet->impactEnemy, NULL);
        return;
    }
    if (bullet->impactWall)
        sfRenderWindow_drawSprite(Win.self, bullet->impactWall, NULL);
}

void draw_bullet(void)
{
    if (Pool.bulletCount == 0)
        return;
    for (uint_t i = 0; i < Pool.bulletCount; i++)
        drawing_bullet(Pool.bullets[i]);
}
