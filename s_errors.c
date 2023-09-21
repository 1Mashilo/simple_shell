#include "shell.h"


/**
 * _strcpy - copies a string
 * @dest: the destination
 * @src: the source
 *
 * Return: pointer to destination
 */
char *_strcpy(char *destination, char *source)
{
    int i = 0;

    if (destination == source || source == NULL)
        return (destination);

    while (source[i])
    {
        destination[i] = source[i];
        i++;
    }
    destination[i] = '\0';

    return (destination);
}

/**
 * _strdup - duplicates a string
 * @str: the string to duplicate
 *
 * Return: pointer to the duplicated string
 */
char *_strdup(const char *original)
{
    int length = 0;
    char *duplicate;
int i = 0;
    if (original == NULL)
        return (NULL);

    while (original[length])
        length++;

    duplicate = (char *)malloc(sizeof(char) * (length + 1));
    if (!duplicate)
        return (NULL);

    for (i = 0; i <= length; i++)
        duplicate[i] = original[i];

    return (duplicate);
}

