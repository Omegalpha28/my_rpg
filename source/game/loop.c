/*
** EPITECH PROJECT, 2024
** csfml-engine
** File description:
** loop
*/

///////////////////////////////////////////////////////////////////////////////
// Headers
///////////////////////////////////////////////////////////////////////////////
#include "rpg.h"

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
static void draw_debug_line(actor_t *act, v2f_t cr)
{
    sfVertexArray *va = sfVertexArray_create();
    sfVertex v;

    v.color = sfRed;
    v.position = subtract2f(act->position, (v2f_t){0.0f, -5.0f});
    sfVertexArray_append(va, v);
    v.position = endpoint2f(act->position, cr, dist2f(act->position, cr));
    sfVertexArray_append(va, v);
    sfVertexArray_setPrimitiveType(va, sfLines);
    sfRenderWindow_drawVertexArray(Win.self, va, NULL);
    sfVertexArray_destroy(va);
}

///////////////////////////////////////////////////////////////////////////////
void game_loop(void)
{
    v2f_t cr = PX_TO_MAPF(sfMouse_getPositionRenderWindow(Win.self));
    sfEvent evt;

    while (sfRenderWindow_pollEvent(Win.self, &evt))
        parse_events(evt);
    player_movement();
    update_entity();
    update_collisions();
    cursor_focus();
    bullet_update();
    update_shaking();
    draw();
    if (Engine.debugMode)
        draw_debug_line(Player.ref, cr);
    draw_visor();
}
