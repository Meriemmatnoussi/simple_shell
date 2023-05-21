#include "shell.h"

/**
 * read_line - Read a line from stdin
 *
 * Return: The line read from stdin, or NULL on Ctrl+D (end of file)
 */
char *read_line(void)
{
	char *line = NULL;
	size_t bufsize = 0;
	ssize_t chars_read;

	chars_read = getline(&line, &bufsize, stdin);
	if (chars_read == -1)
	{
		if (feof(stdin))
		{
			free(line);
			return (NULL);
		}
		else
		{
			perror("getline");
			exit(EXIT_FAILURE);
		}
	}

	return (line);
}
