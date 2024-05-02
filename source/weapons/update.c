/*
** EPITECH PROJECT, 2024
** my_rpg
** File description:
** update
*/

///////////////////////////////////////////////////////////////////////////////
// Headers
///////////////////////////////////////////////////////////////////////////////
#include "rpg.h"

///////////////////////////////////////////////////////////////////////////////
/// \brief Renders a bullet, updating its position based on its origin,
/// destination, and velocity.
///
/// \param              bullet pointer to bullet structure.
///
///////////////////////////////////////////////////////////////////////////////
static void bullet_render(bullet_t *bullet)
{
    v2f_t direction = {bullet->destination.x - bullet->origin.x,
        bullet->destination.y - bullet->origin.y};
    float length = sqrt(direction.x * direction.x + direction.y * direction.y);
    sfVector2f position = sfSprite_getPosition(bullet->sprite);
    float vitesse = 5;

    direction = divide2f(direction, (v2f_t){length, length});
    direction = multiply2f(direction, (v2f_t){vitesse, vitesse});
    position = add2f(position, direction);
    sfSprite_setPosition(bullet->sprite, position);
    sfRenderWindow_drawSprite(Win.self, bullet->sprite, NULL);
}

///////////////////////////////////////////////////////////////////////////////
void bullet_update(void)
{
    if (Pool.bullets == NULL)
        return;
    for (uint_t i = 0; i < Pool.bulletCount; i++) {
        if (Pool.bullets[i]->destroyed)
            continue;
        bullet_render(Pool.bullets[i]);
        bullet_collision(Pool.bullets[i]);
    }
    for (uint_t i = 0; i < Pool.bulletCount; i++) {
        if (!Pool.bullets[i]->destroyed)
            continue;
        remove_bullet(Pool.bullets[i]);
        i--;
    }
}
