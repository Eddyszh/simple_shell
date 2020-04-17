#include "shell.h"
/**
 * builtin - verifies if the command is a builtin
 * @input: pointer to struc
 * Return: pointer to function
 */
void (*builtin(inp_t *input))(inp_t *input)
{
	unsigned int i;
	built_t verify[] = {
		{"exit", _exit_},
		{"env", _env},
		{NULL, NULL}
	};
	for (i = 0; verify[i].f != NULL; i++)
	{
		if (_strcmp(input->tokens[0], verify[i].name) == 0)
			break;
	}
	if (verify[i].f != NULL)
		verify[i].f(input);
	return (verify[i].f);
}
/**
 * _env - print the enviroment
 * @input: pointer to struct
 */
void _env(inp_t *input)
{
	unsigned int i;

	for (i = 0; input->env[i]; i++)
	{
		_puts(input->env[i]);
		_puts("\n");
	}
	input->status = 0;
}
/**
 * init_env - initializes a new enviroment
 * @env: eviromen passed to main
 * Return: pointer to new enviroment
 */
char **init_env(char **env)
{
	char **new = NULL;
	size_t i = 0;

	while (env[i] != NULL)
		i++;
	new = malloc(sizeof(char *) * (i + 1));
	if (!new)
	{
		perror("Error");
		exit(1);
	}
	for (i = 0; env[i] != NULL; i++)
		new[i] = _strdup(env[i]);
	new[i] = NULL;
	return (new);
}
/**
 * _exit_ - terminates the shell
 * @input: pointer to struc
 */
void _exit_(inp_t *input)
{
	int status;

	if (_strcmp(input->tokens[0], "exit") == 0 &&
	    input->tokens[1] != NULL)
	{
		status = _atoi(input->tokens[1]);
		if (status == -1)
		{
			input->status = 2;
			printerror(input, ": Illegal number: ");
			_perror(input->tokens[1]);
			_perror("\n");
			free(input->cmd);
			input->cmd = NULL;
			return;
		}
		input->status = status;
	}
	free(input->buf);
	free(input->tokens);
	free(input->cmd);
	free_environ(input->env);
	exit(input->status);
}
/**
 * free_environ - frees the shell's enviroment
 * @env: given enviroment
 */
void free_environ(char **env)
{
	unsigned int i;

	for (i = 0; env[i] != NULL; i++)
		free(env[i]);
	free(env);
}
