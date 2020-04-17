#include "shell.h"
/**
 * _strdup - duplicates a string
 * @dupl: strint to duplicate
 * Return: pointer to the duplicate
 */
char *_strdup(char *dupl)
{
	char *new;
	unsigned int i = 0, j;

	if (!dupl)
		return (NULL);
	while (dupl[i])
		i++;
	new = malloc(sizeof(char) * (i + 1));
	for (j = 0; j <= i; j++)
		new[j] = dupl[j];
	return (new);
}
/**
 * _strcat - concatenate two strings
 * @s1: string to concatenate
 * @s2: string to concatenate
 * Return: pointer to new allocated space, NULL otherwise
 */
char *_strcat(char *s1, char *s2)
{
	char *s;
	int len1 = 0, len2 = 0, i, j;

	if (s1 == NULL)
		s1 = "";
	while (s1[len1] != '\0')
		len1++;
	if (s2 == NULL)
		s2 = "";
	while (s2[len2] != '\0')
		len2++;
	s = malloc(sizeof(char) * (len1 + len2) + 2);
	if (s == NULL)
		return (NULL);
	for (i = 0; i < len1; i++)
		s[i] = s1[i];
	s[i] = '/';
	for (j = 0; j < len2; j++)
		s[i + 1 + j] = s2[j];
	s[len1 + len2 + 1] = '\0';
	return (s);
}
/**
 * _strcmp - compares two string
 * @s1: string to compare
 * @s2: string to compare
 * Return: 0 on success
 */
int _strcmp(char *s1, char *s2)
{
	int i = 0;

	while (s1[i] == s2[i])
	{
		if (s1[i] == '\0')
			return (0);
		i++;
	}
	return (s1[i] - s2[i]);
}
/**
 * _atoi - converts char to int
 * @str: string to convert
 * Return: int value or 1 on failure
 */
int _atoi(char *str)
{
	unsigned int i, digits;
	int num = 0, max;

	max = INT_MAX;
	for (digits = 0; max != 0; digits++)
		max /= 10;
	for (i = 0; str[i] != '\0' && i < digits; i++)
	{
		num *= 10;
		if (str[i] < '0' || str[i] > '9')
			return (-1);
		if ((i == digits - 1) && (str[i] - '0' > INT_MAX % 10))
			return (-1);
		num += str[i] - '0';
		if ((i == digits - 2) && (str[i + 1] != '\0') && (num > INT_MAX / 10))
			return (-1);
	}
	if (i > digits)
		return (-1);
	return (num);

}
