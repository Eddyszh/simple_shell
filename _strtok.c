#include "shell.h"
/**
 * strmtch - compares characters of strings
 * @c: char to compare
 * @str: string to compare
 * Return: 1 on success, 0 otherwise
 */
unsigned int strmtch(char c, const char *str)
{
	unsigned int i;

	for (i = 0; str[i] != '\0'; i++)
		if (c == str[i])
			return (1);
	return (0);
}

/**
 * _strtok - its behaviour is like the normal strtok
 * @str: string
 * @delim: delimiter
 * Return: pointer to the next token or null otherwise
 */
char *_strtok(char *str, const char *delim)
{
	static char *n;
	static char *token;
	unsigned int i;

	if (str != NULL)
		n = str;
	token = n;
	if (!token)
		return (NULL);
	for (i = 0; n[i] != '\0'; i++)
	{
		if (strmtch(n[i], delim) == 0)
			break;
	}
	if (n[i] == '\0' || n[i] == '#')
	{
		n = NULL;
		return (NULL);
	}
	token = n + i;
	n = token;
	for (i = 0; n[i] != '\0'; i++)
		if (strmtch(n[i], delim) == 1)
			break;
	if (n[i] == '\0')
		n = NULL;
	else
	{
		n[i] = '\0';
		n += i + 1;
		if (*n == '\0')
			n = NULL;
	}
	return (token);
}
