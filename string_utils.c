#include "Shell.h"

/**
 * string_copy - copies a string
 * @dest_str: the destination string
 * @src_str: the source string
 *
 * Return: pointer to destination string
 */
char *string_copy(char *dest_str, char *src_str)
{
	int index = 0;

	if (dest_str == src_str || src_str == NULL)
		return dest_str;

	while (src_str[index])
	{
		dest_str[index] = src_str[index];
		index++;
	}
	dest_str[index] = '\0';

	return dest_str;
}

/**
 * duplicate_string - duplicates a string
 * @str: the string to duplicate
 *
 * Return: pointer to the duplicated string
 */
char *duplicate_string(const char *str)
{
	int length = 0;
	char *result_str;

	if (str == NULL)
		return NULL;

	while (*str++)
		length++;

	result_str = malloc(sizeof(char) * (length + 1));
	if (!result_str)
		return NULL;

	for (length++; length--;)
		result_str[length] = *--str;

	return result_str;
}

/**
 * print_string - prints an input string
 * @str: the string to be printed
 *
 * Return: Nothing
 */
void print_string(char *str)
{
	int index = 0;

	if (!str)
		return;

	while (str[index] != '\0')
	{
		write_char(str[index]);
		index++;
	}
}

/**
 * write_character - writes the character c to stdout
 * @c: The character to print
 *
 * Return: On success 1.
 * On error, -1 is returned, and errno is set appropriately.
 */
int write_character(char c)
{
	static int index;
	static char buffer[WRITE_BUFFER_SIZE];

	if (c == BUFFER_FLUSH || index >= WRITE_BUFFER_SIZE)
	{
		write(1, buffer, index);
		index = 0;
	}

	if (c != BUFFER_FLUSH)
		buffer[index++] = c;

	return 1;
}
