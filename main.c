#include "shell.h"
#include <sys/types.h>
#include <sys/wait.h>
#include <unistd.h>

/**
 * shell_loop - Starts the shell loop,
 *              prompting for commands and executing them.
 */
void shell_loop(void)
{
	char *input;
	char **args;
	int status;

	do {
		printf("$ ");
		input = read_input();
		args = split_input(input);
		status = execute(args);

		free(input);
		free(args);
	} while (status);
}

/**
 * execute - Executes a command by forking a child process
 *           and executing the command.
 * @args: The command and its arguments.
 *
 * Return: 1 to continue the shell loop, 0 to exit the shell.
 */
int execute(char **args)
{
	pid_t pid;
	int status;

	pid = fork();
	if (pid < 0)
	{
		perror("fork");
		exit(EXIT_FAILURE);
	}
	else if (pid == 0)
	{
		if (execvp(args[0], args) == -1)
		{
			perror("execvp");
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
