/*
** EPITECH PROJECT, 2024
** moon-engine
** File description:
** types
*/

#ifndef TYPES_H_
    #define TYPES_H_

///////////////////////////////////////////////////////////////////////////////
// Headers
///////////////////////////////////////////////////////////////////////////////
    #include "dependencies.h"

///////////////////////////////////////////////////////////////////////////////
// Misc
///////////////////////////////////////////////////////////////////////////////
    #undef bool
    #undef false
    #undef true

///////////////////////////////////////////////////////////////////////////////
// Types
///////////////////////////////////////////////////////////////////////////////
typedef unsigned char u8;
typedef unsigned short u16;
typedef unsigned int u32;
typedef unsigned long long u64;
typedef unsigned char uchar;
typedef unsigned int uint;
typedef unsigned long ulong;
typedef unsigned long long ullong;
typedef char *string;
typedef unsigned char *ustring;
typedef const char *cstring;
typedef const unsigned char *custring;
typedef unsigned char byte;
typedef sfVector2f v2f;
typedef sfVector2i v2i;
typedef sfVector2u v2u;
typedef sfVector3f v3f;
typedef sfFloatRect rectf;
typedef sfIntRect recti;
typedef enum {
    false,
    true
} bool;

#endif /* !TYPES_H_ */
