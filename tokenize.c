#include "shell.h"

/**
 * tokenize_command - Découpe une chaîne de commande en un tableau d'arguments.
 *
 * Args :
 *   command : La chaîne de commande à découper.
 *
 * Retour :
 *   Un tableau de chaînes contenant les arguments, ou NULL en cas d'échec.
 */
char **tokenize_command(char *command) {
    char **tokens = NULL;
    char *token = NULL;
    int i = 0;

    tokens = malloc(MAX_ARGS * sizeof(char *));
    if (tokens == NULL) {
        perror("malloc");
        return NULL;
    }

    token = strtok(command, " \n");
    while (token != NULL && i < MAX_ARGS - 1) {
        tokens[i] = token;
        i++;
        token = strtok(NULL, " \n");
    }
    tokens[i] = NULL;

    return tokens;
}
