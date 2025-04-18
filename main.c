#include "main.h"

/**
 * tokenize_input - Sépare une ligne de commande en arguments
 * @line: La ligne complète saisie (ex: "ls -l")
 * Return: Un tableau de chaînes (char **), terminé par NULL
 */
char **tokenize_input(char *line)
{
    char **args = NULL;
    char *token;
    int i = 0;

    args = malloc(sizeof(char *) * 64); /* max 64 mots, tu peux augmenter */
    if (!args)
    {
        perror("malloc");
        exit(EXIT_FAILURE);
    }

    token = strtok(line, " \t\r\n"); /* coupe par espace, tab, retour ligne */
    while (token != NULL)
    {
        args[i++] = token;
        token = strtok(NULL, " \t\r\n");
    }
    args[i] = NULL;

    return (args);
}

/**
 * execute_command - Exécute la commande via execve
 * @args: Les arguments de la commande (ex: {"ls", "-l", NULL})
 */
void execute_command(char **args)
{
    pid_t pid;
    int status;
    char *cmd_path;

    /* Si le chemin est absolu, on l’utilise directement */
    if (strchr(args[0], '/'))
        cmd_path = args[0];
    else
    {
        /* Chercher le chemin de la commande dans le $PATH */
        cmd_path = find_command(args[0]);
        if (!cmd_path)
        {
            fprintf(stderr, "%s: command not found\n", args[0]);
            return;
        }
    }

    pid = fork();
    if (pid == -1)
    {
        perror("fork");
        exit(EXIT_FAILURE);
    }

    if (pid == 0)
    {
        /* Enfant : exécuter la commande */
        if (execve(cmd_path, args, environ) == -1)
        {
            perror("execve");
            exit(EXIT_FAILURE);
        }
    }
    else
        waitpid(pid, &status, 0);

    if (cmd_path != args[0])
        free(cmd_path);
}

/**
 * handle_input - Gère l'entrée utilisateur et exécute la commande
 * @line: La ligne de commande saisie par l'utilisateur
 */
void handle_input(char *line)
{
    char **args;

    /* Enlever le retour à la ligne */
    if (line[strlen(line) - 1] == '\n')
        line[strlen(line) - 1] = '\0';

    /* Tokeniser l'entrée */
    args = tokenize_input(line);
    if (args[0] != NULL)
        execute_command(args);

    free(args); /* Libérer la mémoire allouée pour les arguments */
}

/**
 * main - Fonction principale
 * Retour: 0 si tout s'est bien passé
 */
int main(void)
{
    char *line = NULL;
    size_t len = 0;
    ssize_t nread;

    while (1)
    {
        /* Afficher le prompt */
        printf("#cisfun$ ");
        fflush(stdout);

        /* Lire la ligne de l'entrée standard */
        nread = getline(&line, &len, stdin);

        /* Vérifier si la fin du fichier a été atteinte (Ctrl+D) */
        if (nread == -1)
        {
            printf("\n");
            break;
        }

        /* Appeler handle_input() pour traiter la commande */
        handle_input(line);
    }

    free(line); /* Libérer la mémoire allouée pour la ligne */
    return (0);
}
