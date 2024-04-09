/*
** EPITECH PROJECT, 2024
** csfml-engine
** File description:
** stowa
*/

///////////////////////////////////////////////////////////////////////////////
// Headers
///////////////////////////////////////////////////////////////////////////////
#include "my.h"

///////////////////////////////////////////////////////////////////////////////
uint my_wcount(cstring str)
{
    uint count = 0;
    bool found = false;

    for (; *str; ++str) {
        if (my_isspace(*str)) {
            found = false;
            continue;
        }
        if (found == false) {
            count++;
            found = true;
        }
    }
    return (count + 1);
}

///////////////////////////////////////////////////////////////////////////////
warray my_stowa(string str)
{
    warray wa;
    int wi = 0;
    string lw = str;

    RETURN(str == NULL, NULL);
    wa = malloc(sizeof(string) * my_wcount(str));
    for (;; ++str) {
        for (; *str && my_isspace(*str); ++str);
        lw = str;
        for (; *str && !my_isspace(*str); ++str);
        if (*str == '\0') {
            DOIF(*lw != '\0', EQ(wa[wi], my_strdup(lw)));
            break;
        }
        *str = '\0';
        wa[wi] = my_strdup(lw);
        wi++;
    }
    wa[wi + BOOL(*lw != '\0')] = NULL;
    return (wa);
}
