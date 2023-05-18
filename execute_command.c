#include "shell.h"

/**
 * execute_command - Execute a command with arguments
 * @args: The arguments of the command
 *
 * Return: 1 if successful, 0 otherwise
 */
int execute_command(char **args)
{
	pid_t pid;
	int status;

	if (args[0] == NULL)
		return (1);

	pid = fork();
	if (pid == -1)
	{
		perror("fork");
		exit(EXIT_FAILURE);
	}
	else if (pid == 0)
	{
		if (execve(args[0], args, environ) == -1)
		{
		perror("execve");
		exit(EXIT_FAILURE);
		}
	}
	else
	{
		do {
		waitpid(pid, &status, WUNTRACED);
		} while (!WIFEXITED(status) && !WIFSIGNALED(status));
	}

	return (1);
}
