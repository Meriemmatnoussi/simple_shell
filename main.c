#include "shell.h"

/**
 * handle_exit - Handle the "exit" built-in command
 * @line: The line input
 * @args: The parsed arguments
 *
 * Description: Frees the allocated memory and exits the shell.
 */
void handle_exit(char *line, char **args)
{
	free(line);
	free_args(args);
	exit(0);
}

/**
 * execute_env - Print the current environment variables
 */
void execute_env(void)
{
	int i = 0;

	while (environ[i] != NULL)
	{
		printf("%s\n", environ[i]);
		i++;
	}
}

/**
 * handle_external_command - Handle the execution of external commands
 * @line: The line input
 * @args: The parsed arguments
 *
 * Description: Executes external commands using execute_command.
 *              Frees the allocated memory, exits the shell if execution fails.
 */
void handle_external_command(char *line, char **args)
{
	int status = execute_command(args);

	free(line);
	free_args(args);

	if (!status)
		exit(0);
}

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
			execute_env();
		}
		else
		{
			handle_external_command(line, args);
		}
	} while (1);

	return (0);
}
