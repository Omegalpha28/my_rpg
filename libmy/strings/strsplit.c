/*
** EPITECH PROJECT, 2024
** csfml-engine
** File description:
** strsplit
*/

///////////////////////////////////////////////////////////////////////////////
// Headers
///////////////////////////////////////////////////////////////////////////////
#include "my.h"

///////////////////////////////////////////////////////////////////////////////
warray_t my_strsplit(string_t str, char separator)
{
    string_t cpy = my_strdup(str);
    char sep[2] = {separator, 0};
    warray_t wa = malloc(sizeof(string_t) * (my_countchar(str, separator) +
        2));
    string_t tok = my_strtok(cpy, sep);
    ulong_t wi = 0;

    if (tok == NULL) {
        FREE(wa);
        FREE(cpy);
        return (NULL);
    }
    while (tok != NULL) {
        wa[wi] = my_strdup(tok);
        wi++;
        tok = my_strtok(NULL, sep);
    }
    wa[wi] = 0;
    FREE(cpy);
    return (wa);
}
