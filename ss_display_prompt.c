#include "shell.h"

/**
* read_command_line - Reads a line of input from a file descriptor.
* @file_descriptor: The file descriptor to read from (e.g., stdin).
* @output_line: Pointer to a char pointer where the
* command line will be stored.
*
* Return: The number of characters read (including '\0'), or -1 on failure.
*/
ssize_t read_command_line(int file_descriptor, char **output_line)
{
char *line_buffer = NULL;
size_t line_buffer_size = 0;
ssize_t read_result;
size_t line_length;

(void)file_descriptor;

read_result = getline(&line_buffer, &line_buffer_size, stdin);

if (read_result != -1)
{
line_length = ss_strlen(line_buffer);
if (line_length > 0 && line_buffer[line_length - 1] == '\n')
{
line_buffer[line_length - 1] = '\0';
}
*output_line = malloc(line_length + 1);
if (*output_line == NULL)
{
perror("malloc");
exit(EXIT_FAILURE);
}
ss_strcpy(*output_line, line_buffer);
}

free(line_buffer);

return (read_result);
}

/**
* display_prompt - Displays a prompt for the shell.
* @prompt: The prompt to display.
*/
void display_prompt(const char *prompt)
{
write(STDOUT_FILENO, prompt, ss_strlen(prompt));
}

