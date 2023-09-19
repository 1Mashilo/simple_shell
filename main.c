#include "shell.h"

/**
* main - Entry point of the shell.
* @argc: The number of command-line arguments.
* @argv: An array of strings containing the arguments.
*
* Return: The exit status of the shell.
*/
int main(int argc, char *argv[])
{
char *program_name;
int input_fd;

if (argc > 0)
program_name = argv[0];

if (argc > 1)
{
input_fd = open(argv[1], O_RDONLY);
if (input_fd == -1)
{
perror(program_name);
return (1);
}

return (execute_shell(input_fd));

}
else
{
return (execute_shell(STDIN_FILENO));
}
}

/**
* execute_shell - Executes the shell.
* @input_fd: The file descriptor for input.
*
* Return: The exit status of the shell.
*/
int execute_shell(int input_fd)
{
int ss_interactive = (input_fd == STDIN_FILENO);
int builtin_return = 0;
char *command_line = NULL;
env_node_t *env_list = NULL;

env_list = ss_convert_to_env_node_t(environ);

while (1)
{
ssize_t read_result;
int file_fd;

if (ss_interactive)
display_prompt("$ ");
if (ss_interactive)
{
file_fd = STDIN_FILENO;
read_result = read_command_line(file_fd, &command_line);
}
else
{
file_fd = input_fd;
read_result = read_command_line(file_fd, &command_line);
}
if (read_result != -1)
{
handle_input(command_line, env_list);
free(command_line);
}
else if (ss_interactive)
{
break;
}
}
ss_free_env_list(env_list);
return (builtin_return);
}

