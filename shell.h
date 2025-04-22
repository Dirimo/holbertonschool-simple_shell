#ifndef SHELL_H
#define SHELL_H

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <sys/wait.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <errno.h>

/* Pour execve() */
extern char **environ;

/* ==== BUILTINS ==== */
void print_env(void); /* Affiche toutes les variables d'environnement */
void handle_exit(char **args, char *line); /* Gère exit proprement */

/* ==== EXECUTION ==== */
void execute_command(char **args, char *prog_name);
int is_executable(char *path);

/* ==== PATH ==== */
char *get_full_path(char *command);

/* ==== TOKENIZER ==== */
char **tokenize_line(char *line);

/* ==== PROMPT ==== */
void display_prompt(void);

/* ==== UTILS ==== */
int _strcmp(char *s1, char *s2);
char *_strdup(char *s);
int _strlen(char *s);

#endif /* SHELL_H */
