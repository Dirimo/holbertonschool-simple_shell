#include "shell.h"
#include <stdlib.h>
#include <unistd.h>
#include <stdio.h>

/**
 * main - point d'entrée du shell
 * @argc: nombre d'arguments (non utilisé)
 * @argv: tableau contenant le nom du programme
 * Return: 0
 */
int main(int argc, char **argv)
{
    char *line = NULL;
    size_t len = 0;
    ssize_t nread;
    char **args;
    int i;
    (void)argc;

    while (1)
    {
        if (isatty(STDIN_FILENO))
            display_prompt();

        nread = getline(&line, &len, stdin);
        if (nread == -1)
        {
            free(line);
            if (isatty(STDIN_FILENO))
                write(STDOUT_FILENO, "\n", 1);
            exit(0);
        }

        line[strcspn(line, "\n")] = '\0';
        args = tokenize_line(line);

        if (!args || !args[0])
        {
            free(args);
            continue;
        }

        if (_strcmp(args[0], "exit") == 0)
            handle_exit(args, line);
        else if (_strcmp(args[0], "env") == 0)
            print_env();
        else
            execute_command(args, argv[0]);

        for (i = 0; args[i]; i++)
            free(args[i]);
        free(args);
    }
    free(line);
    return (0);
}
