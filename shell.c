#include "shell.h"
#include <unistd.h>  /* Include for execve() */

int main(void)
{
    shell_loop();

    return 0;
}

void shell_loop(void)
{
    char *line;
    ssize_t line_size;
    size_t bufsize = 0;

    while (1)
    {
        printf("($) ");
        line_size = getline(&line, &bufsize, stdin);
        if (line_size == -1)
        {
            if (feof(stdin))
            {
                putchar('\n');
                break;
            }
            perror("getline");
            exit(EXIT_FAILURE);
        }

        /* Remove newline character */
        line[line_size - 1] = '\0';

        /* Execute command */
        if (exec_command(line) == -1)
        {
            printf("%s: command not found\n", line);
        }

        free(line);
    }
}
