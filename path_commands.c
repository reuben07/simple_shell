#include "Shell.h"

/**
 * is_executable_command - Determines if a file is an executable command.
 * @info_struct: The info struct.
 * @file_path: Path to the file.
 *
 * Return: 1 if the file is an executable command, 0 otherwise.
 */
int is_executable_command(info_t *info_struct, char *file_path)
{
	struct stat file_stat;

	(void)info_struct;
	if (!file_path || stat(file_path, &file_stat))
		return 0;

	if (file_stat.st_mode & S_IFREG)
	{
		return 1;
	}
	return 0;
}

/**
 * copy_characters - Copies characters from a string within a specified range.
 * @input_string: The input string.
 * @start_index: The starting index (inclusive).
 * @end_index: The stopping index (exclusive).
 *
 * Return: A pointer to a new buffer containing the copied characters.
 */
char *copy_characters(char *input_string, int start_index, int end_index)
{
	static char buffer[1024];
	int i = 0, k = 0;

	for (k = 0, i = start_index; i < end_index; i++)
	{
		if (input_string[i] != ':')
			buffer[k++] = input_string[i];
	}
	buffer[k] = '\0';
	return buffer;
}

/**
 * find_command_path - Finds the full path of a command in the PATH environment variable.
 * @info_struct: The info struct.
 * @path_string: The PATH environment variable string.
 * @command: The command to find.
 *
 * Return: The full path of the command if found, or NULL if not found.
 */
char *find_command_path(info_t *info_struct, char *path_string, char *command)
{
	int i = 0, current_position = 0;
	char *path;

	if (!path_string)
		return NULL;

	if ((string_len(command) > 2) && needle_starts(command, "./"))
	{
		if (is_executable_command(info_struct, command))
			return command;
	}

	while (1)
	{
		if (!path_string[i] || path_string[i] == ':')
		{
			path = copy_characters(path_string, current_position, i);
			if (!*path)
				string_conc(path, command);
			else
			{
				string_conc(path, "/");
				string_conc(path, command);
			}
			if (is_executable_command(info_struct, path))
				return path;

			if (!path_string[i])
				break;

			current_position = i;
		}
		i++;
	}

	return NULL;
}
