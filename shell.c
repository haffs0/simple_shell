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

	if (ac < 1)
		return (-1);

	signal(SIGINT, handle_signal);

	while (1)
	{
		free_buffers(args);
		prompt_user();
		line = read_line();
		args = split_line(line);
		status = execute(args);
	}
	if (status < 0 && flags.interactive)
		write(STDERR_FILENO, "\n", 1);
	free(line);
	return (0);
}
