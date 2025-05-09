#include "shell.h"
#include <sys/stat.h>
#include <unistd.h>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <errno.h>

extern char **environ;

char *get_full_path(char *command)
{
    char *path = NULL, *path_copy = NULL, *dir, *full_path;
    struct stat st;
    int i;

    
    for (i = 0; environ[i]; i++)
    {
        if (strncmp(environ[i], "PATH=", 5) == 0)
        {
            path = environ[i] + 5;
            break;
        }
    }

    if (!path)
        return NULL;

    path_copy = strdup(path);
    if (!path_copy)
        return NULL;

    dir = strtok(path_copy, ":");
    while (dir != NULL)
    {
        size_t len = strlen(dir) + strlen(command) + 2;
        full_path = malloc(len);
        if (!full_path)
        {
            free(path_copy);
            return NULL;
        }

        snprintf(full_path, len, "%s/%s", dir, command);

        if (stat(full_path, &st) == 0)
        {
            if (S_ISREG(st.st_mode) && (st.st_mode & S_IXUSR))
            {
                free(path_copy);
                return full_path;
            }
            errno = EACCES;
            free(full_path);
        }
        else
        {
            free(full_path);
        }
        dir = strtok(NULL, ":");
    }

    free(path_copy);
    fprintf(stderr, "%s: command not found\n", command);
    return NULL;
}
