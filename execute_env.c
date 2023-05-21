#include "shell.h"

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
