#include <unistd.h>
#include <stdlib.h>
#include <string.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <stdio.h>
#include "shell.h"

extern char **environ;

void start_shell(void) {
    char command[1024];
    char *args[100];
    pid_t pid;
    int i;
    char *command_copy; /* Pour copier la commande avant strtok */

    while (1) {
        write(STDOUT_FILENO, "$ ", 2);

        if (fgets(command, sizeof(command), stdin) == NULL) {
            write(STDERR_FILENO, "Erreur de lecture\n", 18);
            exit(EXIT_FAILURE); /* Sortir de la boucle en cas d'erreur */
        }

        command[strcspn(command, "\n")] = 0;

        if (strlen(command) == 0) {
            continue;
        }

        /* Copier la commande avant d'utiliser strtok */
        command_copy = strdup(command);
        if (command_copy == NULL) {
            perror("strdup");
            exit(EXIT_FAILURE);
        }

        args[0] = strtok(command_copy, " ");
        i = 1;
        while ((args[i] = strtok(NULL, " ")) != NULL) {
            i++;
        }

        if (strcmp(args[0], "exit") == 0) {
            exit(0);
        }

        pid = fork();
        if (pid < 0) {
            write(STDERR_FILENO, "Erreur de fork\n", 16);
            exit(EXIT_FAILURE);
        }

        if (pid == 0) {
            if (execvp(args[0], args) < 0) {
                write(STDERR_FILENO, "Erreur d'exécution\n", 19);
                exit(EXIT_FAILURE);
            }
        } else {
            wait(NULL);
        }
        free(command_copy);
    }
}
