#include "shell.h"
/**
 * printerror - prints error to stderr
 * @inp: pointer to struct
 * @msg: message to print
 */
void printerror(inp_t *inp, char *msg)
{
	char *words;

	_perror(inp->av[0]);
	_perror(": ");
	words = itos(inp->count);
	_perror(words);
	free(words);
	_perror(": ");
	_perror(inp->tokens[0]);
	if (msg)
		_perror(msg);
	else
		perror("");
}
