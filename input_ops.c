#include "Shell.h"

/**
 * buffer_input - buffers chained commands
 * @info: parameter struct
 * @buffer: address of buffer
 * @length: address of length var
 *
 * Return: bytes read
 */
ssize_t buffer_input(info_t *info, char **buffer, size_t *length)
{
	ssize_t read_bytes = 0;
	size_t length_p = 0;

	if (!*length)
	{
		free(*buffer);
		*buffer = NULL;
		signal(SIGINT, block_ctrl_c);
#if USE_GETLINE
		read_bytes = getline(buffer, &length_p, stdin);
#else
		read_bytes = get_line_input(info, buffer, &length_p);
#endif
		if (read_bytes > 0)
		{
			if ((*buffer)[read_bytes - 1] == '\n')
			{
				(*buffer)[read_bytes - 1] = '\0';
				read_bytes--;
			}
			info->line_count_flag = 1;
			erase_comments(*buffer);
			add_history_entry(info, *buffer, info->hist_count++);

			*length = read_bytes;
			info->command_buffer = buffer;
		}
	}
	return read_bytes;
}

/**
 * get_line_input - gets a line minus the newline
 * @info: parameter struct
 *
 * Return: bytes read
 */
ssize_t get_line_input(info_t *info)
{
	static char *buffer;
	static size_t index_i, index_j, buffer_length;
	ssize_t read_bytes = 0;
	char **buffer_p = &(info->argument), *ptr;

	write_char(BUF_FLUSH);
	read_bytes = buffer_input(info, &buffer, &buffer_length);
	if (read_bytes == -1)
		return -1;
	if (buffer_length)
	{
		index_j = index_i;
		ptr = buffer + index_i;

		monitor_chain(info, buffer, &index_j, index_i, buffer_length);
		while (index_j < buffer_length)
		{
			if (char_del(info, buffer, &index_j))
				break;
			index_j++;
		}

		index_i = index_j + 1;
		if (index_i >= buffer_length)
		{
			index_i = buffer_length = 0;
			info->command_buffer_type = CMD_NORM;
		}

		*buffer_p = ptr;
		return string_len(ptr);
	}

	*buffer_p = buffer;
	return read_bytes;
}

/**
 * read_buffer - reads a buffer
 * @info: parameter struct
 * @buffer: buffer
 * @length: size
 *
 * Return: read_bytes
 */
ssize_t read_buffer(info_t *info, char *buffer, size_t *length)
{
	ssize_t read_bytes = 0;

	if (*length)
		return 0;
	read_bytes = read(info->read_fd, buffer, READ_BUF_SIZE);
	if (read_bytes >= 0)
		*length = read_bytes;
	return read_bytes;
}

/**
 * get_input_line - gets the next line of input from STDIN
 * @info: parameter struct
 * @ptr: address of pointer to buffer, preallocated or NULL
 * @length: size of preallocated ptr buffer if not NULL
 *
 * Return: size
 */
int get_input_line(info_t *info, char **ptr, size_t *length)
{
	static char buffer[READ_BUF_SIZE];
	static size_t index_i, buffer_length;
	size_t k;
	ssize_t read_bytes = 0, size = 0;
	char *p = NULL, *new_p = NULL, *c;

	p = *ptr;
	if (p && length)
		size = *length;
	if (index_i == buffer_length)
		index_i = buffer_length = 0;

	read_bytes = read_buffer(info, buffer, &buffer_length);
	if (read_bytes == -1 || (read_bytes == 0 && buffer_length == 0))
		return -1;

	c = string_char(buffer + index_i, '\n');
	k = c ? 1 + (unsigned int)(c - buffer) : buffer_length;
	new_p = resize_memory_block(p, size, size ? size + k : k + 1);
	if (!new_p)
		return p ? free(p), -1 : -1;

	if (size)
		string_cat(new_p, buffer + index_i, k - index_i);
	else
		copy_string(new_p, buffer + index_i, k - index_i + 1);

	size += k - index_i;
	index_i = k;
	p = new_p;

	if (length)
		*length = size;
	*ptr = p;
	return size;
}

/**
 * block_ctrl_c - blocks ctrl-C
 * @sig_num: the signal number
 *
 * Return: void
 */
void block_ctrl_c(__attribute__((unused)) int sig_num)
{
	string_puts("\n");
	string_puts("$ ");
	write_char(BUF_FLUSH);
}
