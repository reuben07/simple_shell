#include "Shell.h"

/**
 * duplicate_environment - Returns a copy of the environment as an array of strings.
 * @info: Structure containing potential arguments. Used to maintain a
 *        constant function prototype.
 * Return: Always 0
 */
char **duplicate_environment(info_t *info)
{
	if (!info->environ || info->env_altered)
	{
		info->environ = list_to_strings(info->env);
		info->env_altered = 0;
	}

	return (info->environ);
}

/**
 * eliminate_environment_variable - Removes an environment variable.
 * @info: Structure containing potential arguments. Used to maintain a
 *        constant function prototype.
 * @var: The string representing the environment variable to remove.
 * Return: 1 on successful removal, 0 if the variable was not found.
 */
int eliminate_environment_variable(info_t *info, char *var)
{
	list_t *current_node = info->env;
	size_t index = 0;
	char *needle;

	if (!current_node || !var)
		return (0);

	while (current_node)
	{
		needle = needle_starts(current_node->str, var);
		if (needle && *needle == '=')
		{
			info->env_altered = remove_node_at_index(&(info->env), index);
			index = 0;
			current_node = info->env;
			continue;
		}
		current_node = current_node->next;
		index++;
	}
	return (info->env_altered);
}

/**
 * insert_environment_variable - Initializes a new environment variable or modifies an existing one.
 * @info: Structure containing potential arguments. Used to maintain a
 *        constant function prototype.
 * @var: The string representing the environment variable property.
 * @value: The string representing the environment variable value.
 * Return: Always 0
 */
int insert_environment_variable(info_t *info, char *var, char *value)
{
	char *buffer = NULL;
	list_t *current_node;
	char *needle;

	if (!var || !value)
		return (0);

	buffer = malloc(string_len(var) + string_len(value) + 2);
	if (!buffer)
		return (1);
	string_cpy(buffer, var);
	string_conc(buffer, "=");
	string_conc(buffer, value);
	current_node = info->env;
	while (current_node)
	{
		needle = needle_starts(current_node->str, var);
		if (needle && *needle == '=')
		{
			free(current_node->str);
			current_node->str = buffer;
			info->env_altered = 1;
			return (0);
		}
		current_node = current_node->next;
	}
	append_node(&(info->env), buffer, 0);
	free(buffer);
	info->env_altered = 1;
	return (0);
}
