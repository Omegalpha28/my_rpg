/*
** EPITECH PROJECT, 2024
** csfml-engine
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
typedef unsigned char u8_t;
typedef unsigned short u16_t;
typedef unsigned int u32_t;
typedef unsigned long long u64_t;
typedef unsigned char uchar_t;
typedef unsigned int uint_t;
typedef unsigned long ulong_t;
typedef unsigned long long ullong_t;
typedef char *string_t;
typedef unsigned char *ustring_t;
typedef const char *cstring_t;
typedef const unsigned char *custring_t;
typedef unsigned char byte_t;
typedef sfVector2f v2f_t;
typedef sfVector2i v2i_t;
typedef sfVector2u v2u_t;
typedef sfVector3f v3f_t;
typedef sfFloatRect rectf_t;
typedef sfIntRect recti_t;
typedef string_t *warray_t;
typedef cstring_t *cwarray_t;
typedef custring_t *cuwarray_t;
typedef enum {
    false,
    true
} bool_t;

#endif /* !TYPES_H_ */
