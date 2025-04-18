#include "shell.h"

/**
 * display_prompt - Affiche l'invite du shell.
 */
void display_prompt(void) {
    write(STDOUT_FILENO, PROMPT, strlen(PROMPT));
}
