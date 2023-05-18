#include "shell.h"

/**
 * free_args - Free the memory allocated for an array of arguments
 * @args: The array of arguments
 */
void free_args(char **args)
{
	int i = 0;

	while (args[i] != NULL)
	{
		free(args[i]);
		i++;
	}
	free(args);
}
