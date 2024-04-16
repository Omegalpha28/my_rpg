/*
** EPITECH PROJECT, 2024
** my_rpg
** File description:
** draw bullets
*/
#include "rpg.h"

static void drawing_bullets(bullet_t *bullet)
{
    v2f_t direction = {bullet->destination.x - bullet->origin.x,
        bullet->destination.y - bullet->origin.y};
    float length = sqrt(direction.x * direction.x + direction.y * direction.y);
    sfVector2f position = sfSprite_getPosition(bullet->sprite);
    float vitesse = 5;

    direction.x /= length;
    direction.y /= length;
    position.x += direction.x * vitesse;
    position.y += direction.y * vitesse;
    sfSprite_setPosition(bullet->sprite, position);
    sfRenderWindow_drawSprite(Win.self, bullet->sprite, NULL);
}

void draw_bullets(void)
{
    if (Bullet_List.array == NULL)
        return;
    for (uint_t i = 0; i < Bullet_List.count; i++) {
        drawing_bullets(Bullet_List.array[i]);
        destroy_bullet(Bullet_List.array[i]);
    }
}
