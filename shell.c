#include "shell.h"

// Implementation of shell_execute function
void shell_execute() {
    char input[MAX_COMMAND_LENGTH];

    while (1) {
        printf("$ > ");
        fgets(input, MAX_COMMAND_LENGTH, stdin);

        // Remove trailing newline character
        input[strcspn(input, "\n")] = '\0';

        // Exit if user enters "exit" command
        if (strcmp(input, "exit") == 0) {
            printf("Exiting shell...\n");
            break;
        }

        // Execute the command
        system(input);
    }
}
