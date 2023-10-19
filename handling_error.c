#include "Shell.h"

/**
 * display_error_message - Prints an error message to stderr.
 * @message: The string to be printed.
 *
 * Return: Nothing.
 */
void display_error_message(char *message)
{
	int index = 0;

	if (!message)
		return;
	while (message[index] != '\0')
	{
		_write_char_to_stderr(message[index]);
		index++;
	}
}

/**
 * write_char_to_standard_error - Writes a character to stderr.
 * @character: The character to print.
 *
 * Return: On success, 1. On error, -1 is returned, and errno is set appropriately.
 */
int write_char_to_standard_error(char character)
{
	static int index;
	static char buffer[WRITE_BUFFER_SIZE];

	if (character == BUF_FLUSH || index >= WRITE_BUFFER_SIZE)
	{
		write(2, buffer, index);
		index = 0;
	}
	if (character != BUF_FLUSH)
		buffer[index++] = character;
	return 1;
}

/**
 * write_to_file_descriptor - Writes a character to a given file descriptor.
 * @character: The character to print.
 * @file_descriptor: The file descriptor to write to.
 *
 * Return: On success, 1. On error, -1 is returned, and errno is set appropriately.
 */
int write_to_file_descriptor(char character, int file_descriptor)
{
	static int index;
	static char buffer[WRITE_BUFFER_SIZE];

	if (character == BUF_FLUSH || index >= WRITE_BUFFER_SIZE)
	{
		write(file_descriptor, buffer, index);
		index = 0;
	}
	if (character != BUF_FLUSH)
		buffer[index++] = character;
	return 1;
}

/**
 * write_string_to_file_descriptor - Writes an input string to a file descriptor.
 * @string: The string to be printed.
 * @file_descriptor: The file descriptor to write to.
 *
 * Return: The number of characters written.
 */
int write_string_to_file_descriptor(char *string, int file_descriptor)
{
	int count = 0;

	if (!string)
		return 0;
	while (*string)
	{
		count += _write_to_file_descriptor(*string++, file_descriptor);
	}
	return count;
}
