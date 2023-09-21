#include "shell.h"

/**
* s_myenv - prints the current environment
* @info: Structure containing potential arguments. Used to maintain
* constant function prototype.
* Return: Always 0
*/
int s_env(info_t *info)
{
print_list_str(info->env);
return (0);
}

/**
* s_get_env_value - gets the value of an environment variable
* @info: Structure containing potential arguments. Used to maintain
* @name: Environment variable name
*
* Return: The value of the environment variable
*/
char *s_get_env_value(info_t *info, const char *name)
{
list_t *node = info->env;
char *value;

while (node)
{
value = startsWith(node->str, name);
if (value && *value)
return (value);
node = node->next;
}

return (NULL);
}

/**
* s_mysetenv - Initialize a new environment variable,
* or modify an existing one
* @info: Structure containing potential arguments. Used to maintain
* constant function prototype.
* Return: Always 0
*/
int s_mysetenv(info_t *info)
{
if (info->argc != 3)
{
_eputs("Incorrect number of arguments\n");
return (1);
}

if (s_set_environment_variable(info, info->argv[1], info->argv[2]))
return (0);

return (1);
}

/**
* s_myunsetenv - Remove an environment variable
* @info: Structure containing potential arguments. Used to maintain
* constant function prototype.
* Return: Always 0
*/
int s_myunsetenv(info_t *info)
{
int i;

if (info->argc == 1)
{
_eputs("Too few arguments.\n");
return (1);
}

for (i = 1; i < info->argc; i++)
_unset_environment_variable(info, info->argv[i]);

return (0);
}

/**
* s_populate_env_list - populates the environment linked list
* @info: Structure containing potential arguments. Used to maintain
* constant function prototype.
* Return: Always 0
*/
int s_populate_env_list(info_t *info)
{
list_t *node = NULL;
size_t i;

for (i = 0; environ[i]; i++)
add_node_end(&node, environ[i], 0);

info->env = node;
return (0);
}

