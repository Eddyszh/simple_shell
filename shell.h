#ifndef SHELL_H
#define SHELL_H
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <signal.h>
#include <limits.h>
/**
 * struct inp - get the variables of the input
 * @buf: buffer
 * @tokens: line arguments
 * @av: argument passed from shell
 * @cmd: commands
 * @env: eviroment variables
 * @status: exit
 * @count: get the count of commands
 */
typedef struct inp
{
	char *buf;
	char **tokens;
	char **av;
	char **cmd;
	char **env;
	int status;
	unsigned int count;
} inp_t;
/**
 * struct builtins - get the function for builtins
 * @name: name of the builtin
 * @f: functoin of the builtin
 */
typedef struct builtins
{
	char *name;
	void (*f)(inp_t *);
} built_t;
unsigned int strmtch(char c, const char *str);
char *_strtok(char *str, const char *delim);
int init(char **args);
char *get_line(void);
char **_split(char *av, char *del);
unsigned int _strlen(char *s);
char *itos(unsigned int i);
ssize_t _puts(char *s);
ssize_t _perror(char *s);
char **_realloc(char **ptr, size_t *len);
void printerror(inp_t *inp, char *msg);
void sign_handler(int sign_handler);
int execmd(char *cmd, inp_t *input);
char *pathfinder(char **env);
int dirchecker(char *cmd);
void pathchecker(inp_t *input);
int current_exec(inp_t *input);
char *_strdup(char *dupl);
char *_strcat(char *s1, char *s2);
int _strcmp(char *s1, char *s2);
void (*builtin(inp_t *input))(inp_t *input);
void _env(inp_t *input);
char **init_env(char **env);
int _atoi(char *str);
void _exit_(inp_t *inputs);
void free_environ(char **environ);
#endif