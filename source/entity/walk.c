/*
** EPITECH PROJECT, 2024
** my_rpg
** File description:
** walk
*/

///////////////////////////////////////////////////////////////////////////////
// Headers
///////////////////////////////////////////////////////////////////////////////
#include "rpg.h"

///////////////////////////////////////////////////////////////////////////////
void duckwalk(entity_t *duck)
{
    v2f_t move = movetowards2f(duck->actor->position,
        endpoint2f(Player.ref->position, duck->actor->position, duck->radius),
        (duck->speed * Time.deltaTime) / 25);
    v2f_t velocity = subtract2f(move, duck->actor->position);
    float_t curr_rad = distance2f(duck->actor->position, Player.ref->position);

    duck->actor->scale.x = move.x - duck->actor->position.x > 0 ? 1.0f : -1.0f;
    if (curr_rad >= duck->radius){
        duck->actor->position = move;
    } else {
        duck->actor->scale.x *= -1;
        velocity = (v2f_t){0.0f, 0.0f};
    }
    actor_set_anim(duck->actor, velocity.x != 0.0f || velocity.y != 0.0f ?
        "walk" : "idle");
    actor_draw(duck->actor);
}

/*

enemies world 1:

- weird caterpiller (melee)
- mouse (pistol)
- duck (stpid)
-hamster (ak)
- rat (shotgun)
- racoon (also shotgun??)
- croc (lunges at you)
- at one point their is a fox??
- tutorial boss (dont wanna talk about it)
- sir crabington (dont wanna talk about it either)


when it reaches a certain point it stops. and only moves

last position.

in main:

    Entities.array = malloc(sizeof(entity_t *));
    Entities.array[0] = entity_creation(Assets.creatures[creatureDuck],
        (v2f_t){30, 30});

in loop:

    entity_t *duck = Entities.array[0];
    duckwalk(duck);





with this method it speeds up and slows down depending on how close you are.
we dont want that

first off, target. what is their goal.
do they wanna stay in radius, following.

based on a enemy position and player position, a vector map
showing the 8 direction



you take a point you want to go.

and then you take the most direct path to it. a straightline
after that you check you go 45 degrees right. 4 times, where you decrease
the odds by 0.2.
then you increase by 0.2 untill you get a full circle.


their are 2 vector from the same starting point. assuming that the starting
point is 0x0y. the first vector ends at the position 50x45y. with an angle of
45 degrees seperating the two. calculate the end pos of the new vector



0   N   1
    |
1   NE  0.8
    |
2   E   0.6
    |
3   SE  0.4
    |
4   S   0.2
    |
5   SW  0.4
    |
6   W   0.6
    |
7   NW  0.8
    |
0   N   1


*/
