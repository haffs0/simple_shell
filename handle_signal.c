#include "shell.h"

/**
 *  handle_signal- it keeps track is interactive mode
 *  @num: the signal number
 *  Return: nothing
 */

void handle_signal(int num)
{
	(void)m;
	write(STDERR_FILENO, "\n", 1);
	write(STDERR_FILENO, "$ ", 2);
}
