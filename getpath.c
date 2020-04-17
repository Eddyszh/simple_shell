#include "shell.h"
/**
 * execmd - executea a command
 * @cmd: command
 * @input: pointer to struct
 * Return: 0 on success 1 otherwise
 */
int execmd(char *cmd, inp_t *input)
{
	pid_t pid;

	if (access(cmd, X_OK) == 0)
	{
		pid = fork();
		if (pid == -1)
			printerror(input, NULL);
		if (pid == 0)
		{
			if (execve(cmd, input->tokens, input->env) == -1)
				printerror(input, NULL);
		}
		else
		{
			wait(&input->status);
			if (WIFEXITED(input->status))
				input->status = WEXITSTATUS(input->status);
			else if (WIFSIGNALED(input->status) &&
					WTERMSIG(input->status) == SIGINT)
				input->status = 130;
			return (0);
		}
		input->status = 127;
		return (1);
	}
	else
	{
		printerror(input, ": Permission denied\n");
		input->status = 126;
	}
	return (0);
}

/**
 * pathfinder - looks for the path
 * @env: eviroment variables
 * Return: pointer to the path, Null on failure
 */
char *pathfinder(char **env)
{
	char *path = "PATH=";
	unsigned int i, j;

	for (i = 0; env[i] != NULL; i++)
	{
		for (j = 0; j < 5; j++)
			if (path[j] != env[i][j])
				break;
		if (j == 5)
			break;
	}
	return (env[i]);
}

/**
 * dirchecker - looks if the command is part of a path
 * @cmd: given command
 * Return: 1 on success, 0 otherwise
 */
int dirchecker(char *cmd)
{
	unsigned int i;

	for (i = 0; cmd[i]; i++)
		if (cmd[i] == '/')
			return (1);
	return (0);
}

/**
 * pathchecker - looks for the command in path
 * @input: pointer to struct
 */
void pathchecker(inp_t *input)
{
	char *dir, *dupl = NULL, *ver = NULL;
	char **tokens;
	unsigned int i = 0, j = 0;

	if (dirchecker(input->tokens[0]))
		j = current_exec(input);
	else
	{
		dir = pathfinder(input->env);
		if (dir != NULL)
		{
			dupl = _strdup(dir + 5);
			tokens = _split(dupl, ":");
			for (i = 0; tokens && tokens[i]; i++, free(ver))
			{
				ver = _strcat(tokens[i], input->tokens[0]);
				if (access(ver, F_OK) == 0)
				{
					j = execmd(ver, input);
					free(ver);
					break;
				}
			}
			free(dupl);
			if (!tokens)
			{
				input->status = 127;
				_exit_(input);
			}
		}
		if (dir == NULL || tokens[i] == NULL)
		{
			printerror(input, ": not found\n");
			input->status = 127;
		}
		free(tokens);
	}
	if (j == 1)
		_exit_(input);
}

/**
 * current_exec - executes the command in the current dir
 * @input: pointer to struct
 * Return: 0 on success, 1 otherwise
 */
int current_exec(inp_t *input)
{
	pid_t pid;

	if (access(input->tokens[0], F_OK) == 0)
	{
		if (access(input->tokens[0], X_OK) == 0)
		{
			pid = fork();
			if (pid == -1)
				printerror(input, NULL);
			if (pid == 0)
			{
				if (execve(input->tokens[0], input->tokens, input->env) == -1)
					printerror(input, NULL);
			}
			else
			{
				wait(&input->status);
				if (WIFEXITED(input->status))
					input->status = WEXITSTATUS(input->status);
				else if (WIFSIGNALED(input->status) &&
						WTERMSIG(input->status) == SIGINT)
					input->status = 130;
				return (0);
			}
			input->status = 127;
			return (1);
		}
		else
		{
			printerror(input, ": Permission denied\n");
			input->status = 126;
		}
		return (0);
	}
	printerror(input, ": not found\n");
	input->status = 127;
	return (0);
}
