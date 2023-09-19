#include "shell.h"

/**
* ss_strcpy - Copy a string
* @dest: The destination buffer
* @src: The source string to copy
* Return: A pointer to the destination buffer.
*/
char *ss_strcpy(char *dest, const char *src)
{
char *original_dest = dest;

while ((*dest++ = *src++) != '\0')
{

}

return (original_dest);
}

/**
* ss_strlen - Calculate the length of a string.
* @string: The input string.
*
* Return: The length of the string.
*/
size_t ss_strlen(const char *string)
{
size_t length = 0;

while (string[length] != '\0')
{
length++;
}

return (length);
}


/**
* ss_strcmp - Compare two strings.
* @string1: The first string to compare.
* @string2: The second string to compare.
*
* Return:
*   -1 if string1 is less than string2.
*    0 if string1 is equal to string2.
*    1 if string1 is greater than string2.
*/
int ss_strcmp(const char *string1, const char *string2)
{
while (*string1 && (*string1 == *string2))
{
string1++;
string2++;
}

return (*(unsigned char *)string1 - *(unsigned char *)string2);
}

/**
* ss_strdup - Duplicate a string
* * @string: The string to duplicate
* Return: A pointer to the newly allocated duplicate string.
*/
char *ss_strdup(const char *string)
{
size_t len = ss_strlen(string);
char *new_string = malloc(len + 1);

if (!new_string)
return (NULL);

return (ss_strcpy(new_string, string));
}

/**
* ss_strconcat - Concatenate two strings with an optional separator.
* @string1: The first string.
* @sep: The separator to add between string1 and string2 (can be NULL).
* @string2: The second string.
*
* Return: The concatenated string or NULL on failure.
* Caller must free the result.
*/
char *ss_strconcat(const char *string1, const char *sep, const char *string2)
{
size_t len1 = (string1 != NULL) ? strlen(string1) : 0;
size_t len2 = (string2 != NULL) ? strlen(string2) : 0;
size_t seplen = (sep != NULL) ? strlen(sep) : 0;
char *result = malloc(len1 + seplen + len2 + 1);

if (result == NULL)
{
perror("Memory allocation failed");
exit(EXIT_FAILURE);
}

if (len1 > 0)
strcpy(result, string1);

if (seplen > 0)
strcat(result, sep);

if (len2 > 0)
strcat(result, string2);

return (result);
}
