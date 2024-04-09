/*
** EPITECH PROJECT, 2024
** csfml-engine
** File description:
** csfml-engine
*/

///////////////////////////////////////////////////////////////////////////////
// Headers
///////////////////////////////////////////////////////////////////////////////
#include "my.h"

///////////////////////////////////////////////////////////////////////////////
static void filling_remaining_word(ustring dst, int c0, ulong length)
{
    ulong t = length & WMASK;

    if (t) {
        do {
            *dst = c0;
            dst++;
            t--;
        } while (t);
    }
}

///////////////////////////////////////////////////////////////////////////////
static void filling_word(ustring dst, int c0, uint c, ulong length)
{
    ulong t = (unsigned long int)dst & WMASK;

    if (t != 0) {
        t = WSIZE - t;
        length -= t;
        do {
            *dst = c0;
            dst++;
            t--;
        } while (t);
    }
    t = length / WSIZE;
    do {
        *(uint *)dst = c;
        dst += WSIZE;
        t--;
    } while (t);
    filling_remaining_word(dst, c0, length);
}

///////////////////////////////////////////////////////////////////////////////
void *my_memset(void *dst0, int c0, ulong length)
{
    uint c = (uchar)c0;
    ustring dst = (ustring)dst0;

    if (length < 3 * WSIZE) {
        while (length != 0) {
            *dst = c0;
            dst++;
            --length;
        }
        return (dst0);
    }
    if (c != 0) {
        c = (c << 8) | c;
        if (UINT_MAX > 0xffff)
            c = (c << 16) | c;
    }
    filling_word(dst, c0, c, length);
    return (dst0);
}
