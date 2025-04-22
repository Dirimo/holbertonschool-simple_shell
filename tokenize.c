#include <stdio.h>
#include <stdlib.h>
#include <string.h>

char **tokenize_line(char *line)
{
    char **args = NULL;
    char *token;
    int i = 0;
    int j;
    char **new_args;

    token = strtok(line, " ");
    while (token != NULL)
    {
        new_args = malloc(sizeof(char *) * (i + 2));
        if (!new_args)
        {
            for (j = 0; j < i; j++)
                free(args[j]);
            free(args);
            return NULL;
        }

        for (j = 0; j < i; j++)
            new_args[j] = args[j];

        new_args[i] = strdup(token);
        if (!new_args[i])
        {
            for (j = 0; j < i; j++)
                free(new_args[j]);
            free(new_args);
            free(args);
            return NULL;
        }

        new_args[i + 1] = NULL;
        free(args);
        args = new_args;
        i++;

        token = strtok(NULL, " ");
    }

    return args;
}
