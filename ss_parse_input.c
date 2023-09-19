#include "shell.h"

/**
* ss_parse_input - Parse a command string into an array of strings.
* @input: The command string to parse.
*
* Return: An array of strings containing the parsed input.
*/
char **ss_parse_input(const char *input)
{
char **parsed_input;
const char *delimiters = " \t\n";
char *input_copy;
char *token;
size_t i = 0;
size_t num_words;

num_words = count_words(input);
parsed_input = malloc((num_words + 1) * sizeof(char *));
if (parsed_input == NULL)
{
perror("Memory allocation failed");
exit(EXIT_FAILURE);
}
input_copy = ss_strdup(input);
if (input_copy == NULL)
{
perror("Memory allocation failed");
free(parsed_input);
exit(EXIT_FAILURE);
}
token = strtok(input_copy, delimiters);
while (token != NULL)
{
parsed_input[i] = ss_strdup(token);
if (parsed_input[i] == NULL)
{
perror("Memory allocation failed");
free(parsed_input);
free(input_copy);
exit(EXIT_FAILURE);
}
i++;
token = strtok(NULL, delimiters);
}
parsed_input[i] = NULL;
free(input_copy);
return (parsed_input);
}

/**
* count_words - Count the number of words in a string.
* @str: The input string.
*
* Return: The number of words in the string.
*/
size_t count_words(const char *str)
{
size_t count = 0;
int in_word = 0;

while (*str)
{
if (*str == ' ' || *str == '\t' || *str == '\n')
{
if (in_word)
{
in_word = 0;
count++;
}
}
else
{
in_word = 1;
}
str++;
}

if (in_word)
count++;

return (count);
}

/**
* free_parsed_input - Free memory allocated for parsed input.
* @parsed_input: The array of parsed input strings.
*/
void free_parsed_input(char **parsed_input)
{
size_t j = 0;
if (parsed_input == NULL)
return;


for (j = 0; parsed_input[j] != NULL; j++)
{
free(parsed_input[j]);
}

free(parsed_input);
}
