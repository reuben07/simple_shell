#include "Shell.h"

/**
 * _eputs - prints an input string to stderr
 * @str: the string to be printed
 *
 * Return: Nothing
 */

void _eputs(char *str)
{
	if (!str)
		return;

	while (*str)
	{
		_eputchar(*str++);
	}
}

/**
 * _eputchar - writes the character c to stderr
 * @c: The character to print
 *
 * Return: On success 1.
 * On error, -1 is returned, and errno is set appropriately.
 */

int _eputchar(char c)
{
	static int i;
	static char buf[WRITE_BUF_SIZE];

	if (c == BUF_FLUSH || i >= WRITE_BUF_SIZE)
	{
		write(2, buf, i);
		i = 0;
	}

	if (c != BUF_FLUSH)
		buf[i++] = c;

	return (1);
}

/**
 * _putfd - writes the character c to given fd
 * @c: The character to print
 * @fd: The file descriptor to write to
 *
 * Return: On success 1.
 * On error, -1 is returned, and errno is set appropriately.
 */

int _putfd(char c, int fd)
{
	static int i;
	static char buf[WRITE_BUF_SIZE];

	if (c == BUF_FLUSH || i >= WRITE_BUF_SIZE)
	{
		write(fd, buf, i);
		i = 0;
	}

	if (c != BUF_FLUSH)
		buf[i++] = c;

	return (1);
}

/**
 * _putsfd - prints an input string to a specified file descriptor
 * @str: the string to be printed
 * @fd: the file descriptor to write to
 *
 * Return: the number of characters put
 */

int _putsfd(char *str, int fd)
{
    
	int count = 0;

	if (!str)
		return (0);

	while (*str)
	{
		count += _putfd(*str++, fd);
	}

	return (count);
}
