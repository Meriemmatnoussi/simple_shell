#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "shell.h"

#define BUFFER_SIZE 1024

void shell_loop()
{
    char line[BUFFER_SIZE];

    while (1)
    {
        /* Read input line */
        printf(":~/shell$ ");
        fgets(line, sizeof(line), stdin);
        line[strcspn(line, "\n")] = '\0';

        /* Execute command */
        exec_command(line);
    }
}

int main(void)
{
    shell_loop();

    return EXIT_SUCCESS;
}
