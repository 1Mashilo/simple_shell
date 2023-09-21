#include "shell.h"

/**
* _eputs - prints an input string
* @str: the string to be printed
*
* Return: Nothing
*/
void _eputs(char *str)
{
    int index = 0;
    if (!str)
        return;
    while (str[index] != '\0')
    {
        _eputchar(str[index]);
        index++;
    }
}

/**
* _eputchar - writes the character c to stderr
* @c: The character to print
*
* Return: On success 1.
* On error, -1 is returned, and errno is set appropriately.
*/
int _eputchar(char c)
{
    static int buffer_index;
    static char buffer[WRITE_BUF_SIZE];
    if (c == BUF_FLUSH || buffer_index >= WRITE_BUF_SIZE)
    {
        write(2, buffer, buffer_index);
        buffer_index = 0;
    }
    if (c != BUF_FLUSH)
        buffer[buffer_index++] = c;
    return (1);
}

/**
* _putfd - writes the character c to given fd
* @c: The character to print
* @fd: The file descriptor to write to
*
* Return: On success 1.
* On error, -1 is returned, and errno is set appropriately.
*/
int _putfd(char c, int fd)
{
    static int buffer_index;
    static char buffer[WRITE_BUF_SIZE];
    if (c == BUF_FLUSH || buffer_index >= WRITE_BUF_SIZE)
    {
        write(fd, buffer, buffer_index);
        buffer_index = 0;
    }
    if (c != BUF_FLUSH)
        buffer[buffer_index++] = c;
    return (1);
}

/**
* _putsfd - prints an input string
* @str: the string to be printed
* @fd: the file descriptor to write to
*
* Return: the number of characters put
*/
int _putsfd(char *str, int fd)
{
    int index = 0;
    if (!str)
        return (0);
    while (str[index])
    {
        index += _putfd(str[index], fd);
    }
    return (index);
}

