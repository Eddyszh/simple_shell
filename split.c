#include "shell.h"
/**
 * _split - splits commands into tokens
 * @av: arguments passed
 * @del: delimiter
 * Return: token to the next
 */
char **_split(char *av, char *del)
{
	char **tokens = NULL;
	size_t i = 0, count = 10;

	if (!av)
		return (NULL);
	tokens = malloc(sizeof(char *) * count);
	if (!tokens)
	{
		perror("Error");
		return (NULL);
	}
	while ((tokens[i] = _strtok(av, del)) != NULL)
	{
		i++;
		if (i == count)
		{
			tokens = _realloc(tokens, &count);
			if (!tokens)
			{
				perror("Error");
				return (NULL);
			}
		}
		av = NULL;
	}
	return (tokens);
}
