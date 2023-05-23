#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>

#define MAX_COMMAND_LENGTH 100

int main(void) {
    char command[MAX_COMMAND_LENGTH];
    int exit_shell = 0;

    while (!exit_shell) {
        printf("#cisfun$ ");
        if (fgets(command, MAX_COMMAND_LENGTH, stdin) == NULL) {
            exit_shell = 1;  // End of file (Ctrl+D) detected
            continue;
        }

        // Remove the trailing newline character
        command[strcspn(command, "\n")] = '\0';

        // Check if the command is "exit"
        if (strcmp(command, "exit") == 0) {
            exit_shell = 1;
            continue;
        }

        // Fork a child process
        pid_t pid = fork();

        if (pid < 0) {
            perror("fork");
            exit(1);
        } else if (pid == 0) {
            // Child process
            if (execlp(command, command, NULL) == -1) {
                perror("execlp");
                exit(1);
            }
        } else {
            // Parent process
            int status;
            waitpid(pid, &status, 0);

            if (status != 0) {
                fprintf(stderr, "./shell: %s: command not found\n", command);
            }
        }
    }

    return 0;
}
