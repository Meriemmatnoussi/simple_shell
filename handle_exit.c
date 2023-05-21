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
