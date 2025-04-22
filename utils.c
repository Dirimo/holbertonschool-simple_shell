#include <stdlib.h>
#include <unistd.h>
int _strlen(char *s)
{
	int i = 0;

	while (s[i])
		i++;
	return (i);
}

int _strcmp(char *s1, char *s2)
{
	int i = 0;

	while (s1[i] && s2[i])
	{
		if (s1[i] != s2[i])
			return (s1[i] - s2[i]);
		i++;
	}
	return (s1[i] - s2[i]);
}

char *_strdup(char *s)
{
	char *dup;
	int i = 0, j = 0;

	while (s[i])
		i++;

	dup = malloc(sizeof(char) * (i + 1));
	if (!dup)
		return (NULL);

	while (s[j])
	{
		dup[j] = s[j];
		j++;
	}
	dup[j] = '\0';

	return (dup);
}
int is_executable(char *path)
{
    return (access(path, X_OK) == 0); /* Vérifie si le fichier est exécutable */
}
char *_strcpy(char *dest, const char *src)
{
    int i = 0;

    while (src[i] != '\0')
    {
        dest[i] = src[i];
        i++;
    }
    dest[i] = '\0';
    return dest;
}

char *_strcat(char *dest, const char *src)
{
    int i = 0;
    int j = 0;

    while (dest[i] != '\0')
    {
        i++;
    }

    while (src[j] != '\0')
    {
        dest[i + j] = src[j];
        j++;
    }

    dest[i + j] = '\0';
    return dest;
}
