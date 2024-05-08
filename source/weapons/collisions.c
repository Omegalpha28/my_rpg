/*
** EPITECH PROJECT, 2024
** my_rpg
** File description:
** collisions
*/

///////////////////////////////////////////////////////////////////////////////
// Headers
///////////////////////////////////////////////////////////////////////////////
#include "rpg.h"

static void entity_hit(entity_t *evil)
{
    if (!evil || evil->dead || evil->invincible)
        return;
    evil->health -= 10;
    evil->is_dammaged = true;
    evil->invincible = true;
}

static bool_t animation_bullet_destroyed(bullet_t *bullet, uint_t s)
{
    image_t *img = Assets.bullets[BULLET_STATS[bullet->bullet_asset].base + s];
    v2f_t pos = sfSprite_getPosition(bullet->base);

    if (bullet->base_visisble) {
        sfSprite_setPosition(bullet->disappear, pos);
        bullet->base_visisble = false;
        bullet->destroyed_visisble = true;
        bullet->impact_player_visisble = false;
        bullet->impact_wall_visisble = false;
    }
    img->mask.left = (img->size.x / img->grid.x) * bullet->animation;
    bullet->animation++;
    if ((uint_t)img->mask.left < img->size.x) {
        sfSprite_setTextureRect(bullet->disappear, img->mask);
        return (false);
    } else {
        bullet->destroyed = true;
        return (true);
    }
}

static bool_t animation_bullet_impact_actor(bullet_t *bullet, uint_t s)
{
    image_t *img = Assets.bullets[BULLET_STATS[bullet->bullet_asset].base + s];
    v2f_t pos = sfSprite_getPosition(bullet->base);

    if (bullet->base_visisble) {
        sfSprite_setPosition(bullet->disappear, pos);
        bullet->base_visisble = false;
        bullet->destroyed_visisble = false;
        bullet->impact_player_visisble = true;
        bullet->impact_wall_visisble = false;
    }
    img->mask.left = (img->mask.width) * bullet->animation;
    bullet->animation++;
    if ((uint_t)img->mask.left < img->size.x) {
        sfSprite_setTextureRect(bullet->impactEnemy, img->mask);
        return (false);
    } else {
        bullet->destroyed = true;
        return (true);
    }
}

static bool_t player_impact(bullet_t *bullet)
{
    float_t distance_enemy;
    v2f_t pos_player = Player.ref->position;
    float_t radius = 20;
    v2f_t pos = bullet->position;

    distance_enemy = sqrt(pow(pos_player.x - pos.x, 2) +
        pow(pos_player.y - pos.y, 2));
    if (distance_enemy < radius)
        return (animation_bullet_impact_actor(bullet, 2));
    return (false);
}

static bool_t bullet_impact_actor(bullet_t *bullet)
{
    float_t distance_enemy;
    v2f_t pos_enemy;
    float_t radius;
    v2f_t pos = bullet->position;

    for (uint_t i = 0; i < Entities.count; i++) {
        radius = Entities.array[i]->collision;
        pos_enemy = Entities.array[i]->actor->position;
        distance_enemy = sqrt(pow(pos_enemy.x - pos.x, 2) +
            pow(pos_enemy.y - pos.y, 2));
        if ((distance_enemy < radius) && !Entities.array[i]->dead){
            entity_hit(Entities.array[i]);
            return (animation_bullet_impact_actor(bullet, 2));
        }
    }
    return (false);
}

static bool_t bullet_impact_bullet(bullet_t *bullet)
{
    float_t distance_bullet_enemy;
    v2f_t pos_enemy;
    float_t radius;
    v2f_t pos = bullet->position;

    for (uint_t i = 0; i < Pool.bulletCount; i++) {
        radius = Pool.bullets[i]->radius;
        pos_enemy = Pool.bullets[i]->position;
        distance_bullet_enemy = sqrt(pow(pos_enemy.x - pos.x, 2) +
            pow(pos_enemy.y - pos.y, 2));
        if (distance_bullet_enemy < radius &&
            (bullet->sender != Pool.bullets[i]->sender))
            return (animation_bullet_destroyed(bullet, 3));
    }
    return (false);
}

static bool_t collision_bullet(bullet_t *bullet)
{
    v2f_t pos = sfSprite_getPosition(bullet->base);
    v2f_t c_pos = sfCircleShape_getPosition(bullet->area);
    float_t radius = sfCircleShape_getRadius(bullet->area);
    float_t distance = sqrt(pow(pos.x - c_pos.x, 2) + pow(pos.y - c_pos.y, 2));

    if (WEAPON_STATS[bullet->weapon_asset].type == WEAPON_TYPE_MELEE)
        return (false);
    if (distance > radius)
        return (animation_bullet_destroyed(bullet, 3));
    if (bullet_impact_actor(bullet))
        return (true);
    if (bullet_impact_bullet(bullet))
        return (true);
    if (bullet->sender == 1)
        player_impact(bullet);
    return (false);
}

void bullet_collision(void)
{
    if (Pool.bulletCount == 0)
        return;
    for (uint_t i = 0; i < Pool.bulletCount; i++) {
        if (collision_bullet(Pool.bullets[i]))
            remove_bullet(Pool.bullets[i]);
    }
}
