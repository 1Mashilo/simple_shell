#include "shell.h"


/**
* ss_strncmp - Compare two strings up to a specified number of characters.
* @string1: The first string.
* @string2: The second string.
* @n: The maximum number of characters to compare.
*
* Return:
*   - 0 if both strings are equal up to 'n' characters.
*   - A positive integer if 'string1' is greater than 'string2'.
*   - A negative integer if 'string1' is less than 'string2'.
*/
int ss_strncmp(const char *string1, const char *string2, size_t n)
{
while (n--)
{
if (*string1 != *string2)
{
return (*string1 - *string2);
}
if (*string1 == '\0')
{
return (0);
}
string1++;
string2++;
}
return (0);
}


/**
* ss_int_string - Converts an integer to a string.
* @num: The integer to convert.
* @str: Pointer to the output string.
*
* Description: This function converts an integer
* to a string and stores it in
* the provided buffer. It handles negative numbers as well.
*/
void ss_int_string(int num, char *str)
{
int i = 0;
int temp = num;
int divisor = 1;

if (num < 0)
{
str[i++] = '-';
temp = -num;
}

while (temp / divisor >= 10)
{
divisor *= 10;
}

while (divisor != 0)
{
str[i++] = '0' + (temp / divisor);
temp %= divisor;
divisor /= 10;
}

str[i] = '\0';
}
