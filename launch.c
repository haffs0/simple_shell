#include "shell.h"

/**
 * launch - launches program
 * @args: argument
 *
 * Return: 0
 */
int launch(char **args)
{
	char **env = environ;
	int status;

	pid_t pid = fork();

	if (pid == -1)
	{
		return (0);
	}
	else if (pid == 0)
	{
		execve(args[0], args, env)
		exit(0);
	}
	else
	{
		wait(&status);
		return (1);
	}
}
