#include "shell.h"

/**
* s_erratoi - converts a string to an integer
* @str: the string to be converted
* Return: 0 if no numbers in string, converted number otherwise
* -1 on error
*/
int s_erratoi(char *str)
{
int index = 0;
unsigned long int result = 0;

if (*str == '+')
str++;

for (index = 0; str[index] != '\0'; index++)
{
if (str[index] >= '0' && str[index] <= '9')
{
result *= 10;
result += (str[index] - '0');
if (result > INT_MAX)
return (-1); 
}
else
{
return (-1); 
}
}

return (result);
}

/**
* s_print_error - prints an error message
* @info: the parameter & return info struct
* @error_str: string containing specified error type
* Return: None
*/
void s_print_error(info_t *info, char *error_str)
{
_eputs(info->fname);
_eputs(": ");
s_print_d(info->linecount, STDERR_FILENO);
_eputs(": ");
_eputs(info->argv[0]);
_eputs(": ");
_eputs(error_str);
}

/**
* s_print_d - function prints a decimal (integer) number (base 10)
* @input: the input number
* @fd: the file descriptor to write to
* Return: number of characters printed
*/
int s_print_d(int input, int fd)
{
int (*__s_putchar)(char) = _eputchar;
int i, count = 0;
unsigned int absolute, current;

if (fd == STDERR_FILENO)
__s_putchar = _eputchar;

if (input < 0)
{
absolute = -input;
__s_putchar('-');
count++;
}
else
{
absolute = input;
}

current = absolute;

for (i = 1000000000; i > 1; i /= 10)
{
if (absolute / i)
{
__s_putchar('0' + current / i);
count++;
}
current %= i;
}

__s_putchar('0' + current);
count++;

return (count);
}

/**
* s_convert_number - converter function, a clone of itoa
* @num: number
* @base: base
* @flags: argument flags
* Return: string
*/
char *s_convert_number(long int num, int base, int flags)
{
static char *array;
static char buffer[50];
char sign = 0;
char *ptr;
unsigned long n = num;

if (!(flags & CONVERT_UNSIGNED) && num < 0)
{
n = -num;
sign = '-';
}

array = flags & CONVERT_LOWERCASE ? "0123456789abcdef" :
"0123456789ABCDEF";
ptr = &buffer[49];
*ptr = '\0';

do
{
*--ptr = array[n % base];
n /= base;
} while (n != 0);

if (sign)
*--ptr = sign;

return (ptr);
}

/**
* s_remove_comments - replaces first instance of '#' with '\0'
* @buf: address of the string to modify
* Return: Always 0
*/
void s_remove_comments(char *buf)
{
int index;

for (index = 0; buf[index] != '\0'; index++)
{
if (buf[index] == '#' && (!index || buf[index - 1] == ' '))
{
buf[index] = '\0';
break;
}
}
}

