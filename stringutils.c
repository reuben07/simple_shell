#include "Shell.h"

/**
 * str_length - Calculates the length of a string.
 * @str: The input string to determine the length of.
 *
 * Return: The integer length of the string.
 */
int str_len(char *str)
{
	int length = 0;

	if (!str)
		return 0;

	while (*str++)
		length++;
	return length;
}

/**
 * _str_compare - Performs lexicographic comparison between two strings.
 * @str1: The first string for comparison.
 * @str2: The second string for comparison.
 *
 * Return: Integer result of the comparison.
 */
int str_cmp(char *str1, char *str2)
{
	while (*str1 && *str2)
	{
		if (*str1 != *str2)
			return (*str1 - *str2);
		str1++;
		str2++;
	}
	if (*str1 == *str2)
		return 0;
	else
		return (*str1 < *str2 ? -1 : 1);
}

/**
 * needle_starts - Checks if the needle starts with the haystack.
 * @haystack: The string to search.
 * @needle: The substring to find.
 *
 * Return: A pointer to the remaining part of the haystack if needle starts, else NULL.
 */
char *needle_starts(const char *haystack, const char *needle)
{
	while (*needle)
		if (*needle++ != *haystack++)
			return NULL;
	return (char *)haystack;
}

/**
 * concatenate_strings - Concatenates two strings.
 * @destination: The destination buffer.
 * @source: The source buffer to append.
 *
 * Return: A pointer to the destination buffer.
 */
char *concatenate_strings(char *destination, char *source)
{
	char *result = destination;

	while (*destination)
		destination++;
	while (*source)
		*destination++ = *source++;
	*destination = *source;
	return result;
}
