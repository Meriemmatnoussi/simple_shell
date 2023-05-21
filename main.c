#include "shell.h"

/**
 * main - Simple UNIX command line interpreter
 *
 * Return: Always 0
 */
int main(void)
{
	char *line;
	char **args;
	int status;

	do {
		printf("$ ");
		line = read_line();
		args = parse_line(line);

		if (args[0] == NULL)
			continue;

		if (strcmp(args[0], "exit") == 0)
		{
			free(line);
			free_args(args);
			exit(0);
		}

		if (strcmp(args[0], "env") == 0)
		{
			execute_env();
			free(line);
			free_args(args);
			continue;
		}

		status = execute_command(args);

		free(line);
		free_args(args);
	} while (status);

	return (0);
}
