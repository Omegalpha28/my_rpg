/*
** EPITECH PROJECT, 2024
** my_rpg
** File description:
** update
*/
#include "rpg.h"

void bullet_render(bullet_t *bullet)
{
    v2f_t direction;
    float length;
    sfVector2f position;
    float vitesse = bullet->speed;
    sfSprite *sprite;

    if (bullet->base_visisble)
        sprite = bullet->base;
    else
        return;
    direction = (v2f_t){bullet->destination.x - bullet->origin.x,
        bullet->destination.y - bullet->origin.y};
    length = sqrt(direction.x * direction.x + direction.y * direction.y);
    position = sfSprite_getPosition(sprite);
    direction = divide2f(direction, (v2f_t){length, length});
    direction = multiply2f(direction, (v2f_t){vitesse, vitesse});
    position = add2f(position, direction);
    sfSprite_setPosition(sprite, position);
}

void bullet_update(void)
{
    if (Pool.bullets == NULL )
        return;
    bullet_collision();
    for (uint_t i = 0; i < Pool.bulletCount; i++) {
        if (WEAPON_STATS[Pool.bullets[i]->weapon_asset].type ==
            WEAPON_TYPE_MELEE || Pool.bullets[i]->destroyed == true) {
            continue;
            }
        bullet_render(Pool.bullets[i]);
    }
    for (uint_t i = 0; i < Pool.bulletCount; i++) {
        if (!Pool.bullets[i]->destroyed)
            continue;
        remove_bullet(Pool.bullets[i]);
        i--;
    }
}
