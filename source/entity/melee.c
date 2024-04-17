/*
** EPITECH PROJECT, 2024
** my_rpg
** File description:
** melee
*/

///////////////////////////////////////////////////////////////////////////////
// Headers
///////////////////////////////////////////////////////////////////////////////
#include "rpg.h"

///////////////////////////////////////////////////////////////////////////////
void caterkillah_ai(entity_t *evil)
{
    v2f_t move = movetowards2f(evil->actor->position,
        endpoint2f(Player.ref->position, evil->actor->position,
            evil->radius / 4), (evil->speed * Time.deltaTime) / 25);
    float_t curr_rad = distance2f(evil->actor->position, Player.ref->position);

    evil->actor->scale.x = move.x - evil->actor->position.x > 0 ? 1.0f : -1.0f;
    if (curr_rad >= (evil->radius / 4))
        evil->actor->position = move;
    else
        evil->actor->scale.x *= -1;
    actor_set_anim(evil->actor, curr_rad >= evil->radius ?
        "walk" : "angrywalk");
    actor_draw(evil->actor);
}

/*
its more of a case of idle to attack. once it "attacks" it goes into angrywalk
where it will "chase" the player (chase in parenthesis cause they can just
straight up miss.)


*/
