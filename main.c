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

	do {
		printf("$ ");
		line = read_line();

		if (line == NULL)
			break;

		args = parse_line(line);

		if (args[0] == NULL)
		{
			free(line);
			free_args(args);
			continue;
		}

		if (strcmp(args[0], "exit") == 0)
		{
			handle_exit(line, args);
		}
		else if (strcmp(args[0], "env") == 0)
		{
			handle_env();
		}
		else
		{
			handle_external_command(line, args);
		}
	} while (1);

	return (0);
}
