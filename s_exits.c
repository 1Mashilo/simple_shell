#include "shell.h"


/**
* s_strncpy - copies a string
* @destination: the destination string to be copied to
* @source: the source string
* @num: the number of characters to be copied
* Return: the concatenated string
*/
char *s_strncpy(char *destination, char *source, int num)
{
int i, j;
char *result = destination;
i = 0;

while (source[i] != '\0' && i < num - 1)
{
destination[i] = source[i];
i++;
}

if (i < num)
{
j = i;
while (j < num)
{
destination[j] = '\0';
j++;
}
}

return (result);
}

/**
* s_strncat - concatenates two strings
* @destination: the first string
* @source: the second string
* @num: the maximum number of bytes to be used
* Return: the concatenated string
*/
char *s_strncat(char *destination, char *source, int num)
{
int i, j;
char *result = destination;
i = 0;
j = 0;

while (destination[i] != '\0')
i++;

while (source[j] != '\0' && j < num)
{
destination[i] = source[j];
i++;
j++;
}

if (j < num)
destination[i] = '\0';

return (result);
}

/**
* s_strchr - locates a character in a string
* @str: the string to be parsed
* @c: the character to look for
* Return: a pointer to the memory area str
*/
char *s_strchr(char *str, char c)
{
do
{
if (*str == c)

return (str);
} 

while (*str++ != '\0');

return (NULL);
}

