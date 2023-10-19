#include "Shell.h"

/**
 * shell_loop - Main shell loop.
 * @param_info: The parameter & return info struct.
 * @arg_vector: The argument vector from main().
 *
 * Return: 0 on success, 1 on error, or error code.
 */
int shell_loop(info_t *param_info, char **arg_vector)
{
	ssize_t read_result = 0;
	int builtin_result = 0;

	while (read_result != -1 && builtin_result != -2)
	{
		clear_info(param_info);
		if (interactive_mode(param_info))
			string_puts("shell$ ");
		_write_char_to_stderr(BUF_FLUSH);
		read_result = get_line_input(param_info);
		if (read_result != -1)
		{
			initialize_info(param_info, arg_vector);
			builtin_result = find_builtin_command(param_info);
			if (builtin_result == -1)
				find_command_in_path(param_info);
		}
		else if (interactive_mode(param_info))
			write_char('\n');
		free_info(param_info, 0);
	}
	save_history_to_file(param_info);
	free_info(param_info, 1);
	if (!interactive_mode(param_info) && param_info->status)
		exit(param_info->status);
	if (builtin_result == -2)
	{
		if (param_info->err_num == -1)
			exit(param_info->status);
		exit(param_info->err_num);
	}
	return (builtin_result);
}

/**
 * find_builtin_command - Finds a built-in command.
 * @param_info: The parameter & return info struct.
 *
 * Return: The return code from the built-in command.
 */
int find_builtin_command(info_t *param_info)
{
	int i, builtin_result = -1;
	builtin_table builtintbl[] = {
		{"exit", _shellexit},
		{"env", _listenv},
		{"help", _seehelp},
		{"history", _allhistory},
		{"setenv", _setenvironment},
		{"unsetenv", _unsetenvironment},
		{"cd", _changedir},
		{"alias", _myalias},
		{NULL, NULL}};

	for (i = 0; builtintbl[i].type; i++)
		if (string_cmp(param_info->argv[0], builtintbl[i].type) == 0)
		{
			param_info->line_count++;
			builtin_result = builtintbl[i].func(param_info);
			break;
		}
	return (builtin_result);
}

/**
 * find_command_in_path - Finds a command in the PATH.
 * @param_info: The parameter & return info struct.
 */
void find_command_in_path(info_t *param_info)
{
	char *path = NULL;
	int i, arg_count;

	param_info->path = param_info->argv[0];
	if (param_info->linecount_flag == 1)
	{
		param_info->line_count++;
		param_info->linecount_flag = 0;
	}
	for (i = 0, arg_count = 0; param_info->arg[i]; i++)
		if (!char_delim(param_info->arg[i], " \t\n"))
			arg_count++;
	if (!arg_count)
		return;

	path = locate_path(param_info, _environment_variable(param_info, "PATH="), param_info->argv[0]);
	if (path)
	{
		param_info->path = path;
		fork_exec_command(param_info);
	}
	else
	{
		if ((interactive_mode(param_info) || _environment_variable(param_info, "PATH=") || param_info->argv[0][0] == '/') && file_cmd(param_info, param_info->argv[0]))
			fork_exec_command(param_info);
		else if (*(param_info->arg) != '\n')
		{
			param_info->status = 127;
			print_error(param_info, "Not Available\n");
		}
	}
}

/**
 * fork_exec_command - Forks a child process to execute a command.
 * @param_info: The parameter & return info struct.
 */
void fork_exec_command(info_t *param_info)
{
	pid_t child_pid;

	child_pid = fork();
	if (child_pid == -1)
	{
		perror("Error:");
		return;
	}
	if (child_pid == 0)
	{
		if (execve(param_info->path, param_info->argv, copy_env_strings(param_info)) == -1)
		{
			free_info(param_info, 1);
			if (errno == EACCES)
				exit(126);
			exit(1);
		}
	}
	else
	{
		wait(&(param_info->status));
		if (WIFEXITED(param_info->status))
		{
			param_info->status = WEXITSTATUS(param_info->status);
			if (param_info->status == 126)
				print_error(param_info, "Permission denied\n");
		}
	}
}
