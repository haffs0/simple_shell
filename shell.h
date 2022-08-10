#ifndef _SHELL_H_
#define _SHELL_H_

#include <sys/wait.h>
#include <unistd.h>
#include <stdlib.h>
#include <stdio.h>
#include <stdarg.h> 
#include <string.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <time.h>
#include <stdbool.h>

#define TOK_BUFSIZE 64
#define TOK_DELIM " :\t\r\n\a"

int _cd(char **args);
int _help(char **args);
int exit_cmd(char **args);
char *read_line(void);


/* environment variables */
extern char **environ;
extern __sighandler_t signal(int __sig, __sighandler_t __handler);

/* handle built ins */
void print_env(void);
void prompt(void);
void handle_signal(int m);

/* string handlers */
int _strcmp(char *s1, char *s2);
int _strlen(char *s);
int _strncmp(char *s1, char *s2, int n);
char *_strdup(char *s);
char *_strchr(char *s, char c);

void executuion(char *cp, char **cmd);
char *find_path(void);
int main(int ac, char **av, char *envp[]);
char **split_line(char *line);
int own_cmd_handler(char **parsed);
int execute(char **args);
void handle_signal(int num);


/* helper function for efficient free */
void free_buffers(char **buf);

/* about builtin */
struct builtin
{
	char *env;
	char *exit;
} builtin;

/* about info */
struct info
{
	int final_exit;
	int ln_count;
} info;

/* about flags */
struct flags
{
	bool interactive;
} flags;

#endif /* SHELL_H */
