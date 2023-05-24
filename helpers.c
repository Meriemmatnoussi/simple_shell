#include "shell.h"
#include <stdio.h>   /* Include for perror() */
#include <stdlib.h>  /* Include for exit() */
#include <unistd.h>  /* Include for fork(), execvp() */
#include <sys/types.h>  /* Include for pid_t */
#include <sys/wait.h>   /* Include for wait() */

void exec_command(char *command) {
    pid_t pid;

    pid = fork();
    if (pid < 0) {
        perror("fork");
        exit(EXIT_FAILURE);
    } else if (pid == 0) {
        /* Child process */
        char **args = malloc(sizeof(char *) * 2);
        if (args == NULL) {
            perror("malloc");
            exit(EXIT_FAILURE);
        }

        args[0] = command;
        args[1] = NULL;

        if (execvp(args[0], args) == -1) {
            perror("execvp");
            exit(EXIT_FAILURE);
        }

        free(args);
    } else {
        /* Parent process */
        wait(NULL);
    }
}
