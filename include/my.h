/*
** EPITECH PROJECT, 2024
** csfml-engine
** File description:
** libmy
*/

#ifndef LIBMY_H_
    #define LIBMY_H_

///////////////////////////////////////////////////////////////////////////////
// Headers
///////////////////////////////////////////////////////////////////////////////
    #include "moon/dependencies.h"
    #include "moon/macros.h"
    #include "moon/types.h"

    #define WSIZE sizeof(int)
    #define WMASK (WSIZE - 1)
    #define ALIGN (sizeof(ulong_t))
    #define ONES ((ulong_t)-1 / UCHAR_MAX)
    #define HIGHS (ONES * (UCHAR_MAX / 2 + 1))
    #define HASZERO(x) (((x) - ONES) & ~(x) & HIGHS)

    #define MAX_EXTENSION_LENGTH 32

#ifndef ARG_MAX
    #define ARG_MAX 128 * 1024
#endif

///////////////////////////////////////////////////////////////////////////////
/// \brief Maximum character read by buffer
///
///////////////////////////////////////////////////////////////////////////////
    #define MAX_READ_BUFFER 32

///////////////////////////////////////////////////////////////////////////////
/// \brief Check if a character is an alphanumeric character [a-Z0-9].
///
/// \param ch           The character to check.
///
/// \return True if the character is alphanumeric, false otherwise.
///
///////////////////////////////////////////////////////////////////////////////
bool_t my_isalnum(int ch);

///////////////////////////////////////////////////////////////////////////////
/// \brief Check if a character is an alphabetic character [a-Z].
///
/// \param ch           The character to check.
///
/// \return True if the character is an alphabetic character, false otherwise.
///
///////////////////////////////////////////////////////////////////////////////
bool_t my_isalpha(int ch);

///////////////////////////////////////////////////////////////////////////////
/// \brief Check if a character is a control character.
///
/// \param ch           The character to check.
///
/// \return True if the character is a control character, false otherwise.
///
///////////////////////////////////////////////////////////////////////////////
bool_t my_iscntrl(int ch);

///////////////////////////////////////////////////////////////////////////////
/// \brief Check if a character is a digit [0-9].
///
/// \param ch           The character to check.
///
/// \return True if the character is a digit, false otherwise.
///
///////////////////////////////////////////////////////////////////////////////
bool_t my_isdigit(int ch);

///////////////////////////////////////////////////////////////////////////////
/// \brief Check if a character is a graphical character (printable and not a
///        space).
///
/// \param ch           The character to check.
///
/// \return True if the character is a graphical character, false otherwise.
///
///////////////////////////////////////////////////////////////////////////////
bool_t my_isgraph(int ch);

///////////////////////////////////////////////////////////////////////////////
/// \brief Check if a character is a lowercase letter.
///
/// \param ch           The character to check.
///
/// \return True if the character is a lowercase letter, false otherwise.
///
///////////////////////////////////////////////////////////////////////////////
bool_t my_islower(int ch);

///////////////////////////////////////////////////////////////////////////////
/// \brief Check if a character is a printable character (ASCII space to
///        tilde).
///
/// \param ch           The character to check.
///
/// \return True if the character is a printable character, false otherwise.
///
///////////////////////////////////////////////////////////////////////////////
bool_t my_isprint(int ch);

///////////////////////////////////////////////////////////////////////////////
/// \brief Check if a character is a punctuation character.
///
/// \param ch           The character to check.
///
/// \return True if the character is a punctuation character, false otherwise.
///
///////////////////////////////////////////////////////////////////////////////
bool_t my_ispunct(int ch);

///////////////////////////////////////////////////////////////////////////////
/// \brief Check if a character is a whitespace character (tab, newline,
///        vertical tab, form feed, carriage return, or space).
///
/// \param ch           The character to check.
///
/// \return True if the character is a whitespace character, false otherwise.
///
///////////////////////////////////////////////////////////////////////////////
bool_t my_isspace(int ch);

///////////////////////////////////////////////////////////////////////////////
/// \brief Check if a character is a uppercase letter.
///
/// \param ch           The character to check.
///
/// \return True if the character is a uppercase letter, false otherwise.
///
///////////////////////////////////////////////////////////////////////////////
bool_t my_isupper(int ch);

///////////////////////////////////////////////////////////////////////////////
/// \brief Check if a character is a hexadecimal digit.
///
/// \param ch           The character to check.
///
/// \return True if the character is a hexadecimal digit, false otherwise.
///
///////////////////////////////////////////////////////////////////////////////
bool_t my_isxdigit(int ch);

///////////////////////////////////////////////////////////////////////////////
/// \brief Convert an uppercase letter to its lowercase equivalent.
///
/// \param ch           The character to convert.
///
/// \return The lowercase equivalent if the character is an uppercase letter,
/// unchanged otherwise.
///
///////////////////////////////////////////////////////////////////////////////
int my_tolower(int ch);

///////////////////////////////////////////////////////////////////////////////
/// \brief Convert an uppercase letter to its uppercase equivalent.
///
/// \param ch           The character to convert.
///
/// \return The uppercase equivalent if the character is an lowercase letter,
/// unchanged otherwise.
///
///////////////////////////////////////////////////////////////////////////////
int my_toupper(int ch);

///////////////////////////////////////////////////////////////////////////////
/// \brief Calculate the length of a null-terminated string.
///
/// \param str          Pointer to the null-terminated string.
///
/// \return The length of the string (excluding the null terminator)
///
///////////////////////////////////////////////////////////////////////////////
ulong_t my_strlen(cstring_t str);

///////////////////////////////////////////////////////////////////////////////
/// \brief Convert a string to a word array
///
/// \param str          Pointer to the null-derminated string
///
/// \return Array of words
///
///////////////////////////////////////////////////////////////////////////////
warray_t my_stowa(string_t str);

///////////////////////////////////////////////////////////////////////////////
/// \brief Duplicate a string to n
///
/// \param str          The input string to duplicate
/// \param n            The end of the string
///
/// \return A pointer to the duplicated string, or NULL if memory allocation
/// fails
///
///////////////////////////////////////////////////////////////////////////////
string_t my_strndup(cstring_t str, ulong_t n);

///////////////////////////////////////////////////////////////////////////////
/// \brief Calculate the length of a null-terminated array of strings
///
/// \param wa           Pointer to the null-terminated array of strings
///
/// \return The length of the array (number of strings)
///
///////////////////////////////////////////////////////////////////////////////
ulong_t my_walen(warray_t wa);

///////////////////////////////////////////////////////////////////////////////
/// \brief Deallocate memory for a null-terminated array of strings
///
/// \param wa  Pointer to the null-terminated array of strings
///
///////////////////////////////////////////////////////////////////////////////
void my_watroy(warray_t wa);

///////////////////////////////////////////////////////////////////////////////
/// \brief Create a deep copy of an array of mutable strings.
///
/// \param wa           The array of mutable strings to be copied
///
/// \return A deep copy of the input array, or NULL on allocation failure
///
///////////////////////////////////////////////////////////////////////////////
warray_t my_wacpy(warray_t wa);

///////////////////////////////////////////////////////////////////////////////
/// \brief Duplicate a string
///
/// \param str          The input string to duplicate
///
/// \return A pointer to the duplicated string, or NULL if memory allocation
/// fails
///
///////////////////////////////////////////////////////////////////////////////
string_t my_strdup(cstring_t str);

///////////////////////////////////////////////////////////////////////////////
/// \brief Compare two strings up to a specified number of characters.
///
/// \param s1           The first string to compare.
/// \param s2           The second string to compare.
/// \param n            The maximum number of characters to compare.
///
/// \return An integer less than, equal to, or greater than 0 if the first n
/// characters of s1 are found, respectively, to be less than, to match, or be
/// greater than the first n characters of s2.
///
///////////////////////////////////////////////////////////////////////////////
int my_strncmp(cstring_t s1, cstring_t s2, size_t n);

///////////////////////////////////////////////////////////////////////////////
/// \brief Copy at most n characters from the source string to the destination
/// string.
///
/// \param dest         The destination string where characters will be copied.
/// \param src          The source string from which characters will be copied.
/// \param n            The maximum number of characters to copy from the
///                     source string.
///
/// \return The modified destination string.
///
///////////////////////////////////////////////////////////////////////////////
string_t my_strncpy(string_t dest, cstring_t src, uint_t n);

///////////////////////////////////////////////////////////////////////////////
/// \brief Concatenate up to 'n' characters from a null-terminated source
///        string to the end of a destination string.
///
/// \param dest         Null-terminated destination string.
/// \param src          Null-terminated source string.
/// \param n            Maximum number of characters to concatenate.
///
/// \return Pointer to the destination string after concatenation.
///
///////////////////////////////////////////////////////////////////////////////
string_t my_strncat(string_t dest, cstring_t src, uint_t n);

///////////////////////////////////////////////////////////////////////////////
/// \brief Compare two strings.
///
/// \param s1           The first string to compare.
/// \param s2           The second string to compare.
///
/// \return An integer less than, equal to, or greater than zero if s1 is
/// found, respectively, to be less than, to match, or be greater than s2.
///
///////////////////////////////////////////////////////////////////////////////
int my_strcmp(cstring_t s1, cstring_t s2);

///////////////////////////////////////////////////////////////////////////////
/// \brief Calculate the length of a substring in a null-terminated string up
///        to a specified limiter character.
///
/// \param str          Pointer to the null-terminated string.
/// \param limiter      The character acting as the limiter.
///
/// \return The length of the substring up to the limiter (excluding
/// the limiter itself).
///
///////////////////////////////////////////////////////////////////////////////
ulong_t my_strwlen(cstring_t str, char limiter);

///////////////////////////////////////////////////////////////////////////////
/// \brief Concatenate three null-terminated strings and return the result.
///
/// \param s1           Pointer to the first null-terminated string.
/// \param s2           Pointer to the second null-terminated string.
/// \param s3           Pointer to the third null-terminated string.
///
/// \return A dynamically allocated string containing the concatenated
/// result, or NULL on allocation failure.
///
///////////////////////////////////////////////////////////////////////////////
string_t my_strdcat(cstring_t s1, cstring_t s2, cstring_t s3);

///////////////////////////////////////////////////////////////////////////////
/// \brief Convert a string to a word array using a separator
///
/// \param str          Pointer to the null-derminated string
/// \param str          The separator used
///
/// \return Array of words
///
///////////////////////////////////////////////////////////////////////////////
warray_t my_strsplit(string_t str, char separator);

///////////////////////////////////////////////////////////////////////////////
/// \brief Check if all characters in a string satisfy a specified condition.
///
/// \param str          Pointer to the null-terminated string.
/// \param type         The function defining the condition for each character.
///
/// \return True if all characters satisfy the condition, false otherwise.
///
///////////////////////////////////////////////////////////////////////////////
bool_t my_stris(cstring_t str, bool_t (*type)(int ch));

///////////////////////////////////////////////////////////////////////////////
/// \brief Check if a value exists in a null-terminated array of strings.
///
/// \param wa           The null-terminated array of strings to be checked.
/// \param search       The value to be searched for in the array.
///
/// \return True if the value is found, false otherwise.
///
///////////////////////////////////////////////////////////////////////////////
bool_t my_wacmp(warray_t wa, string_t search);

///////////////////////////////////////////////////////////////////////////////
/// \brief libmy macros (DO NOT USE)
///
///////////////////////////////////////////////////////////////////////////////
    #define RETURN(cond, val) if ((cond)) return (val)

///////////////////////////////////////////////////////////////////////////////
/// \brief libmy macros (DO NOT USE)
///
///////////////////////////////////////////////////////////////////////////////
    #define DOIF(cond, func) if ((cond)) func

///////////////////////////////////////////////////////////////////////////////
/// \brief Convert a string to a long integer
///
/// \param s            The string to convert
/// \param ptr          A pointer to a pointer to char, which will be updated
///                     to point to the first non-converted character
///
/// \return The converted long integer value
///
///////////////////////////////////////////////////////////////////////////////
int my_strtol(cstring_t s, cstring_t *ptr);

///////////////////////////////////////////////////////////////////////////////
/// \brief Macro for displaying an error message using 'my_puterr'.
///
/// \param v            The variable or value associated with the error.
/// \param txt          The text of the error message.
///
///////////////////////////////////////////////////////////////////////////////
    #define PUTERR(v, txt) (my_puterr(v), my_puterr(txt))

///////////////////////////////////////////////////////////////////////////////
/// \brief Print a null-terminated string to the standard error output.
///
/// \param str          Pointer to the null-terminated string to be printed.
///
///////////////////////////////////////////////////////////////////////////////
void my_puterr(cstring_t str);

///////////////////////////////////////////////////////////////////////////////
/// \brief Print a null-terminated string to the standard output.
///
/// \param str          Pointer to the null-terminated string to be printed.
///
///////////////////////////////////////////////////////////////////////////////
void my_putstr(cstring_t str);

///////////////////////////////////////////////////////////////////////////////
/// \brief Print a single character to the standard output.
///
/// \param ch           The character to be printed.
///
///////////////////////////////////////////////////////////////////////////////
void my_putchar(int ch);

///////////////////////////////////////////////////////////////////////////////
/// \brief Print an array of mutable strings with a specified separator.
///
/// \param wa           The array of mutable strings to be printed
/// \param separator    The character used to separate each string in the
///                     output
///
///////////////////////////////////////////////////////////////////////////////
void my_putwa(warray_t wa, char separator);

///////////////////////////////////////////////////////////////////////////////
/// \brief Writes a string to a file descriptor followed by a newline character
///
/// \param fd           The file descriptor to write to.
/// \param str          The string to be written.
///
/// \return The number of bytes written in the fd
///
///////////////////////////////////////////////////////////////////////////////
ulong_t my_fputs(int fd, string_t str);

///////////////////////////////////////////////////////////////////////////////
/// \brief Convert a string to an integer
///
/// \param str          The input string to convert to an integer
///
/// \return Returns the integer value corresponding to 'str'
///
///////////////////////////////////////////////////////////////////////////////
int my_atoi(cstring_t str);

///////////////////////////////////////////////////////////////////////////////
/// \brief Copy memory area
///
/// \param dst          Pointer to the destination memory area
/// \param src          Pointer to the source memory area
/// \param n            Number of bytes to copy
///
/// \return Pointer to the destination memory area ('dst')
///////////////////////////////////////////////////////////////////////////////
void *my_memcpy(void *dst, const void *src, ulong_t n);

///////////////////////////////////////////////////////////////////////////////
/// \brief Fill a block of memory with a specified value.
///
/// \param src          Pointer to the memory block to be filled.
/// \param ch           The value to be set (casted to char).
/// \param n            Number of bytes to fill.
///
/// \return Pointer to the filled memory block.
///
///////////////////////////////////////////////////////////////////////////////
void *my_memset(void *src, int ch, ulong_t n);

///////////////////////////////////////////////////////////////////////////////
/// \brief Reallocate memory for a block with a new size and copy the existing
/// data.
///
/// \param ptr          Pointer to the current memory block to be reallocated.
/// \param size         New size of the memory block in bytes.
///
/// \return Pointer to the reallocated and copied memory block.
///
///////////////////////////////////////////////////////////////////////////////
void *my_realloc(void *ptr, ulong_t size);

///////////////////////////////////////////////////////////////////////////////
/// \brief Safe free avoiding freeing NULL
///
/// \param ptr          The pointer
///
///////////////////////////////////////////////////////////////////////////////
void my_free(void **ptr);

///////////////////////////////////////////////////////////////////////////////
/// \brief Use my_free function by transforming the pointer to the correct type
///
/// \param ptr          The pointer
///
///////////////////////////////////////////////////////////////////////////////
    #define FREE(p) my_free((void **)&(p))

///////////////////////////////////////////////////////////////////////////////
/// \brief Check if a string represents a valid integer
///
/// \param str          The input string to check for integer representation
///
/// \return Returns true if 'str' represents a valid integer, otherwise
/// false
///
///////////////////////////////////////////////////////////////////////////////
bool_t my_isint(cstring_t str);

///////////////////////////////////////////////////////////////////////////////
/// \brief Locate the first occurrence of any character in a set.
///
/// \param s            Pointer to the null-terminated string to search.
/// \param accept       Pointer to the null-terminated set of characters to
///                     match.
///
/// \return A pointer to the first matching character in the string or NULL.
///
///////////////////////////////////////////////////////////////////////////////
string_t my_strpbrk(cstring_t s, cstring_t accept);

///////////////////////////////////////////////////////////////////////////////
/// \brief Calculate the length of the initial segment of a string consisting
///        of only characters from another string.
///
/// \param s1           Pointer to the null-terminated string to check.
/// \param s2           Pointer to the null-terminated string containing
///                     characters to match against.
///
/// \return The length of the initial segment of s1 consisting of only
///         characters from s2.
///
///////////////////////////////////////////////////////////////////////////////
ulong_t my_strspn(cstring_t s1, cstring_t s2);

///////////////////////////////////////////////////////////////////////////////
/// \brief Extract tokens from a string.
///
/// \param s            String to tokenize (NULL for subsequent calls).
/// \param delim        Delimiter characters.
/// \param save_ptr     Pointer to a string to maintain state across calls.
///
/// \return A pointer to the next token in the string, or NULL if no more
///         tokens are found.
///
///////////////////////////////////////////////////////////////////////////////
string_t my_strtok_r(string_t s, cstring_t delim, string_t *save_ptr);

///////////////////////////////////////////////////////////////////////////////
/// \brief Extract tokens from a string.
///
/// \param str          String to tokenize (NULL for subsequent calls).
/// \param delim        Delimiter characters.
///
/// \return A pointer to the next token in the string, or NULL if no more
///         tokens are found.
///
///////////////////////////////////////////////////////////////////////////////
string_t my_strtok(string_t str, cstring_t delim);

///////////////////////////////////////////////////////////////////////////////
/// \brief Locate the first occurrence of a character in a string.
///
/// \param p            Pointer to the null-terminated string to search.
/// \param ch           The character to search for.
///
/// \return A pointer to the first matching character in the string or NULL.
///
///////////////////////////////////////////////////////////////////////////////
string_t my_strchr(cstring_t p, int ch);

///////////////////////////////////////////////////////////////////////////////
/// \brief Reallocate memory for a block with a new size and copy the existing
/// data.
///
/// \param ptr          Pointer to the current memory block to be reallocated.
/// \param old_size     New size of the memory block in bytes.
/// \param new_size     Old size of the memory block in bytes.
///
/// \return      Pointer to the reallocated and copied memory block.
///
///////////////////////////////////////////////////////////////////////////////
void *my_orealloc(void *ptr, ulong_t old_size, ulong_t new_size);

///////////////////////////////////////////////////////////////////////////////
/// \brief Count the occurrences of a specified character in a null-terminated
///        string.
///
/// \param str          Pointer to the null-terminated string.
/// \param ch           The character to count in the string.
///
/// \return The number of occurrences of the specified character in the string.
///
///////////////////////////////////////////////////////////////////////////////
ulong_t my_countchar(cstring_t str, char ch);

///////////////////////////////////////////////////////////////////////////////
/// \brief Count the number of words in the string
///
/// \param str          Pointer to the null-derminated string
///
/// \return Return the number of words
///
///////////////////////////////////////////////////////////////////////////////
uint_t my_wcount(cstring_t str);

///////////////////////////////////////////////////////////////////////////////
/// \brief Print an integer to the standard output.
///
/// \param nbr          The integer to be printed.
///
///////////////////////////////////////////////////////////////////////////////
void my_putnbr(int nbr);

///////////////////////////////////////////////////////////////////////////////
/// \brief Convert a string to a boolean value
///
/// \param str          The input string to convert to a boolean value
///
/// \return Returns the boolean value corresponding to 'str', or false if the
///conversion is not possible
///
///////////////////////////////////////////////////////////////////////////////
bool_t my_atob(cstring_t str);

///////////////////////////////////////////////////////////////////////////////
/// \brief Convert a string to a floating-point number
///
/// \param str          The input string to convert to a floating-point number
///
/// \return Returns the floating-point value corresponding to 'str'
///
///////////////////////////////////////////////////////////////////////////////
double my_atof(cstring_t str);

///////////////////////////////////////////////////////////////////////////////
/// \brief Check if a string represents a valid boolean value
///
/// \param str          The input string to check for boolean representation
///
/// \return Returns true if 'str' represents a valid boolean value, otherwise
/// false
///
///////////////////////////////////////////////////////////////////////////////
bool_t my_isbool(cstring_t str);

///////////////////////////////////////////////////////////////////////////////
/// \brief Check if a string represents a valid floating-point number
///
/// \param str          The input string to check for floating-point
///                     representation
///
/// \return Returns true if 'str' represents a valid floating-point number,
/// otherwise false
///
///////////////////////////////////////////////////////////////////////////////
bool_t my_isfloat(cstring_t str);

///////////////////////////////////////////////////////////////////////////////
/// \brief Count the number of entries in a directory.
///
/// \param path         The path of the directory.
///
/// \return The number of entries in the directory.
///
///////////////////////////////////////////////////////////////////////////////
u8_t my_dirlen(cstring_t path);

///////////////////////////////////////////////////////////////////////////////
/// \brief Retrieves the content of a directory.
///
/// \param path         The path of the directory.
///
/// \return An array containing the names of the files and directories in the
/// specified path.
///
///////////////////////////////////////////////////////////////////////////////
warray_t my_dircontent(cstring_t path);

///////////////////////////////////////////////////////////////////////////////
/// \brief Determine if a path is a directory
///
/// \param path         The path to check
///
/// \return True if the path is a directory, false otherwise or false if the
/// path doesn't exists
///
///////////////////////////////////////////////////////////////////////////////
bool_t my_isdir(cstring_t path);

///////////////////////////////////////////////////////////////////////////////
/// \brief Find the extension name of a path
///
/// \param path         The path to look for an extension
///
/// \return A pointer to the extension, NULL otherwise
///
///////////////////////////////////////////////////////////////////////////////
string_t my_extname(cstring_t path);

///////////////////////////////////////////////////////////////////////////////
/// \brief Find the last occurence of a character
///
/// \param str          The string for looking
/// \param ch           The character to look for
///
/// \return Pointer to the last occurence of the character, NULL otherwise
///
///////////////////////////////////////////////////////////////////////////////
string_t my_strrchr(cstring_t str, int ch);

///////////////////////////////////////////////////////////////////////////////
/// \brief Print an error message on the stderr
///
/// \param err          The error message
///
/// \return Always return false
///
///////////////////////////////////////////////////////////////////////////////
bool_t my_error(cstring_t err);

///////////////////////////////////////////////////////////////////////////////
/// \brief Find the basename of a filename
///
/// \param filename     The filename to check
///
/// \return Pointer to the basename of the file
///
///////////////////////////////////////////////////////////////////////////////
string_t my_basename(cstring_t filename);

///////////////////////////////////////////////////////////////////////////////
/// \brief Append a character to the content of a buffer.
///
/// \param buffer       The buffer to which the character will be appended.
/// \param c            The character to append to the buffer.
///
///////////////////////////////////////////////////////////////////////////////
void my_buffchar(buffer_t *buffer, char c);

///////////////////////////////////////////////////////////////////////////////
/// \brief Initialize a buffer with default values.
///
/// \return Pointer to the newly initialized buffer or NULL on allocation
/// failure.
///
///////////////////////////////////////////////////////////////////////////////
buffer_t *my_buffinit(void);

///////////////////////////////////////////////////////////////////////////////
/// \brief Append a string to the content of a buffer.
///
/// \param buffer       The buffer to which the string will be appended.
/// \param str          The null-terminated string to append to the buffer.
///
///////////////////////////////////////////////////////////////////////////////
void my_buffstr(buffer_t *buffer, cstring_t str);

///////////////////////////////////////////////////////////////////////////////
/// \brief Append an integer to the content of a buffer.
///
/// \param buffer       The buffer to which the integer will be appended.
/// \param value        The integer value to append to the buffer.
/// \param bytes        The number of bytes to consider from the integer.
///
///////////////////////////////////////////////////////////////////////////////
void my_buffint(buffer_t *buffer, uint_t value, uint_t bytes);

///////////////////////////////////////////////////////////////////////////////
/// \brief Deallocate memory for a buffer.
///
/// \param buffer       The buffer to deallocate.
///
///////////////////////////////////////////////////////////////////////////////
void my_bufftroy(buffer_t *buffer);

///////////////////////////////////////////////////////////////////////////////
/// \brief Write the content of a buffer to a file.
///
/// \param buffer       The buffer containing the content to be written.
/// \param path         The filename to write the content to.
///
/// \return True on successful write, false otherwise.
///
///////////////////////////////////////////////////////////////////////////////
bool_t my_fbuff(buffer_t *buffer, cstring_t path);

///////////////////////////////////////////////////////////////////////////////
/// \brief Read an unsigned int from a buffer
///
/// \param buff         The buffer to read from
/// \param bytes        The number of bytes in the int
/// \param idx          Pointer to the current reading index
///
/// \return The unsigned integer readed from the buffer
///
///////////////////////////////////////////////////////////////////////////////
uint_t my_rbuffint(cstring_t buff, uint_t bytes, ulong_t *idx);

#endif /* !LIBMY_H_ */