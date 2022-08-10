#include "shell.h"

char *builtin_cmd[] = {
    "cd",
    "help",
    "exit"
};


int (*builtin_cmd_func[]) (char **) = {
    &_cd,
    &_help,
    &exit_cmd
};

int num_builtins() {
    return sizeof(builtin_cmd) / sizeof(char *);
}

/**
 * _cd - change directory
 * @args: parameters
 * Return: 1 on success
 */
 
int _cd(char **args)
{
    if (args[1] == NULL) 
    {
        fprintf(stderr, "lsh: expected argument to \"cd\"\n");
    } 
    else 
    {
        if (chdir(args[1]) != 0)
        {
            perror("lsh");
        }
    }
    return 1;
}

/**
 * _help - Builtin command: help
 * @args: lists of args
 * Return: 1 on success
 */

int _help(char **args)
{
    int i;

    printf("Type program names and arguments, and hit enter.\n");
    printf("The following are built in:\n");

    for (i = 0; i < num_builtins(); i++) {
        printf("  %s\n", builtin_cmd[i]);
    }

    printf("Use the man command for information on other programs.\n");
    return 1;
}

/**
 * exit_cmd - Builtin command: exit
 * @args: lists of args
 * Return: 0 always
 */

int exit_cmd(char **args)
{
    return 0;
}

/**
 * launch_cmd - executed the system command
 * @args: lists of args
 * Return: 1 on success
 */
int launch_cmd(char** args)
{

    pid_t pid = fork();

    if (pid == -1)
    {
        printf("\nFailed forking child..");
        return (0);
    }
    else if (pid == 0)
    {
        if (execve(args[0], args, NULL) < 0)
        {
            printf("\nCould not execute command..");
        }
        exit(0);
    }
    else
    {
        wait(NULL);
        return(1);
    }
}

/**
 * execute - execute builtin commands and launch program
 * @args: lists of args
 * Return: 1 on success
 */

int execute(char **args)
{
    int i;
    if (args[0] == NULL)
    {
        return (1);
    }

    for (i = 0; i < num_builtins(); i++)
    {
        if (strcmp(args[0], builtin_cmd[i]) == 0)
        {
            return (*builtin_cmd_func[i])(args);
        }
    }

    return launch_cmd(args);
}

/**
 * read_line - read line of input from stdin
 * Return: a line
 */

char *read_line(void)
{
    char *line = NULL;
    ssize_t bufsize = 0;

    if (getline(&line, &bufsize, stdin) == -1)
    {
        if (feof(stdin))
        {
            exit(EXIT_SUCCESS);
        }
        else
        {
            perror("readline");
            exit(EXIT_FAILURE);
        }
    }
    return (line);
}

/**
 * split_line - split line into tokens
 * @line: line to be split
 * Return: a pointer
 */

char **split_line(char *line)
{
    int bufsize = TOK_BUFSIZE, position = 0;
    char **tokens = malloc(bufsize * sizeof(char*));
    char *token;

    if (!tokens)
    {
        fprintf(stderr, "lsh: allocation error\n");
        exit(EXIT_FAILURE);
    }

    token = strtok(line, TOK_DELIM);
    while (token != NULL)
    {
        tokens[position] = token;
        position++;

        if (position >= bufsize)
        {
            bufsize += TOK_BUFSIZE;
            tokens = realloc(tokens, bufsize * sizeof(char*));
            if (!tokens)
            {
                fprintf(stderr, "lsh: allocation error\n");
                exit(EXIT_FAILURE);
            }
        }

        token = strtok(NULL, TOK_DELIM);
    }
    tokens[position] = NULL;
    return (tokens);
}

/**
 * exec_args_piped - execute command with pipe
 * @parsed: first parameters before pipe
 * @parsedpipe: second parameters after pipe
 * Return: 1 on success
 */

int exec_args_piped(char** parsed, char** parsedpipe)
{
	int pipefd[2];
	pid_t p1, p2;

	if (pipe(pipefd) < 0)
    {
		printf("\nPipe could not be initialized");
		return (0);
	}

	p1 = fork();

	if (p1 < 0)
    {
		printf("\nCould not fork");
		return (0);
	}

	if (p1 == 0)
    {
		close(pipefd[0]);
		dup2(pipefd[1], STDOUT_FILENO);
		close(pipefd[1]);

		if (execve(parsed[0], parsed, NULL) < 0)
        {
			printf("\nCould not execute command 1..");
			exit(0);
		}
	}
    else
    {
		p2 = fork();

		if (p2 < 0)
        {
			printf("\nCould not fork");
			return (0);
		}

		if (p2 == 0)
        {
			close(pipefd[1]);
			dup2(pipefd[0], STDIN_FILENO);
			close(pipefd[0]);
			if (execve(parsedpipe[0], parsedpipe, NULL) < 0)
            {
				printf("\nCould not execute command 2..");
				exit(0);
			}
		}
        else
        {
			wait(NULL);
            return (1);
		}
	}
}

/**
 * parse_pipe - check if a line contain a pipe
 * @str: the line
 * @strpiped: where to store line before pipe and after
 * Return: 1 on success
 */

int parse_pipe(char* str, char** strpiped)
{
	int i;
	for (i = 0; i < 2; i++)
    {
		strpiped[i] = strsep(&str, "|");
		if (strpiped[i] == NULL)
			break;
	}

	if (strpiped[1] == NULL)
		return 0;
	else
        return 1;
}


/**
 * main - entry point
 * @argc: number of args
 * @argv: lists of args
 * Return: 0 on success
 */

int main(int argc, char **argv)
{
    char *line, *line_copy;
    char **args, **args1, **args2;
    int status, piped = 0;
    char* strpiped[2];

    do
    {
        printf("%s ", "$");

        line = read_line();
        line_copy = strdup(line);
        piped = parse_pipe(line, strpiped);

        if (piped)
        {
            args1 = split_line(strpiped[0]);
            args2 = split_line(strpiped[1]);

        }
        else
        {
            args = split_line(line_copy);
        }

        piped = piped + 1;

        if (piped == 1)
            status = execute(args);

        if (piped == 2)
            status = exec_args_piped(args1, args2);

        piped = 0;

        free(line);
    } while (status);

    return (EXIT_SUCCESS);
}

