#ifndef MAIN_H
#define MAIN_H

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <sys/stat.h>

extern char **environ;

/* Function prototypes */
char **tokenize_input(char *line);
void execute_command(char **args);
void handle_input(char *line);
char *find_command(char *command);
#endif
