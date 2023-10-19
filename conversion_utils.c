#include "Shell.h"

/**
 * string_to_integer - Converts a string to an integer.
 * @str: The string to be converted.
 *
 * Return: The converted number if successful, or -1 on error.
 */
int string_to_integer(char *str)
{
	int index = 0;
	unsigned long int result = 0;

	if (*str == '+')
		str++;
	for (index = 0; str[index] != '\0'; index++)
	{
		if (str[index] >= '0' && str[index] <= '9')
		{
			result *= 10;
			result += (str[index] - '0');
			if (result > INT_MAX)
				return -1;
		}
		else
			return -1;
	}
	return result;
}

/**
 * display_error_message - Prints an error message to the standard error.
 * @info: The parameter and return info struct.
 * @error_string: String containing a specified error type.
 */
void display_error_message(info_t *info, char *error_string)
{
	show_error_msg(info->filename);
	show_error_msg(": ");
	print_error_dec(info->line_number, STDERR_FILENO);
	show_error_msg(": ");
	show_error_msg(info->argv[0]);
	show_error_msg(": ");
	show_error_msg(error_string);
}

/**
 * print_error_dec - Prints a decimal (integer) number (base 10) to the specified file descriptor.
 * @input: The input number to be printed.
 * @fd: The file descriptor to write to.
 *
 * Return: The number of characters printed.
 */
int print_error_dec(int input, int fd)
{
	int (*__putchar)(char) = write_char;
	int i, count = 0;
	unsigned int absolute_value, current;

	if (fd == STDERR_FILENO)
		__putchar = _write_char_to_standard_error;
	if (input < 0)
	{
		absolute_value = -input;
		__putchar('-');
		count++;
	}
	else
		absolute_value = input;
	current = absolute_value;
	for (i = 1000000000; i > 1; i /= 10)
	{
		if (absolute_value / i)
		{
			__putchar('0' + current / i);
			count++;
		}
		current %= i;
	}
	__putchar('0' + current);
	count++;

	return count;
}

/**
 * convert_number_to_string - Converter function for converting
 * 		a number to a string.
 * @number: The number to be converted.
 * @base: The base for the conversion.
 * @flags: Argument flags.
 *
 * Return: The resulting string.
 */
char *convert_number_to_string(long int number, int base, int flags)
{
	static char *character_array;
	static char buffer[50];
	char sign = 0;
	char *pointer;
	unsigned long n = number;

	if (!(flags & CONVERT_UNSIGNED) && number < 0)
	{
		n = -number;
		sign = '-';
	}
	character_array = flags & CONVERT_LOWERCASE ? "0123456abcd" : "0123456ABCD";
	pointer = &buffer[49];
	*pointer = '\0';

	do
	{
		*--pointer = character_array[n % base];
		n /= base;
	} while (n != 0);

	if (sign)
		*--pointer = sign;
	return pointer;
}

/**
 * remove_comments - Replaces the first instance of
 * 		'#' with '\0' in the input string.
 * @buffer: Address of the string to modify.
 */
void remove_comments(char *buffer)
{
	int index;

	for (index = 0; buffer[index] != '\0'; index++)
		if (buffer[index] == '#' && (!index || buffer[index - 1] == ' '))
		{
			buffer[index] = '\0';
			break;
		}
}
