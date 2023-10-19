#include "Shell.h"

/**
 * show_environment - Display the current environment.
 * @info: Structure containing potential arguments.
 *        Used to maintain constant function prototype.
 *
 * Return: Always 0.
 */
int _show_environment(info_t *info)
{
	output_string_list(info->env);
	return (0);
}

/**
 * get_environment_variable - Retrieve the value of an environment variable.
 * @info: Structure containing potential arguments. Used to maintain
 *        constant function prototype.
 * @name: Name of the environment variable.
 *
 * Return: The value of the environment variable.
 */
char *get_environment_variable(info_t *info, const char *variable_name)
{
	list_t *node = info->env;
	char *value;

	while (node)
	{
		value = needle_starts(node->str, variable_name);
		if (value && *value)
			return (value);
		node = node->next;
	}
	return (NULL);
}

/**
 * _set_environment_variable - Initialize a new environment variable or modify an existing one.
 * @info: Structure containing potential arguments. Used to maintain constant
 *        function prototype.
 *
 * Return: 1 on success, 0 on failure.
 */
int set_environment_variable(info_t *info)
{
	if (info->argc != 3)
	{
		show_error_msg("Invalid number of arguments\n");
		return (0);
	}
	if (add_env_variable(info, info->argv[1], info->argv[2]))
		return (1);
	return (0);
}

/**
 * _unset_environment_variable - Remove one or more environment variables.
 * @info: Structure containing potential arguments. Used to maintain
 *        constant function prototype.
 *
 * Return: 0 on success, 1 on failure.
 */
int _unset_environment_variable(info_t *info)
{
	int i;

	if (info->argc == 1)
	{
		show_error_msg("Few arguments.\n");
		return (1);
	}
	for (i = 1; i <= info->argc; i++)
		remove_env_variable(info, info->argv[i]);

	return (0);
}

/**
 * populate_env - Populate the env linked list with the current environment variables.
 * @info: Structure containing potential arguments. Used to maintain
 *        constant function prototype.
 *
 * Return: Always 0.
 */
int populate_env(info_t *info)
{
	list_t *node = NULL;
	size_t i;

	for (i = 0; environ[i]; i++)
		append_node(&node, environ[i], 0);
	info->env = node;
	return (0);
}
