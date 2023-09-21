#include "shell.h"

/**
* s_get_environment - returns the string array copy of our environment
* @info: Structure containing potential arguments. Used to maintain
* constant function prototype.
* Return: Always 0
*/
char **s_get_environment(info_t *info)
{
if (!info->environment || info->environment_changed)
{
info->environment = list_to_strings(info->env);
info->environment_changed = 0;
}
return (info->environment);
}
 
/**
 * _unset_environment_variable - Remove an environment variable
 * @info: Structure containing potential arguments. Used to maintain
 * constant function prototype.
 * @var: the string env var property to remove
 * Return: 1 on delete, 0 otherwise
 */
int _unset_environment_variable(info_t *info, char *var)
{
    list_t *current_node = info->env;
    size_t index = 0;
    char *property;

    if (!current_node || !var)
        return (0);

    while (current_node)
    {
        property = startsWith(current_node->str, var);

        if (property && *property == '=')
        {
            info->env_changed = delete_node_at_index(&(info->env), index);
            index = 0;
            current_node = info->env;
            continue;
        }

        current_node = current_node->next;
        index++;
    }

    return (info->env_changed);
}

/**
* s_set_environment_variable - Initialize a new environment variable,
* or modify an existing one
* @info: Structure containing potential arguments. Used to maintain
* constant function prototype.
* @variable: the string environment variable property
* @value: the string environment variable value
* Return: Always 0
*/
int s_set_environment_variable(info_t *info, char *variable, char *value)
{
char *buffer = NULL;
list_t *node;
char *ptr;

if (!variable || !value)
return (0);

buffer = malloc(_strlen(variable) + _strlen(value) + 2);

if (!buffer)
return (1);

_strcpy(buffer, variable);
_strcat(buffer, "=");
_strcat(buffer, value);

node = info->env;

while (node)
{
ptr = startsWith(node->str, variable);

if (ptr && *ptr == '=')
{
free(node->str);
node->str = buffer;
info->environment_changed = 1;
return (0);
}

node = node->next;
}

add_node_end(&(info->env), buffer, 0);
free(buffer);
info->environment_changed = 1;

return (0);
}
