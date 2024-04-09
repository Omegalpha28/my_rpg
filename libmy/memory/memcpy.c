/*
** EPITECH PROJECT, 2024
** csfml-engine
** File description:
** memcpy
*/

///////////////////////////////////////////////////////////////////////////////
// Headers
///////////////////////////////////////////////////////////////////////////////
#include "my.h"

///////////////////////////////////////////////////////////////////////////////
static void cpy_low_high_chunk(string_t dst, cstring_t src, ulong_t length,
    ulong_t t)
{
    if (t) {
        do {
            *(int *)dst = *(int *)src;
            src += WSIZE;
            dst += WSIZE;
            t--;
        } while (t);
    }
    t = length & WMASK;
    if (t) {
        do {
            *dst = *src;
            dst++;
            src++;
            t--;
        } while (t);
    }
}

///////////////////////////////////////////////////////////////////////////////
static void cpy_low_high(string_t dst, cstring_t src, ulong_t length,
    ulong_t t)
{
    if ((t | (unsigned long int)dst) & WMASK) {
        if ((t ^ (unsigned long int)dst) & WMASK || length < WSIZE)
            t = length;
        else
            t = WSIZE - (t & WMASK);
        length -= t;
        do {
            *dst = *src;
            dst++;
            src++;
            t--;
        } while (t);
    }
    cpy_low_high_chunk(dst, src, length, length / WSIZE);
}

///////////////////////////////////////////////////////////////////////////////
static void cpy_high_low_chunk(string_t dst, cstring_t src, ulong_t length,
    ulong_t t)
{
    if (t) {
        do {
            src -= WSIZE;
            dst -= WSIZE;
            *(int *)dst = *(int *)src;
            t--;
        } while (t);
    }
    t = length & WMASK;
    if (t) {
        do {
            dst--;
            src--;
            *dst = *src;
            t--;
        } while (t);
    }
}

///////////////////////////////////////////////////////////////////////////////
static void cpy_high_low(string_t dst, cstring_t src, ulong_t length,
    ulong_t t)
{
    src += length;
    dst += length;
    if ((t | (unsigned long int)dst) & WMASK) {
        if ((t ^ (unsigned long int)dst) & WMASK || length <= WSIZE)
            t = length;
        else
            t &= WMASK;
        length -= t;
        do {
            dst--;
            src--;
            *dst = *src;
            t--;
        } while (t);
    }
    cpy_high_low_chunk(dst, src, length, length / WSIZE);
}

///////////////////////////////////////////////////////////////////////////////
void *my_memcpy(void *dst0, const void *src0, ulong_t length)
{
    string_t dst = (string_t)dst0;
    cstring_t src = (cstring_t)src0;

    if (length == 0 || dst == src)
        return (dst0);
    if ((ulong_t)dst < (ulong_t)src) {
        cpy_low_high(dst, src, length, (unsigned long int)src);
    } else {
        cpy_high_low(dst, src, length, (unsigned long int)src);
    }
    return (dst0);
}
