#include "shell.h"

/**
*  _strlen  - returns the length of a string
* @s: the string whose length to check
*
* Return: integer length of the string
*/
int _strlen(char *s)
{
int length = 0;

if (!s)
return (0);

while (*s++)
length++;

return length;
}

/**
* stringCompare - performs lexicographic comparison of two strings.
* @s1: the first string
* @s2: the second string
*
* Return: negative if s1 < s2, positive if s1 > s2, zero if s1 == s2
*/
int _strcmp(char *string1, char *s2)
{
while (*string1 && *s2)
{
if (*string1 != *s2)
return (*string1 - *s2);

string1++;
s2++;
}

if (*string1 == *s2)
return (0);
else
return (*string1 < *s2 ? -1 : 1);
}

/**
* startsWith - checks if a string starts with another string
* @haystack: string to search
* @needle: the substring to find
*
* Return: address of the next character of haystack or NULL
*/
char *startsWith(const char *haystack, const char *needle)
{
while (*needle)
{
if (*needle++ != *haystack++)
return (NULL);
}

return ((char *)haystack);
}

/**
* _strcat - concatenates two strings
* @dest: the destination buffer
* @src: the source buffer
*
* Return: pointer to the destination buffer
*/
char *_strcat(char *destination, char *src)
{
char *ret = destination;

while (*destination)
destination++;

while (*src)
*destination++ = *src++;

*destination = *src;

return (ret);
}

