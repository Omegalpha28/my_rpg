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
    actor_t *prev = Pool.actors[j];
    actor_t *next = Pool.actors[j + 1];

    if (floorf(prev->position.y +
        prev->self->sheets[prev->sheetId]->image->mask.height / 2.0f) <=
        floorf(next->position.y +
        next->self->sheets[next->sheetId]->image->mask.height / 2.0f))
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

    pos = endpoint2f(pos, cr, 10.0f);
    if (cr.x < pos.x) {
        sfSprite_setScale(wp, V2F(-1.0f, 1.0f));
        angle += 180.0f;
    }
    sfSprite_setTexture(wp, Assets.weapons->self, false);
    sfSprite_setTextureRect(wp, (recti_t){42 * Player.weapon, 0, 42, 24});
    sfSprite_setOrigin(wp, (v2f_t){21.0f, 12.0f});
    sfSprite_setPosition(wp, pos);
    sfSprite_setRotation(wp, angle);
    sfRenderWindow_drawSprite(Win.self, wp, NULL);
    sfSprite_destroy(wp);
}

///////////////////////////////////////////////////////////////////////////////
static void draw_visor(void)
{
    sfSprite *visor = sfSprite_create();
    v2f_t mouse = PX_TO_MAPF(sfMouse_getPositionRenderWindow(Win.self));
    sfBool pressed = sfMouse_isButtonPressed(sfMouseLeft);
    sfIntRect rect = {39, 16, 16, 16};
    float angle = 5.0f * (float)Time.currentTime / 100.0f;

    if (pressed)
        rect = (sfIntRect){16, 18, 14, 14};
    sfSprite_setTexture(visor, Assets.ui[UI_VISOR]->self, false);
    sfSprite_setOrigin(visor, !pressed ? V2F(8.0f, 8.0f) : V2F(7.0f, 7.0f));
    sfSprite_setPosition(visor, mouse);
    sfSprite_setTextureRect(visor, rect);
    sfSprite_setScale(visor, V2F(0.75f, 0.75f));
    sfSprite_setRotation(visor, angle);
    sfRenderWindow_drawSprite(Win.self, visor, false);
    sfSprite_destroy(visor);
    sfRenderWindow_setMouseCursorVisible(Win.self, sfFalse);
}

///////////////////////////////////////////////////////////////////////////////
static void draw_debug_line(v2f_t cr)
{
    sfVertexArray *va = sfVertexArray_create();
    v2f_t origin = endpoint2f(add2f(Player.ref->position, V2F(0.0f, 8.0f)),
        cr, 25.0f);
    sfVertex v;

    v.color = sfRed;
    v.position = origin;
    sfVertexArray_append(va, v);
    v.position = endpoint2f(origin, cr,
        BULLET_STATS[WEAPON_STATS[Player.weapon].bulletType].range);
    sfVertexArray_append(va, v);
    sfVertexArray_setPrimitiveType(va, sfLines);
    sfRenderWindow_drawVertexArray(Win.self, va, NULL);
    sfVertexArray_destroy(va);
}

///////////////////////////////////////////////////////////////////////////////
static void draw_hud(void)
{
    v2f_t cr = PX_TO_MAPF(sfMouse_getPositionRenderWindow(Win.self));

    if (Engine.debugMode && !DASH && !DANCE)
        draw_debug_line(cr);
    draw_visor();
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
    draw_all_bullets();
    draw_visible_props(Editor.fProps, Editor.fCount);
    for (uint_t i = 0; i < Pool.effectCount; i++)
        if (!Pool.effects[i]->self->background)
            effect_draw(Pool.effects[i]);
    draw_hud();
}
