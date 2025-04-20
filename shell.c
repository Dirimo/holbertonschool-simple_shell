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
    while (1) {
        write(STDOUT_FILENO, "$ ", 2);
        if (fgets(command, sizeof(command), stdin) == NULL) {
            write(STDERR_FILENO, "Erreur de lecture\n", 18);
            continue;
        }
        command[strcspn(command, "\n")] = 0;
        if (strlen(command) == 0) {
            continue;
        }
        args[0] = strtok(command, " ");
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
    }
}
