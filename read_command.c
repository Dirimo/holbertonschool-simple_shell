#include "shell.h"

/**
 * read_command - Lit une commande depuis l'entrée standard.
 *
 * Retour :
 *   Un pointeur vers la chaîne contenant la commande, ou NULL en cas d'échec.
 */
char *read_command(void) {
    char *command = NULL;
    size_t len = 0;
    ssize_t nread;

    nread = getline(&command, &len, stdin);

    if (nread == -1) {
        free(command);
        return NULL;
    }

    return command;
}
