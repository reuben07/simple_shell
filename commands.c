#include "Shell.h"

/**
 * exit_shell - Exits the shell.
 * @info: Structure containing potential arguments.
 *
 * Return: Exits with a given exit status.
 *         (0) if info->argv[0] != "exit"
 */
int exit_shell(info_t *info)
{
	int exit_code;

	if (info->argv[1])
	{
		exit_code = string_to_int(info->argv[1]);
		if (exit_code == -1)
		{
			info->status = 2;
			print_error(info, "Invalid number: ");
			show_error_msg(info->argv[1]);
			_write_char_to_stderr('\n');
			return (1);
		}
		info->err_num = string_to_int(info->argv[1]);
		return (-2);
	}
	info->err_num = -1;
	return (-2);
}

/**
 * _change_dir - Changes the current directory of the process.
 * @info: Structure containing potential arguments.
 *
 * Return: Always 0.
 */
int _change_dir(info_t *info)
{
	char *curr_dir, *target_dir, buffer[1024];
	int chdir_result;

	curr_dir = getcwd(buffer, 1024);
	if (!curr_dir)
		string_puts("TODO: >>Failure message here<<\n");
	if (!info->argv[1])
	{
		target_dir = _environment_variable(info, "HOME=");
		if (!target_dir)
			chdir_result = chdir((target_dir = _environment_variable(info, "PWD=")) ? target_dir : "/");
		else
			chdir_result = chdir(target_dir);
	}
	else if (string_cmp(info->argv[1], "-") == 0)
	{
		if (!_environment_variable(info, "OLDPWD="))
		{
			string_puts(curr_dir);
			write_char('\n');
			return (1);
		}
		string_puts(_environment_variable(info, "OLDPWD=")), write_char('\n');
		chdir_result = chdir((target_dir = _environment_variable(info, "OLDPWD=")) ? target_dir : "/");
	}
	else
		chdir_result = chdir(info->argv[1]);
	if (chdir_result == -1)
	{
		print_error(info, "Can't change directory!");
		show_error_msg(info->argv[1]);
		_write_char_to_stderr('\n');
	}
	else
	{
		add_env_variable(info, "OLDPWD", _environment_variable(info, "PWD="));
		add_env_variable(info, "PWD", getcwd(buffer, 1024));
	}
	return (0);
}

/**
 * get_help - Provides help information.
 * @info: Structure containing potential arguments.
 *
 * Return: Always 0.
 */
int get_help(info_t *info)
{
	char **arg_array;

	arg_array = info->argv;
	string_puts("Help function works\n");
	if (0)
		string_puts(*arg_array);
	return (0);
}
