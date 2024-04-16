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

void duckwalk(entity_t *duck)
{
    duck->actor->position = movetowards2f(duck->actor->position,
        Player.ref->position, (duck->speed * Time.deltaTime) / 25);
    actor_set_anim(duck->actor, "walk");
    actor_draw(duck->actor);
}

/*

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
