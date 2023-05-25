#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "shell.h"

#define BUFFER_SIZE 1024

void print_prompt() {
    printf("$ ");
}

char* read_command() {
    char* command = malloc(BUFFER_SIZE * sizeof(char));
    fgets(command, BUFFER_SIZE, stdin);
    return command;
}

void execute_command(char* command) {
    command[strcspn(command, "\n")] = '\0';  // Remove the trailing newline character
    if (strcmp(command, "exit") == 0) {
        exit(0);  // Exit the shell if the command is "exit"
    } else {
        int ret = system(command);  // Execute the command using the system() function
        if (ret == -1) {
            perror("Error executing command");
        }
    }
}

int main() {
    while (1) {
        print_prompt();
        char* command = read_command();
        execute_command(command);
        free(command);
    }
    return 0;
}
