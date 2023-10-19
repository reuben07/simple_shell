#include "shell.h"

/**
 * main - Entry point of the shell program
 *
 * Return: Always 0 (Success)
 */

int main(void)
{
	char *STring = "This is my simple shell project";

	/* Print the string for the shell project */
	_puts_norm(STring);

	return (0);
}

/**
 * _puts_norm - Print a string to the standard output
 * @s: The string to be printed
 *
 * Return: Number of characters printed (excluding null byte)
 */

int _puts_norm(char *s)
{
	char *message = "Print Message: ";

	_puts(message);
	_puts(s);

	return (_strlen(s));
}

/**
 * _puts - Print a string to the standard output
 * @s: The string to be printed
 */

void _puts(char *s)
{
	while (*s)
	{
		_putchar(*s);
		s++;
	}
	_putchar('\n');
}

/**
 * _putchar - Write a character to the standard output
 * @c: The character to be written
 *
 * Return: On success, 1. On error, -1 is returned.
 */

int _putchar(char c)
{
	return (write(1, &c, 1));
}

/**
 * _strlen - Calculate the length of a string
 * @s: The string to be measured
 *
 * Return: Length of the string
 */

int _strlen(const char *s)
{
	int length = 0;

	while (s[length] != '\0')
	{
		length++;
	}

	return (length);
}
