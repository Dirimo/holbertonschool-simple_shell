#ifndef SHELL_H
#define SHELL_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <errno.h>

#define PROMPT "#cisfun$ "
#define MAX_COMMAND_LENGTH 100
#define MAX_ARGS 10

extern char **environ; /* Déclare la variable environ */

/* Prototypes des fonction */
void display_prompt(void);
char *read_command(void);
char **tokenize_command(char *command);
void execute_command(char **args);

#endif
