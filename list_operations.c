#include "Shell.h"

/**
 * count_elements - Counts the number of elements in a linked list.
 * @current_node: Pointer to the first node.
 *
 * Return: The total number of elements in the list.
 */
size_t count_elements(const list_t *current_node)
{
	size_t count = 0;

	while (current_node)
	{
		current_node = current_node->next;
		count++;
	}
	return count;
}

/**
 * convert_list_to_strings - Converts a linked list to an array of strings.
 * @head: Pointer to the first node.
 *
 * Return: An array of strings.
 */
char **convert_list_to_strings(list_t *head)
{
	list_t *current_node = head;
	size_t num_elements = count_elements(head), index;
	char **strings;
	char *current_string;

	if (!head || !num_elements)
		return NULL;

	strings = malloc(sizeof(char *) * (num_elements + 1));
	if (!strings)
		return NULL;

	for (index = 0; current_node; current_node = current_node->next, index++)
	{
		current_string = malloc(string_length(current_node->str) + 1);
		if (!current_string)
		{
			for (size_t j = 0; j < index; j++)
				free(strings[j]);
			free(strings);
			return NULL;
		}

		current_string = string_copy(current_string, current_node->str);
		strings[index] = current_string;
	}

	strings[index] = NULL;
	return strings;
}

/**
 * display_list_elements - Prints all elements of a list_t linked list.
 * @current_node: Pointer to the first node.
 *
 * Return: The number of elements in the list.
 */
size_t display_list_elements(const list_t *current_node)
{
	size_t count = 0;

	while (current_node)
	{
		string_puts(convert_number_to_string(current_node->num, 10, 0));
		write_char(':');
		write_char(' ');
		string_puts(current_node->str ? current_node->str : "(nil)");
		string_puts("\n");
		current_node = current_node->next;
		count++;
	}
	return count;
}

/**
 * find_node_by_prefix - Returns a node whose string starts with a given prefix.
 * @start_node: Pointer to list head.
 * @prefix: The prefix to match.
 * @next_char: The next character after the prefix to match (-1 if any character).
 *
 * Return: The matching node or NULL if not found.
 */
list_t *find_node_by_prefix(list_t *start_node, char *prefix, char next_char)
{
	char *found_prefix = NULL;

	while (start_node)
	{
		found_prefix = needle_starts(start_node->str, prefix);
		if (found_prefix && ((next_char == -1) || (*found_prefix == next_char)))
			return start_node;
		start_node = start_node->next;
	}
	return NULL;
}

/**
 * get_node_index - Retrieves the index of a specific node in a linked list.
 * @list_head: Pointer to the list head.
 * @target_node: Pointer to the target node.
 *
 * Return: The index of the node or -1 if the node is not found.
 */
ssize_t get_node_index(list_t *list_head, list_t *target_node)
{
	size_t index = 0;

	while (list_head)
	{
		if (list_head == target_node)
			return index;
		list_head = list_head->next;
		index++;
	}
	return -1;
}
