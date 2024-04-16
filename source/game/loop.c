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
static void draw_debug_line(actor_t *act, v2f_t cr)
{
    sfVertexArray *va = sfVertexArray_create();
    sfVertex v;

    v.color = sfRed;
    v.position = subtract2f(act->position, (v2f_t){0.0f, -5.0f});
    sfVertexArray_append(va, v);
    v.position = endpoint2f(act->position, cr, 50.0f);
    sfVertexArray_append(va, v);
    sfVertexArray_setPrimitiveType(va, sfLines);
    sfRenderWindow_drawVertexArray(Win.self, va, NULL);
    sfVertexArray_destroy(va);
}

///////////////////////////////////////////////////////////////////////////////
void game_loop(void)
{
    actor_t *act = Player.ref;
    v2f_t cr = PX_TO_MAPF(sfMouse_getPositionRenderWindow(Win.self));
    sfEvent evt;

    while (sfRenderWindow_pollEvent(Win.self, &evt))
            parse_events(evt);
    player_movement();
    actor_draw(act);
    draw_debug_line(act, cr);
    draw_debug_safe();
}
