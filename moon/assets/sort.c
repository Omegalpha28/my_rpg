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
static void swap_alphabetically(warray_t arr, uint_t j)
{
    string_t tmp = NULL;

    if (strcmp(my_basename(arr[j]), my_basename(arr[j + 1])) <= 0)
        return;
    tmp = arr[j];
    arr[j] = arr[j + 1];
    arr[j] = tmp;
}

///////////////////////////////////////////////////////////////////////////////
void sort_warray(warray_t arr)
{
    ulong_t len = 0;

    if (arr == NULL || arr[0] == NULL)
        return;
    len = my_walen(arr);
    for (uint_t i = 0; i < len - 1; i++)
        for (uint_t j = 0; j < len - 1 - i; j++)
            swap_alphabetically(arr, j);
}
