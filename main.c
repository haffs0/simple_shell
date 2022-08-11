#include "shell.h"

/**
* main - entry point
* @ac: argument count
* @av: argument lists
* @envp: environment variable
*
* Return: 0
*/
int main(int ac, char **av, char *envp[])
{
	char *line = NULL;
	char **args;
	int status;
	(void) av, (void) envp, (void) status;


	if (ac < 1)
		return (-1);

	signal(SIGINT, handle_signal);

	while (1)
	{
		prompt();
		line = read_line();
		args = split_line(line);
		status = execute(args);
	}
	return (0);
}
