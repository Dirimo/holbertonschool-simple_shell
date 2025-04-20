#include <unistd.h>
#include <stdlib.h>
#include <string.h>
#include "shell.h"

char *get_absolute_path(char *command) {
    char *path = getenv("PATH");
    char *path_copy = strdup(path);
    char *token = strtok(path_copy, ":");
    char *full_path = malloc(1024);

    while (token != NULL) {
        snprintf(full_path, 1024, "%s/%s", token, command);
        if (access(full_path, X_OK) == 0) {
            free(path_copy);
            return full_path;
        }
        token = strtok(NULL, ":");
    }
    
    free(path_copy);
    free(full_path);
    return NULL;
}
