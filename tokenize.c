#include <stdio.h>
#include <stdlib.h>
#include <string.h>

char **tokenize_line(char *line)
{
    char **args = NULL;
    char *token;
    int i = 0;
    char **temp;

    token = strtok(line, " ");
    while (token != NULL)
    {
        temp = realloc(args, sizeof(char *) * (i + 1));
        if (!temp)
        {
            free(args);
            return NULL;
        }

        args = temp;
        args[i] = strdup(token);
        i++;

        token = strtok(NULL, " ");
    }

    temp = realloc(args, sizeof(char *) * (i + 1));
    if (!temp)
    {
        free(args);
        return NULL;
    }

    args = temp;
    args[i] = NULL;

    return args;
}
