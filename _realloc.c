#include "shell.h"
/**
 * _realloc - reallocates memory
 * @ptr: pointer to the old size
 * @len: lenght of the pointer
 * Return: pointer to new memory allocation
 */
char **_realloc(char **ptr, size_t *len)
{
	char **new;
	size_t i;

	new = malloc(sizeof(char *) * ((*len) + 10));
	if (!new)
	{
		free(new);
		return (NULL);
	}
	for (i = 0; i < (*len); i++)
		new[i] = ptr[i];
	*len += 10;
	free(ptr);
	return (new);
}
