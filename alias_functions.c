#include "Shell.h"

/**
 * _all_history - Displays the history list, one command per line, preceded
 * with line numbers starting at 0.
 * @info: Parameter struct for maintaining function prototype.
 *
 * Return: Always 0.
 */
int _all_history(info_t *info)
{
	list_t *curr_node = info->history;
	show_list(curr_node);
	return (0);
}

/**
 * unset_alias - Unsets an alias by its name.
 * @info: Parameter struct.
 * @alias_str: The alias string to unset.
 *
 * Return: Always 0 on success, 1 on error.
 */
int unset_alias(info_t *info, char *alias_str)
{
	char *equal_pos;
	char saved_char;
	int ret_val;

	equal_pos = string_char(alias_str, '=');
	if (!equal_pos)
		return (1);
	saved_char = *equal_pos;
	*equal_pos = 0;
	ret_val = remove_node_at_index(&(info->alias),
		                           retrieve_node_index(info->alias, find_node_with_prefix(info->alias, alias_str, -1)));
	*equal_pos = saved_char;
	return (ret_val);
}

/**
 * assign_alias - Sets an alias to a string.
 * @info: Parameter struct.
 * @alias_str: The alias string to set.
 *
 * Return: Always 0 on success, 1 on error.
 */
int assign_alias(info_t *info, char *alias_str)
{
	char *equal_pos;

	equal_pos = string_char(alias_str, '=');
	if (!equal_pos)
		return (1);
	if (!*++equal_pos)
		return (remove_alias(info, alias_str));

	remove_alias(info, alias_str);
	return (append_node(&(info->alias), alias_str, 0) == NULL);
}

/**
 * show_alias - Prints an alias string.
 * @alias_node: The alias node.
 *
 * Return: Always 0 on success, 1 on error.
 */
int show_alias(list_t *alias_node)
{
	char *equal_pos = NULL;
	char *char_ptr = NULL;

	if (alias_node)
	{
		equal_pos = string_char(alias_node->str, '=');
		for (char_ptr = alias_node->str; char_ptr <= equal_pos; char_ptr++)
			write_char(*char_ptr);
		write_char('\'');
		string_puts(equal_pos + 1);
		string_puts("'\n");
		return (0);
	}
	return (1);
}

/**
 * _my_alias - Mimics the alias built-in (man alias).
 * @info: Parameter struct for maintaining function prototype.
 *
 * Return: Always 0.
 */
int _my_alias(info_t *info)
{
	int i = 0;
	char *equal_pos = NULL;
	list_t *alias_node = NULL;

	if (info->argc == 1)
	{
		alias_node = info->alias;
		while (alias_node)
		{
			display_alias(alias_node);
			alias_node = alias_node->next;
		}
		return (0);
	}
	for (i = 1; info->argv[i]; i++)
	{
		equal_pos = string_char(info->argv[i], '=');
		if (equal_pos)
			add_alias(info, info->argv[i]);
		else
			display_alias(find_node_with_prefix(info->alias, info->argv[i], '='));
	}

	return (0);
}
