/*
** EPITECH PROJECT, 2024
** B-MUL-200-LYN-2-1-myrpg-mallory.scotton
** File description:
** iscoord
*/

///////////////////////////////////////////////////////////////////////////////
// Headers
///////////////////////////////////////////////////////////////////////////////
#include "my.h"

///////////////////////////////////////////////////////////////////////////////
bool_t my_iscoord(string_t str)
{
    warray_t arr = NULL;

    if (my_countchar(str, 'x') != 1)
        return (false);
    arr = my_strsplit(str, 'x');
    if (arr == NULL || my_walen(arr) != 2) {
        my_watroy(arr);
        return (false);
    }
    if (!my_isint(arr[0]) || !my_isint(arr[1])) {
        my_watroy(arr);
        return (false);
    }
    my_watroy(arr);
    return (true);
}
