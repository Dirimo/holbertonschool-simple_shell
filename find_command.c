#include "main.h"
#include <string.h>
#include <stdlib.h>
#include <sys/stat.h>
#include <stdio.h>

/**
 * find_command - Cherche une commande dans les répertoires du PATH
 * @command: La commande à chercher (ex: "ls")
 * Return: Le chemin absolu de la commande, ou NULL si non trouvée
 */
char *find_command(char *command)
{
	char *path = getenv("PATH");
	char *path_copy, *token, *full_path;
	struct stat st;

	if (!path)
		return (NULL);

	path_copy = strdup(path); /* strtok modifie la chaîne */
	if (!path_copy)
		return (NULL);

	token = strtok(path_copy, ":");
	while (token)
	{
		full_path = malloc(strlen(token) + strlen(command) + 2);
		if (!full_path)
		{
			free(path_copy);
			return (NULL);
		}

		sprintf(full_path, "%s/%s", token, command);

		if (stat(full_path, &st) == 0)
		{
			free(path_copy);
			return (full_path); /* Commande trouvée */
		}

		free(full_path);
		token = strtok(NULL, ":");
	}
	free(path_copy);
	return (NULL); /* Commande non trouvée */
}
