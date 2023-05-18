#include "shell.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>

#define BUFFER_SIZE 1024

/**
 * display_prompt - Displays the prompt symbol.
 */
void display_prompt(void)
{
	printf("$ ");
}

/**
 * read_command - Reads a command from the user.
 * @buffer: The buffer to store the command.
 */
void read_command(char *buffer)
{
	fgets(buffer, BUFFER_SIZE, stdin);
}

/**
 * execute_command - Executes a command by forking a child
 *                   process and using exec to run the command.
 * @command: The command to execute.
 * Return: 0 on success, -1 on failure.
 */
int execute_command(char *command)
{
	pid_t pid;

	command[strcspn(command, "\n")] = '\0';

	pid = fork();

	if (pid < 0)
	{
		perror("fork");
		return (-1);
	}
	else if (pid == 0)
	{
		if (execlp(command, command, NULL) == -1)
		{
			perror("exec");
			exit(EXIT_FAILURE);
		}
	}
	else
	{
		wait(NULL);
	}

	return (0);
}

/**
 * main - The main function that runs the simple shell.
 *        Prompts the user for commands, executes them,
 *        and exits when "exit" is entered.
 * Return: 0 on success.
 */
int main(void)
{
	char command[BUFFER_SIZE];

	while (1)
	{
		display_prompt();
		read_command(command);

		if (strcmp(command, "exit\n") == 0)
		{
			break;
		}

		execute_command(command);
	}

	return (0);
}
