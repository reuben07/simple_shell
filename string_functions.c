#include "Shell.h"

/**
 * custom_copy - Copies the first 'max_chars' characters from the source string to the destination string.
 * @dst: The destination string to copy to.
 * @src: The source string.
 * @max_chars: The maximum number of characters to copy.
 *
 * Returns: A pointer to the modified destination string.
 */
char *custom_copy(char *dst, char *src, int max_chars)
{
    int index;
    char *result = dst;

    for (index = 0; index < max_chars - 1 && src[index] != '\0'; index++)
        dst[index] = src[index];
    dst[index] = '\0';

    return result;
}

/**
 * custom_concat - Concatenates the first 'max_bytes' bytes of the source string to the end of the destination string.
 * @dst: The destination string.
 * @src: The source string.
 * @max_bytes: The maximum number of bytes to concatenate.
 *
 * Returns: A pointer to the modified destination string.
 */
char *custom_concat(char *dst, char *src, int max_bytes)
{
    int dst_length = string_len(dst);
    int index;

    for (index = 0; index < max_bytes && src[index] != '\0'; index++)
        dst[dst_length + index] = src[index];
    dst[dst_length + index] = '\0';

    return dst;
}

/**
 * custom_char_search - Searches for the first occurrence of a character 'target_char' in the input string 'str'.
 * @str: The string to search within.
 * @target_char: The character to look for.
 *
 * Returns: A pointer to the first occurrence of 'target_char' in 'str', or NULL if not found.
 */
char *custom_char_search(char *str, char target_char)
{
    do
    {
        if (*str == target_char)
            return str;
    } while (*str++ != '\0');

    return NULL;
}
