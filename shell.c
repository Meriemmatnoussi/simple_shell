#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <sys/types.h>
#include <sys/wait.h>

#define BUFFER_SIZE 1024
/**
 * main - Simple UNIX command line interpreter.
 *
 * Return: Always 0.
 */

int main(void)
{
char input[BUFFER_SIZE];

while (1)
{
	printf("$ ");
if (fgets(input, BUFFER_SIZE, stdin) == NULL)
	break;

	input[strcspn(input, "\n")] = '\0';

	pid_t pid = fork();

	if (pid < 0)
	{
	perror("fork");
	exit(EXIT_FAILURE);
	}
	else if (pid == 0)
	{
	execlp(input, input, NULL);
	perror("execlp");
	exit(EXIT_FAILURE);
	}
	else
	{
	waitpid(pid, NULL, 0);
	}
	}

return (0);
}
