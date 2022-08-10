#ifndef _SHELL_H_
#define _SHELL_H_

#include <sys/wait.h>
#include <unistd.h>
#include <stdlib.h>
#include <stdio.h>
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

/* string function */
int _strlen(const char *string)

/* environment variables */
extern char **environ;
extern __sighandler_t signal(int__sig, __sighandler_t__handler);

/* handle built ins */
void print_env(void);

/* string handlers */
int_strcmp(char *s1, char *s2);
int_strlen(char *s)
int_strncmp(char *s1, char *s2, int n);
char *_strdup(char *s);
char *_strchr(char *s, char c);

void executuion(char *cp, char **cmd);
char *find_path(void);

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
