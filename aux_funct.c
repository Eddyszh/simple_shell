#include "shell.h"
/**
 * _strlen - gets the lenght of string
 * @s: string to be count
 * Return: the lenght of the string
 */
unsigned int _strlen(char *s)
{
	unsigned int i = 0;

	while (s[i])
		i++;
	return (i);
}

/**
 * itos - converts int to string
 * @i: unsigned int
 * Return: converted string
 */
char *itos(unsigned int i)
{
	char *s;
	unsigned int t, d;

	t = i;
	for (d = 0; t != 0; d++)
		t /= 10;
	s = malloc(sizeof(char) * (d + 1));
	if (!s)
	{
		perror("Error");
		exit(127);
	}
	s[d] = '\0';
	for (--d; i; --d)
	{
		s[d] = (i % 10) + '0';
		i /= 10;
	}
	return (s);
}

/**
 * _puts - prints to the stdout
 * @s: string recived
 * Return: count of numbers printed
 */
ssize_t _puts(char *s)
{
	ssize_t in, out;

	in = _strlen(s);
	out = write(STDOUT_FILENO, s, in);
	if (in != out)
	{
		perror("Error");
		return (-1);
	}
	return (out);
}

/**
 * _perror - prints error to stderr
 * @s: string recived
 * Return: count of numbers printed
 */
ssize_t _perror(char *s)
{
	unsigned int in, out;

	in = _strlen(s);
	out = write(STDERR_FILENO, s, in);
	if (in != out)
	{
		perror("Error");
		return (-1);
	}
	return (out);
}
