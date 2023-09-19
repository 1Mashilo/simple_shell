#include "shell.h"

/**
* ss_getenv - Find the value of an environment variable in
* a list of environment variables.
*
* @env_list: Linked list of environment variables (env_node_t *).
* @var_name: Name of the environment variable to find.
*
* Return: The value of the environment variable
* or NULL if not found.
*/
char *ss_getenv(env_node_t *env_list, const char *var_name)
{
env_node_t *current = env_list;
size_t var_name_len = ss_strlen(var_name);

while (current != NULL)
{
if (ss_strncmp(current->data, var_name, var_name_len) == 0)
{
return (current->data + var_name_len + 1);
}
current = current->next;
}

return (NULL);
}

/**
* ss_convert_to_env_node_t - Convert environment variables
* to env_node_t format.
* @environ: The array of environment variables.
*
* Return: A linked list of env_node_t containing environment
* variables.
*/
env_node_t *ss_convert_to_env_node_t(char **environ)
{
env_node_t *env_list = NULL;
int i = 0;

while (environ[i] != NULL)
{
ss_add_to_env_list(&env_list, environ[i]);
i++;
}

return (env_list);
}

/**
* ss_add_to_env_list - Add an environment variable to the linked list.
* @env_list: Pointer to the head of the linked list.
* @env_var: The environment variable to add.
*/
void ss_add_to_env_list(env_node_t **env_list, const char *env_var)
{
env_node_t *new_node = malloc(sizeof(env_node_t));
if (new_node == NULL)
{
perror("Memory allocation failed");
exit(EXIT_FAILURE);
}

new_node->data = ss_strdup(env_var);
if (new_node->data == NULL)
{
perror("Memory allocation failed");
free(new_node);
exit(EXIT_FAILURE);
}

new_node->next = NULL;

if (*env_list == NULL)
{
*env_list = new_node;
}
else
{
env_node_t *current = *env_list;
while (current->next != NULL)
{
current = current->next;
}
current->next = new_node;
}
}

/**
* ss_env - Prints the environment variables and their count.
* @env_list: Linked list of environment variables.
*/
void ss_env(env_node_t *env_list)
{
size_t printed_count = 0;
env_node_t *current = env_list;
char count_str[20];

while (current != NULL)
{
write(STDOUT_FILENO, current->data, ss_strlen(current->data));
write(STDOUT_FILENO, "\n", 1);
printed_count++;
current = current->next;
}
ss_int_string((int)printed_count, count_str);
write(STDOUT_FILENO, count_str, ss_strlen(count_str));
}
