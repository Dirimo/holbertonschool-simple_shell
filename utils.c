#include <stdlib.h>
#include <string.h>
#include "shell.h"

void free_tokens(char **tokens) {
    free(tokens);
}
