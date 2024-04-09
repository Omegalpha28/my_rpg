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
warray my_strsplit(string str, char separator)
{
    string cpy = my_strdup(str);
    char sep[2] = {separator, 0};
    warray wa = malloc(sizeof(string) * (my_countchar(str, separator) + 2));
    string tok = my_strtok(cpy, sep);
    ulong wi = 0;

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
