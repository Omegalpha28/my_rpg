/*
** EPITECH PROJECT, 2024
** my_rpg
** File description:
** destroy bullets
*/
#include "rpg.h"

static void remove_bullet(bullet_t *bullet)
{
    bullet_t **tmp = NULL;
    uint_t j = 0;

    if (bullet == NULL)
        return;
    tmp = malloc(sizeof(bullet_t *) * (Bullet_List.count - 1));
    for (uint_t i = 0; i < Bullet_List.count; i++) {
        if (Bullet_List.array[i] == bullet)
            continue;
        tmp[j] = Bullet_List.array[i];
        j++;
    }
    Bullet_List.count--;
    FREE(Bullet_List.array);
    Bullet_List.array = tmp;
    FREE(bullet);
}

static void animation_bullet_destroyed(bullet_t *bullet)
{
    recti_t rect = (sfIntRect){bullet->begin + bullet->rect_sprite, 0,
        bullet->rect_sprite, bullet->rect_sprite};

    bullet->begin += bullet->rect_sprite;
    if (bullet->begin < bullet->size_max_x)
        sfSprite_setTextureRect(bullet->sprite, rect);
    else
        remove_bullet(bullet);
}

void destroy_bullet(bullet_t *bullet)
{
    v2f_t pos = sfSprite_getPosition(bullet->sprite);
    v2f_t c_pos = sfCircleShape_getPosition(bullet->area);
    float_t radius = sfCircleShape_getRadius(bullet->area);
    float distance = sqrt(pow(pos.x - c_pos.x, 2) + pow(pos.y - c_pos.y, 2));

    if (distance > radius) {
        animation_bullet_destroyed(bullet);
    }
}
