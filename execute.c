#include "shell.h"

/**
 * execute - execute the args
 * @args: list of args
 * Return: 1 on success
 */

int execute(char **args)
{
	if (own_cmd_handler(args))
	{
		return (0);
	}
	else if (**args == '/')
	{
		return (launch(args));
	}
	return (0);
}
