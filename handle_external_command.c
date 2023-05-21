#include "shell.h"

/**
 * handle_external_command - Handle the execution of external commands
 * @line: The line input
 * @args: The parsed arguments
 *
 * Description: Executes external commands using execute_command.
 *              Frees the allocated memory, exits the shell if execution fails
 */
void handle_external_command(char *line, char **args)
{
	int status = execute_command(args);

	free(line);
	free_args(args);

	if (!status)
		exit(0);
}
