#include "Shell.h"

/**
 * reallocate_memory - Reallocates a block of memory.
 * @old_ptr: Pointer to the previously allocated memory.
 * @old_size: Size of the currently allocated memory block.
 * @new_size: Size of the new memory block.
 *
 * This function reallocates a block of memory. If old_ptr is NULL, it behaves
 * like malloc and allocates a new block of memory of the specified new_size.
 * If new_size is 0, it behaves like free and releases the memory pointed to by old_ptr.
 *
 * Return: Pointer to the newly reallocated memory, or NULL on failure.
 */
void *reallocate_memory(void *old_ptr, size_t old_size, size_t new_size)
{
	char *new_ptr;

	if (!old_ptr)
		return malloc(new_size);

	if (!new_size)
		return (free(old_ptr), NULL);

	if (new_size == old_size)
		return old_ptr;

	new_ptr = malloc(new_size);
	if (!new_ptr)
		return NULL;

	old_size = old_size < new_size ? old_size : new_size;
	while (old_size--)
		new_ptr[old_size] = ((char *)old_ptr)[old_size];

	free(old_ptr);
	return new_ptr;
}

/**
 * fill_memory_block - Fills a block of memory with a specified value.
 * @block: Pointer to the memory block to be filled.
 * @value: The value to fill the memory with.
 * @size: Number of bytes to fill.
 *
 * This function fills a block of memory pointed to by block with the value value for size bytes.
 *
 * Return: The pointer to the filled memory block.
 */
char *fill_memory_block(char *block, char value, size_t size)
{
	size_t i;

	for (i = 0; i < size; i++)
		block[i] = value;
	return block;
}

/**
 * free_string_array - Frees a block of memory allocated for a string array.
 * @str_array: Pointer to the string array to be freed.
 *
 * This function frees a block of memory allocated for an array of strings.
 */
void free_string_array(char **str_array)
{
	char **ptr = str_array;

	if (!str_array)
		return;

	while (*str_array)
		free(*str_array++);

	free(ptr);
}
