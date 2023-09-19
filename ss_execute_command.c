#include "shell.h"

/**
* ss_execute_builtin - Execute a built-in command.
* @argv: An array of strings containing the command and its arguments.
* @env_list: The environment variable list.
*
* Return: The exit status of the executed built-in command or -1 on error.
*/
int ss_execute_builtin(char **argv, env_node_t *env_list)
{
if (argv[0] == NULL)
{

return (0);
}

if (ss_strcmp(argv[0], "exit") == 0)
{
ss_exit();
return (0);
}
else if (ss_strcmp(argv[0], "env") == 0)
{

ss_env(env_list);
return (0);
}

return (-1);
}

/**
* ss_execute_external - Execute an external command.
* @argv: An array of strings containing the command and its arguments.
* @env_list: The environment variable list.
*
* Return: The exit status of the executed external command or -1 on error.
*/
int ss_execute_external(char **argv, env_node_t *env_list)
{
pid_t child_pid;
int child_status;
char **envp;
char *command_path;

command_path = ss_find_path("/usr/local/bin:/usr/bin", argv[0]);
if (command_path == NULL)
{perror("Command not found");
return (-1);
}
child_pid = fork();
if (child_pid  == -1)
{perror("Fork failed");
return (-1);
}
if (child_pid == 0)
{envp = env_list_to_char_array(env_list);
if (envp == NULL)
{perror("Failed to convert environment variables");
exit(EXIT_FAILURE);
}
if (execve(command_path, argv, envp) == -1)
{
perror("Execution failed");
exit(EXIT_FAILURE);
}
}
else
{
waitpid(child_pid, &child_status, 0);
if (WIFEXITED(child_status))
{
return (WEXITSTATUS(child_status));
}
else
{perror("Child process did not exit normally");
return (-1);
}
}
return (0);
}

/**
* ss_execute_command - Execute a command.
* @argv: An array of strings containing the command and its arguments.
* @env_list: The environment variable list.
*
* Return: The exit status of the executed command or -1 on error.
*/
int ss_execute_command(char **argv, env_node_t *env_list)
{
int exit_status;

exit_status = ss_execute_builtin(argv, env_list);
if (exit_status == -1)
{
exit_status = ss_execute_external(argv, env_list);
}
return (exit_status);
}

/**
* env_list_to_char_array - Convert an environment variable
* linked list to a char array.
* @env_list: The environment variable linked list.
*
* Return: A char array containing environment variable strings.
*/
char **env_list_to_char_array(env_node_t *env_list)
{
int count = 0;
env_node_t *current;
char **char_array;
int i;

current = env_list;

while (current != NULL)
{
count++;
current = current->next;
}


char_array = (char **)malloc((count + 1) * sizeof(char *));
if (char_array == NULL)
{
perror("Memory allocation failed");
exit(EXIT_FAILURE);
}

current = env_list;
i = 0;
while (current != NULL)
{
char_array[i] = ss_strdup(current->data);
if (char_array[i] == NULL)
{
perror("Memory allocation failed");
exit(EXIT_FAILURE);
}
i++;
current = current->next;
}
char_array[count] = NULL;
return (char_array);
}

