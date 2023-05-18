#include "shell.h"

/**
 * parse_line - Parse a line into individual arguments
 * @line: The line to parse
 *
 * Return: An array of arguments
 */
char **parse_line(char *line)
{
	const char *delimiters = " \t\r\n\v\f";
	char **args = NULL;
	char *token;
	int i = 0;

	token = strtok(line, delimiters);
	while (token != NULL)
	{
		args = realloc(args, (i + 1) * sizeof(char *));
		if (args == NULL)
		{
		perror("realloc");
		exit(EXIT_FAILURE);
		}

		args[i] = _strdup(token);
		token = strtok(NULL, delimiters);
		i++;
	}

	args = realloc(args, (i + 1) * sizeof(char *));
	if (args == NULL)
	{
		perror("realloc");
		exit(EXIT_FAILURE);
	}
	args[i] = NULL;

	return (args);
}
