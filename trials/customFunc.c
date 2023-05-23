#include "main.h"

int _strlen(char *str)
{
    int i = 0;

    while (*str)
    {
         i++;
         str++;
    }

    return (i);
}

int _strncmp(const char* str1, const char* str2, size_t n) {
    size_t i;

    for (i = 0; i < n; i++) {
        if (str1[i] < str2[i]) {
            return -1;
        }
        else if (str1[i] > str2[i]) {
            return 1;
        }
        else if (str1[i] == '\0' || str2[i] == '\0') {
            break;
        }
    }

    return 0;
}

char *get_env(char *name) 
{
    extern char **environ;
    char **env = environ;

    while (*env != NULL) {
        char* variable = *env;

        if (_strncmp(variable, name, _strlen(name)) == 0) {
            // Skip the variable name and the equals sign to get the value
            return variable + strlen(name) + 1;
        }

        env++;
    }
    return NULL;
}

char *_strncpy(char *dest, char *src, int n)
{
	int i = 0;

	while (i < n && src[i] != '\0')
	{
		dest[i] = src[i];
		i++;
	}

	while (i < n)
	{
		dest[i] = '\0';
		i++;
	}
	return (dest);
}