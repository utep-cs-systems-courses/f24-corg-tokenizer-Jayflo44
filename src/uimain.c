#include <stdio.h>
#include <ctype.h>
#include <stdlib.h>
#include <string.h>
#include "tokenizer.h"
#include "history.h"

int main() {
    printf("Welcome!\n");
    printf("At any time, you can enter: 'exit' to terminate the program or 'history' to show the history of each sentence entered.\n");
    char str[100]; // Buffer to hold user input
    List *history = init_history(); // Initializes history.
    int recalled = 0;  // Flag to track whether a command is recalled from history
    if (history == NULL) {
        printf("Failed to create history.\n");
        return 1;
    }
    while (1) {
        printf("Enter a string: ");
        fgets(str, sizeof(str), stdin); // Get user input

        // Remove the newline character if present
        str[strcspn(str, "\n")] = '\0';

        if (strcmp(str, "exit") == 0) {
            printf("Exiting...\n");
            break;
        } else if (strcmp(str, "history") == 0) {
            printf("History:\n");
            print_history(history); // Print history
            continue; // Skip adding the 'history' command to history
        } else if (str[0] == '!' && isdigit(str[1])) {
            // Handle case where the user enters !<number> to recall a specific history command
            int id = atoi(&str[1]); // Convert the number after '!' to an integer

            // Get the command from history corresponding to the given ID
            char *command = get_history(history, id);
            if (command != NULL) {
                printf("Repeating command %d: %s\n", id, command);

                // Treat the recalled command as input and set the recall flag (do not add to history)
                strcpy(str, command);
                recalled = 1;  // Set the flag to indicate this is a recalled command
            } else {
                printf("No command found for !%d\n", id);
                continue;
            }
        }
        // Only add the current command to history if it's not recalled, 'history', or 'exit'
        if (!recalled && strcmp(str, "history") != 0 && strcmp(str, "exit") != 0) {
            add_history(history, str); // Add the current command to history
        }
        // Reset the recall flag after processing
        recalled = 0;
        // Tokenize the input string (whether it was recalled or newly entered)
        char **tokens = tokenize(str);
        if (tokens != NULL) {
            printf("Tokens:\n");
            print_tokens(tokens);  // Print each token
            free_tokens(tokens);   // Free allocated memory
        } else {
            printf("Tokenization failed.\n");
        }
    }
    free_history(history); // Free the history when done
    return 0;
}
