#include "Shell.h"

/**
 * release_memory - Frees a memory block and sets the pointer to NULL.
 * @memory_ptr: A pointer to a memory block.
 *
 * This function frees the memory pointed to by 'memory_ptr' and sets it to NULL.
 * It provides a safe way to release dynamically allocated memory, preventing memory leaks.
 *
 * @memory_ptr: A pointer to a memory block.
 *
 * Return: 1 if memory was freed, otherwise 0.
 */
int release_memory(void **memory_ptr)
{
	if (memory_ptr && *memory_ptr)
	{
		free(*memory_ptr);
		*memory_ptr = NULL;
		return 1;
	}
	return 0;
}
