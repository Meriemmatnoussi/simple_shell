#include "shell.h"

/**
 * shell_loop - Main loop for the shell program
 */
void shell_loop(void)
{
    char *input;
    char **arguments;
    int status;

    do {
        printf("$ ");
        input = read_input();
        arguments = split_input(input);
        status = execute(arguments);

        free(input);
        free(arguments);
    } while (status);
}

/**
 * execute - Execute a command with the given arguments
 * @args: Array of command arguments
 * Return: 1 if the shell should continue, 0 otherwise
 */
int execute(char **args)
{
    pid_t process_id;
    int process_status;

    process_id = fork();

    if (process_id < 0)
    {
        perror("fork");
        exit(EXIT_FAILURE);
    }
    else if (process_id == 0)
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
            waitpid(process_id, &process_status, WUNTRACED);
        } while (!WIFEXITED(process_status) && !WIFSIGNALED(process_status));
    }

    return 1;
}
