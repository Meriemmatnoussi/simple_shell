#include "shell.h"
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>

#define PROMPT "$ "

void print_prompt()
{
    char cwd[1024];
    if (getcwd(cwd, sizeof(cwd)) != NULL)
        printf("%s ", cwd);
    else
        perror("getcwd");
}

char *read_command()
{
    char *command = NULL;
    size_t size = 0;
    ssize_t length = getline(&command, &size, stdin);

    if (length == -1)
    {
        if (feof(stdin))
        {
            exit(EXIT_SUCCESS);
        }
        else
        {
            perror("getline");
            exit(EXIT_FAILURE);
        }
    }

    if (length > 0 && command[length - 1] == '\n')
        command[length - 1] = '\0';

    return command;
}

void exec_command(char *command)
{
    pid_t pid;

    pid = fork();
    if (pid < 0)
    {
        perror("fork");
        exit(EXIT_FAILURE);
    }
    else if (pid == 0)
    {
        /* Child process */
        char **args = malloc(sizeof(char *) * 3);
        if (args == NULL)
        {
            perror("malloc");
            exit(EXIT_FAILURE);
        }

        args[0] = "/bin/sh";
        args[1] = "-c";
        args[2] = command;
        args[3] = NULL;

        if (execvp(args[0], args) == -1)
        {
            perror("execvp");
            exit(EXIT_FAILURE);
        }
    }
    else
    {
        /* Parent process */
        wait(NULL);
    }
}

int main(void)
{
    char *command;

    while (1)
    {
        print_prompt();
        printf(PROMPT);
        command = read_command();

        if (strcmp(command, "exit") == 0)
        {
            free(command);
            break;
        }

        exec_command(command);

        free(command);
    }

    return 0;
}
