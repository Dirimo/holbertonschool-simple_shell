#include "shell.h"
#include <sys/stat.h>
#include <unistd.h>
#include <stdlib.h>
#include <string.h>
#include <stdio.h> // For NULL

char *get_full_path(char *command) {
	char *path, *path_copy, *dir, *full_path;
	struct stat st;

	path = getenv("PATH");
	if (!path) {
		return NULL;
	}

	path_copy = strdup(path);
	if (!path_copy) {
		return NULL; // Handle strdup failure
	}

	dir = strtok(path_copy, ":");
	while (dir != NULL) {
		size_t full_path_len = strlen(dir) + strlen(command) + 2; // +1 for '/', +1 for null terminator
		full_path = malloc(full_path_len);

		if (!full_path) {
			free(path_copy);
			return NULL;
		}

		strcpy(full_path, dir);
		strcat(full_path, "/");
		strcat(full_path, command);

		if (stat(full_path, &st) == 0 && S_ISREG(st.st_mode) && (st.st_mode & S_IXUSR)) {
			free(path_copy);
			return full_path;
		}

		free(full_path);
		dir = strtok(NULL, ":");
	}

	free(path_copy);
	return NULL;
}
