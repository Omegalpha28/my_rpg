/*
** EPITECH PROJECT, 2024
** csfml-engine
** File description:
** countchar
*/

///////////////////////////////////////////////////////////////////////////////
// Headers
///////////////////////////////////////////////////////////////////////////////
#include "my.h"

///////////////////////////////////////////////////////////////////////////////
/// \brief Count the occurrences of a specified character in a null-terminated
///        string.
///
/// This function iterates through the input null-terminated string 'str' and
/// increments the count for each occurrence of the specified character 'ch'.
/// The final count is returned.
///
/// \param str  Pointer to the null-terminated string.
/// \param ch   The character to count in the string.
///
/// \return     The number of occurrences of the specified character in the
///             string.
///
///////////////////////////////////////////////////////////////////////////////
ulong my_countchar(cstring str, char ch)
{
    ulong count = ch == '\0' ? 1 : 0;

    for (; *str; str++)
        if (*str == ch)
            count++;
    return (count);
}
