#ifndef SHELL_H
#define SHELL_H

void start_shell();
char **tokenize(char *command);
char *get_absolute_path(char *command);
void free_tokens(char **tokens);

#endif
