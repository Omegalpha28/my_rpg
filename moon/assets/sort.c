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

///////////////////////////////////////////////////////////////////////////////
void sort_warray(warray_t arr)
{
    uint_t i = 0;
    string_t tmp = NULL;

    if (arr == NULL || arr[0] == NULL)
        return;
    while (arr[i] && arr[i + 1]) {
        if (strcmp(my_basename(arr[i]), my_basename(arr[i + 1])) > 0) {
            tmp = arr[i];
            arr[i] = arr[i + 1];
            arr[i + 1] = tmp;
            i = 0;
        } else
            i++;
    }
}
