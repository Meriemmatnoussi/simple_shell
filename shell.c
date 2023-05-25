#include "shell.h"

void shell_loop(void)
{
    char *input_str;
    char **args;
    int execution_status;

    do {
        printf("$ ");
        input_str = read_input();
        args = split_input(input_str);
        execution_status = execute(args);

        free(input_str);
        free(args);
    } while (execution_status);
}

int execute(char **args)
{
    pid_t process_id;
    int status;

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
            waitpid(process_id, &status, WUNTRACED);
        } while (!WIFEXITED(status) && !WIFSIGNALED(status));
    }

    return 1;
}
