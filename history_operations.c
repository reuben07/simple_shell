#include "Shell.h"

/**
 * history_file_path - Get the path to the history file.
 * @info: Parameter struct.
 *
 * Return: Allocated string containing the history file path.
 */
char *history_file_path(info_t *info)
{
	char *home_dir, *path;

	home_dir = _environment_variable(info, "HOME=");
	if (!home_dir)
		return (NULL);
	path = malloc(sizeof(char) * (string_len(home_dir) + string_len(HIST_FILENAME) + 2));
	if (!path)
		return (NULL);
	path[0] = 0;
	string_cpy(path, home_dir);
	string_conc(path, "/");
	string_conc(path, HIST_FILENAME);
	return (path);
}

/**
 * save_history - Save the history list to a file.
 * @info: Parameter struct.
 *
 * Return: 1 on success, else -1.
 */
int save_history(info_t *info)
{
	ssize_t file_descriptor;
	char *file_name = get_history_file_path(info);
	list_t *curr_node = NULL;

	if (!file_name)
		return (-1);

	file_descriptor = open(file_name, O_CREAT | O_TRUNC | O_RDWR, 0644);
	free(file_name);
	if (file_descriptor == -1)
		return (-1);
	for (curr_node = info->history; curr_node; curr_node = curr_node->next)
	{
		_write_string_to_fd(curr_node->str, file_descriptor);
		_write_to_fd('\n', file_descriptor);
	}
	_write_to_fd(BUF_FLUSH, file_descriptor);
	close(file_descriptor);
	return (1);
}

/**
 * load_history - Load history from a file.
 * @info: Parameter struct.
 *
 * Return: hist_count on success, 0 otherwise.
 */
int load_history(info_t *info)
{
	int i, last = 0, line_count = 0;
	ssize_t file_descriptor, read_length, file_size = 0;
	struct stat file_stat;
	char *buffer = NULL, *file_name = get_history_file_path(info);

	if (!file_name)
		return (0);

	file_descriptor = open(file_name, O_RDONLY);
	free(file_name);
	if (file_descriptor == -1)
		return (0);
	if (!fstat(file_descriptor, &file_stat))
		file_size = file_stat.st_size;
	if (file_size < 2)
		return (0);
	buffer = malloc(sizeof(char) * (file_size + 1));
	if (!buffer)
		return (0);
	read_length = read(file_descriptor, buffer, file_size);
	buffer[file_size] = 0;
	if (read_length <= 0)
		return (free(buffer), 0);
	close(file_descriptor);
	for (i = 0; i < file_size; i++)
		if (buffer[i] == '\n')
		{
			buffer[i] = 0;
			add_history_entry(info, buffer + last, line_count++);
			last = i + 1;
		}
	if (last != i)
		add_history_entry(info, buffer + last, line_count++);
	free(buffer);
	info->hist_count = line_count;
	while (info->hist_count-- >= HIST_MAX)
		remove_node_at_index(&(info->history), 0);
	update_history_line_numbers(info);
	return (info->hist_count);
}

/**
 * history_entry - Add a history entry to the linked list.
 * @info: Parameter struct.
 * @buffer: Buffer containing the history entry.
 * @line_count: The history line count (hist_count).
 *
 * Return: Always 0.
 */
int history_entry(info_t *info, char *buffer, int line_count)
{
	list_t *node = NULL;

	if (info->history)
		node = info->history;
	append_node(&node, buffer, line_count);

	if (!info->history)
		info->history = node;
	return (0);
}

/**
 * renumber_history_line - Renumber the history linked
 * list after changes.
 * @info: Parameter struct.
 *
 * Return: The new hist_count.
 */
int renumber_history_line(info_t *info)
{
	list_t *node = info->history;
	int i = 0;

	while (node)
	{
		node->num = i++;
		node = node->next;
	}
	return (info->hist_count = i);
}
