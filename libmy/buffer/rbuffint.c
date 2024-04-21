/*
** EPITECH PROJECT, 2024
** B-MUL-200-LYN-2-1-myrpg-mallory.scotton
** File description:
** rbuffint
*/

///////////////////////////////////////////////////////////////////////////////
// Headers
///////////////////////////////////////////////////////////////////////////////
#include "my.h"

///////////////////////////////////////////////////////////////////////////////
uint_t my_rbuffint(cstring_t buff, uint_t bytes, ulong_t *idx)
{
    uint_t value = 0;

    for (uint_t i = 0; i < bytes; i++) {
        value <<= 8;
        value |= (uchar_t)buff[(*idx)];
        (*idx)++;
    }
    return (value);
}
