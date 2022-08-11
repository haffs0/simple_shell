#include "shell.h"
/**
 * own_cmd_handler - handles cmd
 * @parsed: parser
 * Return: 0
 */

int own_cmd_handler(char **parsed)
{
	int NoOfOwnCmds = 2, i, switchOwnArg = 0;
	char *ListOfOwnCmds[NoOfOwnCmds];

	ListOfOwnCmds[0] = "exit";
	ListOfOwnCmds[1] = "env";

	for (i = 0; i < NoOfOwnCmds; i++)
	{
		if (_strcmp(parsed[0], ListOfOwnCmds[i]) == 0)
		{
			switchOwnArg = i + 1;
			break;
		}
	}

	switch (switchOwnArg)
	{
		case 1:
			exit(0);
		case 2:
			print_env();
			return (1);
		default:
			break;
	}

	return (0);
}
