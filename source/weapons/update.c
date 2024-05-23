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
static recti_t get_bullet_box(bullet_t *bullet)
{
    return ((recti_t){
        (int)bullet->position.x - 2,
        (int)bullet->position.y - 2,
        (int)4, (int)4
    });
}

///////////////////////////////////////////////////////////////////////////////
static float get_bullet_angle_from_prop(recti_t pr, bullet_t *blt,
    recti_t bm)
{
    float dx = blt->position.x - (pr.left + pr.width / 2.0f);
    float dy = blt->position.y - (pr.top + pr.height / 2.0f);

    if (fabs(dx) > fabs(dy)) {
        if (dx > 0) {
            blt->position.x = (pr.left + pr.width) + bm.width / 2.0f + 5.0f;
            return (180.0f);
        }
        blt->position.x = pr.left - bm.width / 2.0f - 5.0f;
        return (0.0f);
    } else {
        if (dy > 0) {
            blt->position.y = (pr.top + pr.height) + bm.height / 2.0f + 5.0f;
            return (-90.0f);
        }
        blt->position.y = pr.top - bm.height / 2.0f - 5.0f;
        return (90.0f);
    }
}

///////////////////////////////////////////////////////////////////////////////
static void check_bullet_collision_prop(bullet_t *bullet, prop_t *prop)
{
    bullet_stat_t stat = BULLET_STATS[WEAPON_STATS[bullet->weapon].bulletType];
    recti_t pmask = prop->self->image->mask;
    recti_t prect = {prop->position.x - pmask.width / 2.0f, prop->position.y
        - pmask.height / 2.0f, pmask.width, pmask.height};
    recti_t brect = get_bullet_box(bullet);

    if (!sfIntRect_intersects(&brect, &prect, NULL) || bullet->state !=
        BULLET_STATE_FLYING)
        return;
    sfSprite_setRotation(bullet->sprite, get_bullet_angle_from_prop(prect,
        bullet, bullet->img->mask) - (stat.invert ? 180.0f : 0.0f));
    bullet->img = Assets.bullets[stat.impactWall];
    bullet->state = BULLET_STATE_IMPACT;
    sfx(SFX_BULLET_HIT_NON_DAMAGEABLE);
}

///////////////////////////////////////////////////////////////////////////////
static recti_t reduce_actor_collision_box(recti_t arect)
{
    float amount = 10.0f;

    arect.left += arect.width / amount / 2.0f;
    arect.top += arect.height / amount / 2.0f;
    arect.width -= arect.width / amount;
    arect.width -= arect.height / amount;
    return (arect);
}

///////////////////////////////////////////////////////////////////////////////
static void check_bullet_collision_actor(bullet_t *bullet, actor_t *actor)
{
    bullet_stat_t stat = BULLET_STATS[WEAPON_STATS[bullet->weapon].bulletType];
    recti_t amask = actor->self->sheets[actor->sheetId]->image->mask;
    recti_t arect = {actor->position.x - amask.width / 2.0f, actor->position.y
        - amask.height / 2.0f, amask.width, amask.height};
    recti_t brect = get_bullet_box(bullet);

    arect = reduce_actor_collision_box(arect);
    if (!sfIntRect_intersects(&brect, &arect, NULL) || bullet->state !=
        BULLET_STATE_FLYING || (DASH && Player.ref == actor))
        return;
    bullet->img = Assets.bullets[stat.impactEnemy];
    bullet->state = BULLET_STATE_IMPACT;
    if (actor->dead)
        return;
    actor->invincible = !actor->invincible;
    actor->health -= (Player.ref == actor) ? 1 :
        WEAPON_STATS[bullet->weapon].damage;
    actor->damaged = true;
    sfx(SFX_BULLET_HIT_DAMAGEABLE);
}

///////////////////////////////////////////////////////////////////////////////
static void check_bullet_collision_bullet(bullet_t *bullet, bullet_t *other)
{
    recti_t bullet_box = get_bullet_box(bullet);
    bullet_stat_t stat_bullet =
        BULLET_STATS[WEAPON_STATS[bullet->weapon].bulletType];
    recti_t other_box = get_bullet_box(other);
    bullet_stat_t stat_other =
        BULLET_STATS[WEAPON_STATS[bullet->weapon].bulletType];

    if (!sfIntRect_intersects(&bullet_box, &other_box, NULL)
        || (bullet->state != BULLET_STATE_FLYING ||
        other->state != BULLET_STATE_FLYING))
        return;
    bullet->img = Assets.bullets[stat_bullet.impactEnemy];
    bullet->state = BULLET_STATE_IMPACT;
    other->img = Assets.bullets[stat_other.impactEnemy];
    other->state = BULLET_STATE_IMPACT;
    sfx(SFX_BULLET_HIT_DAMAGEABLE);
}

///////////////////////////////////////////////////////////////////////////////
static void check_bullet_collision(bullet_t *bullet)
{
    for (uint_t i = 0; i < Pool.bulletCount; i++) {
        if (Pool.bullets[i]->sender == bullet->sender)
            continue;
        check_bullet_collision_bullet(bullet, Pool.bullets[i]);
    }
    for (uint_t i = 0; i < Pool.actorCount; i++)
        if (!Pool.actors[i]->dead && Pool.actors[i] != bullet->sender)
            check_bullet_collision_actor(bullet, Pool.actors[i]);
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
    float speed = ((bullet->sender == Player.ref) ? stat.speed :
        stat.speed / 5.0f);
    float distance = clampf(speed * elapsedTime, 0.0f, stat.range);

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
