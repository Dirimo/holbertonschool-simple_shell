#include "main.h"

/**
 * main - Entry point of the shell.
 * Return: Always 0
 */
int main(void)
{
	char *line = NULL;
	size_t len = 0;

	while (1)
	{
		print_prompt();

		if (getline(&line, &len, stdin) == -1)
		{
			write(STDOUT_FILENO, "\n", 1);
			break;
		}

		if (line[0] == '\n')
			continue;

		handle_input(line);
	}

	free(line);
	return (0);
}
