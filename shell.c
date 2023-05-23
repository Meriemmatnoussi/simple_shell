#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/wait.h>
#include <string.h>

#define BUFFER_SIZE 1024

int main(void) {
    char *buffer;
    size_t bufsize = BUFFER_SIZE;

    buffer = (char *)malloc(bufsize * sizeof(char));
    if (buffer == NULL) {
        perror("malloc error");
        exit(EXIT_FAILURE);
    }

    while (1) {
        printf("$ ");
        if (getline(&buffer, &bufsize, stdin) == -1) {
            if (feof(stdin)) {
                printf("\n");
                break;
            } else {
                perror("getline error");
                exit(EXIT_FAILURE);
            }
        }

        // Remove newline character from the end
        buffer[strcspn(buffer, "\n")] = '\0';

        // Fork a child process
        pid_t pid = fork();

        if (pid == -1) {
            perror("fork error");
            exit(EXIT_FAILURE);
        } else if (pid == 0) {
            // Child process
            if (execve(buffer, (char *[]) {buffer, NULL}, NULL) == -1) {
                perror("execve error");
                exit(EXIT_FAILURE);
            }
        } else {
            // Parent process
            wait(NULL);
        }
    }

    free(buffer);

    return 0;
}
