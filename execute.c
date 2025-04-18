#include "shell.h"

/**
 * execute_command - Exécute une commande.
 *
 * Args :
 *   args : Un tableau de chaînes contenant la commande et ses arguments.
 */
void execute_command(char **args) {
    pid_t pid;
    int status;
    char error_message[256];

    if (args == NULL || args[0] == NULL) {
        
        return;
    }

    pid = fork();
    if (pid == -1) {
        perror("fork");
        return;
    }

    if (pid == 0) {
        
        execve(args[0], args, environ);

        
        snprintf(error_message, sizeof(error_message),
	 "%s: No such file or directory\n", args[0]);
        write(STDERR_FILENO, error_message, strlen(error_message));
        exit(EXIT_FAILURE);
    } else {
        
        wait(&status);
    }
}
