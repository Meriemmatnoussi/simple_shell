#include "shell.h"

/**
 * handle_env - Handle the "env" built-in command
 *
 * Description: Prints the environment variables using execute_env.
 */
void handle_env(void)
{
	execute_env();
}
