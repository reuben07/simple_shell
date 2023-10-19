#include "Shell.h"

/**
 * add_to_start - Adds a node to the beginning of the list.
 * @list_head: Address of the pointer to the head node.
 * @data: Data field of the node.
 * @index: Node index used by history.
 *
 * Return: The size of the list.
 */
list_t *add_to_start(list_t **list_head, const char *data, int index)
{
	list_t *new_node;

	if (!list_head)
		return (NULL);

	new_node = malloc(sizeof(list_t));
	if (!new_node)
		return (NULL);

	fill_memory((void *)new_node, 0, sizeof(list_t));
	new_node->index = index;

	if (data)
	{
		new_node->data = string_dpl(data);
		if (!new_node->data)
		{
			free(new_node);
			return (NULL);
		}
	}

	new_node->next = *list_head;
	*list_head = new_node;
	return (new_node);
}

/**
 * append_to_end - Adds a node to the end of the list.
 * @list_head: Address of the pointer to the head node.
 * @data: Data field of the node.
 * @index: Node index used by history.
 *
 * Return: The size of the list.
 */
list_t *append_to_end(list_t **list_head, const char *data, int index)
{
	list_t *new_node, *node;

	if (!list_head)
		return (NULL);

	node = *list_head;
	new_node = malloc(sizeof(list_t));
	if (!new_node)
		return (NULL);

	fill_memory((void *)new_node, 0, sizeof(list_t));
	new_node->index = index;

	if (data)
	{
		new_node->data = string_dpl(data);
		if (!new_node->data)
		{
			free(new_node);
			return (NULL);
		}
	}

	if (node)
	{
		while (node->next)
			node = node->next;
		node->next = new_node;
	}
	else
		*list_head = new_node;

	return (new_node);
}

/**
 * print_data_list - Prints only the data element of a list_t linked list.
 * @head: Pointer to the first node.
 *
 * Return: The size of the list.
 */
size_t print_data_list(const list_t *head)
{
	size_t size = 0;

	while (head)
	{
		string_puts(head->data ? head->data : "(nil)");
		string_puts("\n");
		head = head->next;
		size++;
	}

	return (size);
}

/**
 * remove_node_at_position - Deletes a node at the given position.
 * @list_head: Address of the pointer to the head node.
 * @position: Position of the node to delete.
 *
 * Return: 1 on success, 0 on failure.
 */
int remove_node_at_position(list_t **list_head, unsigned int position)
{
	list_t *node, *prev_node;
	unsigned int count = 0;

	if (!list_head || !*list_head)
		return (0);

	if (!position)
	{
		node = *list_head;
		*list_head = (*list_head)->next;
		free(node->data);
		free(node);
		return (1);
	}

	node = *list_head;
	while (node)
	{
		if (count == position)
		{
			prev_node->next = node->next;
			free(node->data);
			free(node);
			return (1);
		}

		count++;
		prev_node = node;
		node = node->next;
	}

	return (0);
}

/**
 * clear_data_list - Frees all nodes of a list.
 * @list_head_ptr: Address of the pointer to the head node.
 *
 * Return: Void.
 */
void clear_data_list(list_t **list_head_ptr)
{
	list_t *node, *next_node, *head;

	if (!list_head_ptr || !*list_head_ptr)
		return;

	head = *list_head_ptr;
	node = head;

	while (node)
	{
		next_node = node->next;
		free(node->data);
		free(node);
		node = next_node;
	}

	*list_head_ptr = NULL;
}
