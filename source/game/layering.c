/*
** EPITECH PROJECT, 2024
** B-MUL-200-LYN-2-1-myrpg-mallory.scotton
** File description:
** layering
*/

///////////////////////////////////////////////////////////////////////////////
// Headers
///////////////////////////////////////////////////////////////////////////////
#include "rpg.h"

///////////////////////////////////////////////////////////////////////////////
static void swap_actors(uint_t j, bool_t *swapped)
{
    actor_t *tmp = Pool.actors[j];

    if (floorf(Pool.actors[j]->position.y) <=
        floorf(Pool.actors[j + 1]->position.y))
        return;
    Pool.actors[j] = Pool.actors[j + 1];
    Pool.actors[j + 1] = tmp;
    *swapped = true;
}

///////////////////////////////////////////////////////////////////////////////
void sort_actors_pool(void)
{
    bool_t swapped = false;

    if (Pool.actorCount == 0)
        return;
    for (uint_t i = 0; i < Pool.actorCount - 1; i++) {
        swapped = false;
        for (uint_t j = 0; j < Pool.actorCount - i - 1; j++)
            swap_actors(j, &swapped);
        if (swapped == false)
            break;
    }
}

///////////////////////////////////////////////////////////////////////////////
static bool_t draw_weapon_under(void)
{
    v2f_t cr = PX_TO_MAP(sfMouse_getPositionRenderWindow(Win.self));
    v2f_t pos = add2f(Player.ref->position, V2F(0.0f, 8.0f));
    float deltaX = cr.x - pos.x;
    float deltaY = cr.y - pos.y;
    float angle = atan2f(deltaY, deltaX) * (180.0f / M_PI);

    return (angle >= -152.5f && angle <= -27.5f);
}

///////////////////////////////////////////////////////////////////////////////
static void draw_weapon(void)
{
    v2f_t cr = PX_TO_MAP(sfMouse_getPositionRenderWindow(Win.self));
    sfSprite *wp = sfSprite_create();
    v2f_t pos = add2f(Player.ref->position, V2F(0.0f, 8.0f));
    float deltaX = cr.x - Player.ref->position.x;
    float deltaY = cr.y - Player.ref->position.y;
    float angle = atan2f(deltaY, deltaX) * (180.0f / M_PI);

    pos = endpoint2f(pos, cr, 5.0f);
    if (cr.x < pos.x) {
        sfSprite_setScale(wp, V2F(-1.0f, 1.0f));
        angle += 180.0f;
    }
    sfSprite_setTexture(wp, Assets.weapons->self, false);
    sfSprite_setTextureRect(wp, (recti_t){42 * Player.weapon, 0, 42, 24});
    sfSprite_setOrigin(wp, (v2f_t){15.0f, 12.0f});
    sfSprite_setPosition(wp, pos);
    sfSprite_setRotation(wp, angle);
    sfRenderWindow_drawSprite(Win.self, wp, NULL);
    sfSprite_destroy(wp);
}

///////////////////////////////////////////////////////////////////////////////
void draw(void)
{
    bool_t under = draw_weapon_under();

    draw_visible_props(Editor.bProps, Editor.bCount);
    for (uint_t i = 0; i < Pool.effectCount; i++)
        if (Pool.effects[i]->self->background)
            effect_draw(Pool.effects[i]);
    sort_actors_pool();
    for (uint_t i = 0; i < Pool.actorCount; i++) {
        if (Player.ref == Pool.actors[i] && under && !(DANCE || DASH))
            draw_weapon();
        actor_draw(Pool.actors[i]);
        if (Player.ref == Pool.actors[i] && !under && !(DANCE || DASH))
            draw_weapon();
    }
    draw_visible_props(Editor.fProps, Editor.fCount);
    for (uint_t i = 0; i < Pool.effectCount; i++)
        if (!Pool.effects[i]->self->background)
            effect_draw(Pool.effects[i]);
    bullet_update();
}
