#include <stdlib.h>
#include <string.h>
#include "shell.h"

char **tokenize(char *command) {
    char **tokens = malloc(100 * sizeof(char*));
    char *token;
    int i = 0;

    token = strtok(command, " ");
    while (token != NULL) {
        tokens[i++] = token;
        token = strtok(NULL, " ");
    }
    tokens[i] = NULL;
    return tokens;
}
