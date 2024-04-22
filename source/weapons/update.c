/*
** EPITECH PROJECT, 2024
** my_rpg
** File description:
** destroy bullets
*/

///////////////////////////////////////////////////////////////////////////////
// Headers
///////////////////////////////////////////////////////////////////////////////
#include "rpg.h"


///////////////////////////////////////////////////////////////////////////////
/// \brief verifies if bullet has hit a target. if it has then give bullet,
/// hit condition.
///
/// \param bullet       Pointer to bullet structure.
///
/// \return true if hit
///
///////////////////////////////////////////////////////////////////////////////
static bool_t animation_bullet_destroyed(bullet_t *bullet)
{
    recti_t rect = (sfIntRect){bullet->begin + bullet->rect_sprite, 0,
        bullet->rect_sprite, bullet->rect_sprite};

    bullet->begin += bullet->rect_sprite;
    if (bullet->begin + bullet->rect_sprite < bullet->size_max_x) {
        sfSprite_setTextureRect(bullet->sprite, rect);
        return (false);
    } else {
        bullet->hit = true;
        return (true);
    }
}

///////////////////////////////////////////////////////////////////////////////
static void entity_hit(entity_t *evil)
{
    if (!evil || evil->dead || evil->invincible)
        return;
    evil->health -= 10;
    evil->is_dammaged = true;
    evil->invincible = true;
}

///////////////////////////////////////////////////////////////////////////////
/// \brief Verifies bullet collision with entitiy.
///
/// \param bullet       Pointer to bullet structure.
/// \param pos          Bullet position.
///
/// \return true if hit
///
///////////////////////////////////////////////////////////////////////////////
static bool_t entities_impact(bullet_t *bullet, v2f_t pos)
{
    float_t distance_enemy;
    v2f_t pos_enemy;
    float_t radius;

    for (uint_t i = 0; i < Entities.count; i++) {
        radius = Entities.array[i]->collision;
        pos_enemy = Entities.array[i]->actor->position;
        distance_enemy = sqrt(pow(pos_enemy.x - pos.x, 2) +
            pow(pos_enemy.y - pos.y, 2));
        if ((distance_enemy < radius || bullet->begin) &&
            !animation_bullet_destroyed(bullet)){
            entity_hit(Entities.array[i]);
            return (true);
        }
    }
    return (false);
}

///////////////////////////////////////////////////////////////////////////////
/// \brief Verifies bullet collision with player.
///
/// \param bullet       Pointer to bullet structure.
/// \param pos          Bullet position.
///
///////////////////////////////////////////////////////////////////////////////
static bool_t player_impact(bullet_t *bullet, v2f_t pos)
{
    float_t distance_enemy;
    v2f_t pos_player = Player.ref->position;
    float_t radius = 20;

    distance_enemy = sqrt(pow(pos_player.x - pos.x, 2) +
        pow(pos_player.y - pos.y, 2));
    if ((distance_enemy < radius || bullet->begin) &&
        !animation_bullet_destroyed(bullet))
        return (true);
    return (false);
}

///////////////////////////////////////////////////////////////////////////////
/// \brief Verifies bullet collision with entitiy.
///
/// \param bullet       Pointer to bullet structure.
/// \param pos          Bullet position.
///
/// \return true if hit
///
///////////////////////////////////////////////////////////////////////////////
bool_t bullet_collision(bullet_t *bullet)
{
    v2f_t pos = sfSprite_getPosition(bullet->sprite);
    v2f_t c_pos = sfCircleShape_getPosition(bullet->area);
    float_t radius = sfCircleShape_getRadius(bullet->area);
    float_t distance = sqrt(pow(pos.x - c_pos.x, 2) + pow(pos.y - c_pos.y, 2));

    if (distance > radius){
        animation_bullet_destroyed(bullet);
        return (true);
    }
    if ((!bullet->sender && Entities.count > 0 &&
        !entities_impact(bullet, pos)) ||
        (bullet->sender && !player_impact(bullet, pos)))
        return (true);
    return (false);
}
