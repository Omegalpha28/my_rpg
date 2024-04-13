/*
** EPITECH PROJECT, 2024
** B-MUL-200-LYN-2-1-myrpg-mallory.scotton
** File description:
** sort
*/

///////////////////////////////////////////////////////////////////////////////
// Headers
///////////////////////////////////////////////////////////////////////////////
#include "moon.h"

///////////////////////////////////////////////////////////////////////////////
static void swap_creatures(uint_t j, bool_t *swapped)
{
    creature_t *tmp = Assets.creatures[j];

    if (Assets.creatures[j]->id < Assets.creatures[j + 1]->id)
        return;
    Assets.creatures[j] = Assets.creatures[j + 1];
    Assets.creatures[j + 1] = tmp;
    *swapped = true;
}

///////////////////////////////////////////////////////////////////////////////
void sort_creatures(void)
{
    bool_t swapped = false;

    for (uint_t i = 0; i < Assets.creatureCount - 1; i++) {
        swapped = false;
        for (uint_t j = 0; j < Assets.creatureCount - i - 1; j++)
            swap_creatures(j, &swapped);
        if (swapped == false)
            break;
    }
}
