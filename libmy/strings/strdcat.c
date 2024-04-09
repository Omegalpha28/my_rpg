/*
** EPITECH PROJECT, 2024
** csfml-engine
** File description:
** strdcat
*/

///////////////////////////////////////////////////////////////////////////////
// Headers
///////////////////////////////////////////////////////////////////////////////
#include "my.h"

///////////////////////////////////////////////////////////////////////////////
string my_strdcat(cstring s1, cstring s2, cstring s3)
{
    string str = malloc(sizeof(char) * (my_strlen(s1) + my_strlen(s2) +
        my_strlen(s3) + 1));
    string save = str;

    for (; *s1; s1++) {
        *str = *s1;
        str++;
    }
    for (; *s2; s2++) {
        *str = *s2;
        str++;
    }
    for (; *s3; s3++) {
        *str = *s3;
        str++;
    }
    *str = '\0';
    return (save);
}
