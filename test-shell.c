#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <sys/types.h>
#include <sys/wait.h>

#define BUFFER_SIZE 1024

int main(void) {
    char input[BUFFER_SIZE];
    const char* prompt = "MyShell$ ";

    while (1) {
        printf("%s", prompt);  // Display the prompt
        if (fgets(input, BUFFER_SIZE, stdin) == NULL)
            break;  // Handle end of file (Ctrl+D)

        input[strcspn(input, "\n")] = '\0';  // Remove the trailing newline character

        if (strcmp(input, "exit") == 0)
            break;  // Exit the shell

        pid_t pid = fork();  // Fork a child process
        if (pid < 0) {
            perror("fork");
            exit(EXIT_FAILURE);
        } else if (pid == 0) {
            // Child process
            execlp(input, input, NULL);  // Execute the command
            perror(input);  // If execlp returns, an error occurred
            exit(EXIT_FAILURE);
        } else {
            // Parent process
            waitpid(pid, NULL, 0);  // Wait for the child process to complete
        }
    }

    return 0;
}
