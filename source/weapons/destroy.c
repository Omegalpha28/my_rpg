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

static int entities_impact(bullet_t *bullet, v2f_t pos)
{
    float_t distance_ennemy;
    v2f_t pos_ennemy;
    float_t radius = 20;

    for (uint_t i = 0; i < Entities.count; i++) {
        pos_ennemy = Entities.array[i]->actor->position;
        distance_ennemy = sqrt(pow(pos_ennemy.x - pos.x, 2) +
            pow(pos_ennemy.y - pos.y, 2));
        if (distance_ennemy < radius) {
            animation_bullet_destroyed(bullet);
            return 0;
        }
    }
    return 1;
}

static int player_impact(bullet_t *bullet, v2f_t pos)
{
    float_t distance_ennemy;
    v2f_t pos_player;
    float_t radius = 20;

    for (uint_t i = 0; i < Entities.count; i++) {
        pos_player = Player.ref->position;
        distance_ennemy = sqrt(pow(pos_player.x - pos.x, 2) +
            pow(pos_player.y - pos.y, 2));
        if (distance_ennemy < radius) {
            animation_bullet_destroyed(bullet);
            return 0;
        }
    }
    return 1;
}

int destroy_bullet(bullet_t *bullet)
{
    v2f_t pos = sfSprite_getPosition(bullet->sprite);
    v2f_t c_pos = sfCircleShape_getPosition(bullet->area);
    float_t radius = sfCircleShape_getRadius(bullet->area);
    float_t distance = sqrt(pow(pos.x - c_pos.x, 2) + pow(pos.y - c_pos.y, 2));
    uint_t count = Entities.count;

    if (bullet->sender == 0) {
        DOIF(count > 0, DOIF(entities_impact(bullet, pos) == 0, return 0));
    } else
        DOIF(player_impact(bullet, pos) == 0, return 0);
    DOIF(distance > radius, animation_bullet_destroyed(bullet));
    return 0;
}
