#include "Shell.h"

/**
 * clear_shell_info - Initializes shell_info_t struct.
 * @shell_info: Address of the shell_info_t struct.
 */
void clear_shell_info(shell_info_t *shell_info)
{
	shell_info->argument = NULL;
	shell_info->arguments = NULL;
	shell_info->executable_path = NULL;
	shell_info->argument_count = 0;
}

/**
 * set_shell_info - Initializes shell_info_t struct.
 * @shell_info: Address of the shell_info_t struct.
 * @argument_vector: Argument vector.
 */
void set_shell_info(shell_info_t *shell_info, char **argument_vector)
{
	int i = 0;

	shell_info->filename = argument_vector[0];
	if (shell_info->argument)
	{
		shell_info->arguments = strtow(shell_info->argument, " \t");
		if (!shell_info->arguments)
		{
			shell_info->arguments = malloc(sizeof(char *) * 2);
			if (shell_info->arguments)
			{
				shell_info->arguments[0] = _strdup(shell_info->argument);
				shell_info->arguments[1] = NULL;
			}
		}
		for (i = 0; shell_info->arguments && shell_info->arguments[i]; i++)
			;
		shell_info->argument_count = i;

		replace_shell_alias(shell_info);
		replace_shell_variable(shell_info);
	}
}

/**
 * free_shell_info - Frees shell_info_t struct fields.
 * @shell_info: Address of the shell_info_t struct.
 * @free_all: True if freeing all fields.
 */
void free_shell_info(shell_info_t *shell_info, int free_all)
{
	ffree(shell_info->arguments);
	shell_info->arguments = NULL;
	shell_info->executable_path = NULL;
	if (free_all)
	{
		if (!shell_info->command_buffer)
			free(shell_info->argument);
		if (shell_info->environment)
			free_list(&(shell_info->environment));
		if (shell_info->history)
			free_list(&(shell_info->history));
		if (shell_info->alias)
			free_list(&(shell_info->alias));
		ffree(shell_info->environment_variables);
		shell_info->environment_variables = NULL;
		bfree((void **)shell_info->command_buffer);
		if (shell_info->read_file_descriptor > 2)
			close(shell_info->read_file_descriptor);
		_putchar(BUF_FLUSH);
	}
}
