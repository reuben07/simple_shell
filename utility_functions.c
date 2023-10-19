#include "Shell.h"

/**
 * check_interactive_mode - Checks if the shell is in interactive mode.
 * @info: The structure containing information about the shell.
 *
 * Return: 1 if the shell is in interactive mode, 0 otherwise.
 */
int check_interactive_mode(info_t *info)
{
	return (isatty(STDIN_FILENO) && info->readfd <= 2);
}

/**
 * is_character_delimiter - Checks if a character is a delimiter.
 * @c: The character to check.
 * @delimiters: The delimiter string.
 *
 * Return: 1 if true, 0 if false.
 */
int is_character_delimiter(char c, char *delimiters)
{
	while (*delimiters)
		if (*delimiters++ == c)
			return (1);
	return (0);
}

/**
 * is_character_alphabetic - Checks if a character is alphabetic.
 * @c: The character to check.
 *
 * Return: 1 if 'c' is alphabetic, 0 otherwise.
 */
int is_character_alphabetic(int c)
{
	if ((c >= 'a' && c <= 'z') || (c >= 'A' && c <= 'Z'))
		return (1);
	else
		return (0);
}

/**
 * convert_string_to_integer - Converts a string to an integer.
 * @s: The string to be converted.
 *
 * Return: 0 if there are no numbers in the string, the converted number otherwise.
 */
int convert_string_to_integer(char *s)
{
	int i, sign = 1, flag = 0, output;
	unsigned int result = 0;

	for (i = 0; s[i] != '\0' && flag != 2; i++)
	{
		if (s[i] == '-')
			sign *= -1;

		if (s[i] >= '0' && s[i] <= '9')
		{
			flag = 1;
			result *= 10;
			result += (s[i] - '0');
		}
		else if (flag == 1)
			flag = 2;
	}

	if (sign == -1)
		output = -result;
	else
		output = result;

	return (output);
}
