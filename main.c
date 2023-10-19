#include "Shell.h"

/**
 * main - Entry point for the shell program.
 * @argc: The number of arguments.
 * @argv: The argument vector.
 *
 * Return: 0 on success, non-zero on failure.
 */
int main(int argc, char *argv[])
{
	info_t param_info;
	char *arg_vector[] = {argv[0], NULL};

	initialize_info(&param_info, arg_vector);

	if (argc > 1)
	{
		if (batch_mode(&param_info, argv[1]) == -1)
		{
			free_info(&param_info, 1);
			return (EXIT_FAILURE);
		}
		free_info(&param_info, 1);
		return (EXIT_SUCCESS);
	}

	if (!check_interactive_mode(&param_info))
	{
		free_info(&param_info, 1);
		return (EXIT_SUCCESS);
	}

	return (shell_loop(&param_info, arg_vector));
}
