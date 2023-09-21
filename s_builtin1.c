#include "shell.h"

/**
* s_history - displays the history list, one command by line, preceded
* with line numbers, starting at 0.
* @info: Structure containing potential arguments. Used to maintain
* constant function prototype.
* Return: Always 0
*/
int s_history(info_t *info)
{
print_list(info->history);
return (0);
}

/**
* s_set_alias - sets an alias to a string
* @info: Parameter struct
* @alias_str: The alias string
*
* Return: Always 0 on success, 1 on error
*/
int s_set_alias(info_t *info, char *alias_str)
{
char *equals_sign;

equals_sign = s_strchr(alias_str, '=');
if (!equals_sign)
return (1);

if (!*++equals_sign)
return (s_unset_alias(info, alias_str));

s_unset_alias(info, alias_str);

return (add_node_end(&(info->alias), alias_str, 0) == NULL);
}

/**
* s_print_alias - prints an alias string
* @node: The alias node
*
* Return: Always 0 on success, 1 on error
*/
int s_print_alias(list_t *node)
{
char *alias_end = NULL, *alias_start = NULL;

if (node)
{
alias_end = s_strchr(node->str, '=');

for (alias_start = node->str; alias_start <= alias_end; alias_start++)
_putchar(*alias_start);

_putchar('\'');
_puts(alias_end + 1);
_puts("'\n");

return (0);
}

return (1);
}

/**
* s_myalias - mimics the alias builtin (man alias)
* @info: Structure containing potential arguments. Used to maintain
* constant function prototype.
* Return: Always 0
*/
int s_myalias(info_t *info)
{
int i = 0;
char *equals_sign = NULL;
list_t *node = NULL;

if (info->argc == 1)
{
node = info->alias;
while (node)
{
s_print_alias(node);
node = node->next;
}
return (0);
}

for (i = 1; info->argv[i]; i++)
{
equals_sign = s_strchr(info->argv[i], '=');
if (equals_sign)
s_set_alias(info, info->argv[i]);
else
s_print_alias(node_starts_with(info->alias, info->argv[i], '='));
}

return (0);
}

