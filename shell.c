#include "shell.h"
#define TOKENS " \n\t\r\a"
/**
 * main - initilizes the shell function
 * @ac: number of command arguments
 * @av: array of arguments
 * @env: eviroment path
 */
int main(int ac, char **av, char **env) 
{
	size_t buf = 0;
	unsigned int i, interac = 0;
	inp_t input = {NULL, NULL, NULL, NULL, NULL, 0, 0};

	(void)ac;
	input.av = av;
	input.env = init_env(env);
	signal(SIGINT, sign_handler);
	if (!isatty(STDIN_FILENO))
		interac = 1;
	if (interac == 0)
		_puts("$ ");
	while (getline(&(input.buf), &buf, stdin) != -1)
	{
		input.count++;
		input.cmd = _split(input.buf, ";");
		for (i = 0; input.cmd && input.cmd[i] != NULL; i++)
		{
			input.tokens = _split(input.cmd[i], TOKENS);
			if (input.tokens && input.tokens[0])
				if (builtin(&input) == NULL)
					pathchecker(&input);
			free(input.tokens);
		}
		free(input.buf);
		free(input.cmd);
		if (interac == 0)
			_puts("$ ");
		input.buf = NULL;
	}
	if (interac == 0)
		_puts("\n");
	free_environ(input.env);
	free(input.buf);
	exit(input.status);
}

/**
 * sign_handler - handles the ctrl + c sign
 * @sign_handler: int
 */
void sign_handler(int sign_handler)
{
	(void)sign_handler;
	_puts("\n$ ");
}
