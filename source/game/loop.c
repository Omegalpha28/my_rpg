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

    Player.velocity = (v2f_t){0.0f, 0.0f};
    if (UP)
        Player.velocity.y += -SPEED;
    if (DOWN)
        Player.velocity.y += SPEED;
    if (LEFT)
        Player.velocity.x += -SPEED;
    if (RIGHT)
        Player.velocity.x += SPEED;
    Player.velocity = normalize2f(Player.velocity);
    actor_set_anim(act, (Player.velocity.x != 0.0f ||
        Player.velocity.y != 0.0f) ? "walk" : "idle");
    actor_move(act, Player.velocity);
    act->scale.x = act->position.x > cr.x ? -1.0f : 1.0f;
    actor_draw(act);
    draw_debug_line(act, cr);
    draw_debug_safe();
}
