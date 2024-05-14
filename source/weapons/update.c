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
static float get_bullet_angle_from_prop(recti_t pr, bullet_t *blt,
    recti_t bm)
{
    float distL = fabsf(blt->position.x - pr.left);
    float distR = fabsf((pr.left + pr.width) - blt->position.x);
    float distT = fabsf(blt->position.y - pr.top);
    float distB = fabsf((pr.top + pr.height) - blt->position.y);
    float minDist = fminf(fminf(distL, distR), fminf(distT, distB));

    if (minDist == distL) {
        blt->position.x = pr.left - bm.width / 2.0f - 5.0f;
        return (0.0f);
    }
    if (minDist == distR) {
        blt->position.x = (pr.left + pr.width) + bm.width / 2.0f + 5.0f;
        return (-180.0f);
    }
    if (minDist == distT) {
        blt->position.y = pr.top - bm.height / 2.0f - 5.0f;
        return (90.0f);
    }
    blt->position.y = (pr.top + pr.height) + bm.height / 2.0f + 5.0f;
    return (-90.0f);
}

///////////////////////////////////////////////////////////////////////////////
static void check_bullet_collision_prop(bullet_t *bullet, prop_t *prop)
{
    bullet_stat_t stat = BULLET_STATS[WEAPON_STATS[bullet->weapon].bulletType];
    recti_t pmask = prop->self->image->mask;
    recti_t prect = {prop->position.x - pmask.width / 2.0f, prop->position.y
        - pmask.height / 2.0f, pmask.width, pmask.height};
    recti_t bmask = bullet->img->mask;
    recti_t brect = {bullet->position.x - bmask.width / 2.0f,
        bullet->position.y - bmask.height / 2.0f, bmask.width, bmask.height};

    if (!sfIntRect_intersects(&brect, &prect, NULL) || bullet->state !=
        BULLET_STATE_FLYING)
        return;
    sfSprite_setRotation(bullet->sprite, get_bullet_angle_from_prop(prect,
        bullet, bmask) - (stat.invert ? 180.0f : 0.0f));
    bullet->img = Assets.bullets[stat.impactWall];
    bullet->state = BULLET_STATE_IMPACT;
}

///////////////////////////////////////////////////////////////////////////////
static void check_bullet_collision_entity(bullet_t *bullet, entity_t *ent)
{
    bullet_stat_t stat = BULLET_STATS[WEAPON_STATS[bullet->weapon].bulletType];
    v2f_t pos = ent->actor->position;
    float dist = sqrt(pow(pos.x - bullet->position.x, 2) +
        pow(pos.y - bullet->position.y, 2));

    if ((dist < ent->collision) && !ent->dead &&
        bullet->state == BULLET_STATE_FLYING) {
        bullet->img = Assets.bullets[stat.impactEnemy];
        bullet->state = BULLET_STATE_IMPACT;
        if (ent->invincible)
            return;
        ent->health -= WEAPON_STATS[bullet->weapon].damage;
        ent->is_dammaged = true;
        ent->invincible = true;
    }
}

///////////////////////////////////////////////////////////////////////////////
static void check_bullet_collision_bullet(bullet_t *bullet, bullet_t *other)
{
    bullet = bullet;
    other = other;
}

///////////////////////////////////////////////////////////////////////////////
static void check_bullet_collision(bullet_t *bullet)
{
    for (uint_t i = 0; i < Pool.bulletCount; i++) {
        if (Pool.bullets[i]->sender == bullet->sender)
            continue;
        check_bullet_collision_bullet(bullet, Pool.bullets[i]);
    }
    for (int i = 0; i < Entities.count; i++)
        check_bullet_collision_entity(bullet, Entities.array[i]);
    for (uint_t i = 0; i < Pool.propCount; i++) {
        if (!Pool.props[i]->collision || CMP(Pool.props[i]->self->name,
            "water"))
            continue;
        check_bullet_collision_prop(bullet, Pool.props[i]);
    }
}

///////////////////////////////////////////////////////////////////////////////
static void update_bullet(bullet_t *bullet)
{
    bullet_stat_t stat = BULLET_STATS[WEAPON_STATS[bullet->weapon].bulletType];
    float elapsedTime = (Time.currentTime - bullet->startAt) / 15.0f;
    float distance = clampf(stat.speed * elapsedTime, 0.0f, stat.range);

    check_bullet_collision(bullet);
    if (bullet->state != BULLET_STATE_FLYING)
        return;
    bullet->position = endpoint2f(bullet->origin, bullet->destination,
        distance);
    if (distance == stat.range) {
        bullet->img = Assets.bullets[stat.disappear];
        bullet->state = BULLET_STATE_IMPACT;
    }
}

///////////////////////////////////////////////////////////////////////////////
void update_all_bullets(void)
{
    for (uint_t i = 0; i < Pool.bulletCount; i++) {
        update_bullet(Pool.bullets[i]);
        if (Pool.bullets[i]->state != BULLET_STATE_DESTROYED)
            continue;
        destroy_bullet(Pool.bullets[i]);
        i--;
    }
}
