/**
 * split_line - split line into tokens
 * @line: line to be split
 * Return: a pointer
 */

char **split_line(char *line)
{
	int bufsize = TOK_BUFSIZE, position = 0, toklen;
	char **tokens = malloc(bufsize * sizeof(char));
	char *token, *token_copy;

	if (!tokens)
		exit(EXIT_FAILURE);

	token = strtok(line, TOK_DELIM);
	while (token != NULL)
	{
		toklen = _strlen(token);
		token_copy = malloc((toklen + 1) * sizeof(char));
		token_copy = _strdup(token);

		tokens[position] = token_copy;
		position++;

		token = strtok(NULL, TOK_DELIM);
	}
	tokens[position] = NULL;
	return (tokens);
}
