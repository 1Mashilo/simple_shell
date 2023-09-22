#include "shell.h"

/**
* bfree - frees a pointer and NULLs the address
* @pointer: address of the pointer to free
*
* Return: 1 if freed, otherwise 0.
*/
int bfree(void **pointer)
{
if (pointer && *pointer)
{
free(*pointer);
*pointer = NULL;
return (1);
}
return (0);
}

/**
* ffree - frees a string of strings
* @pp: string of strings
*/
void ffree(char **ptr)
{
char **a = ptr;
if (!ptr)
return;
while (*ptr)
free(*ptr++);
free(a);
}

