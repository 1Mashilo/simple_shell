#include "shell.h"

/**
* s_exit - exits the shell
* @info: Structure containing potential arguments. Used to maintain
* constant function prototype.
* Return: exits with a given exit status
* (0) if info->argv[0] != "exit"
*/
int s_exit(info_t *info)
{
int exit_status;

if (info->argv[1])
{
exit_status = s_erratoi(info->argv[1]);
if (exit_status == -1)
{
info->status = 2;
s_print_error(info, "Illegal number: ");
_eputs(info->argv[1]);
_eputchar('\n');
return (1);
}
info->err_num = exit_status;
return (-2);
}
info->err_num = -1;
return (-2);
}

/**
* s_cd - changes the current directory of the process
* @info: Structure containing potential arguments. Used to maintain
* constant function prototype.
* Return: Always 0
*/
int s_cd(info_t *info)
{
char *current_directory, *new_directory;
char buffer[1024];
int chdir_result;

current_directory = getcwd(buffer, 1024);
if (!current_directory)
_puts("TODO: >>getcwd failure emsg here<<\n");

if (!info->argv[1])
{
new_directory = s_get_env_value(info, "HOME=");
if (!new_directory)
chdir_result = chdir((new_directory = s_get_env_value(info, "PWD=")) ? new_directory : "/");
else
chdir_result = chdir(new_directory);
}
else if (_strcmp(info->argv[1], "-") == 0)
{
if (!s_get_env_value(info, "OLDPWD="))
{
_puts(current_directory);
_putchar('\n');
return (1);
}
_puts(s_get_env_value(info, "OLDPWD="));
_putchar('\n');
chdir_result = chdir((new_directory = s_get_env_value(info, "OLDPWD=")) ? new_directory : "/");
}
else
{
chdir_result = chdir(info->argv[1]);
}

if (chdir_result == -1)
{
s_print_error(info, "can't cd to ");
_eputs(info->argv[1]);
_eputchar('\n');
}
else
{
s_set_environment_variable(info, "OLDPWD", s_get_env_value(info, "PWD="));
s_set_environment_variable(info, "PWD", getcwd(buffer, 1024));
}

return (0);
}

/**
* s_help - displays a help message for the shell
* @info: Structure containing potential arguments. Used to maintain
* constant function prototype.
* Return: Always 0
*/
int s_help(info_t *info)
{
char **arguments = info->argv;

_puts("Help function is not yet implemented.\n");
if (0)
_puts(*arguments);

return (0);
}


/**
* unset_alias - unsets an alias
* @info: Parameter struct
* @alias_str: The alias to unset
*
* Return: Always 0 on success, 1 on error
*/
int s_unset_alias(info_t *info, char *alias_str)
{
char *equals_sign, saved_char;
int ret;

equals_sign =s_strchr(alias_str, '=');
if (!equals_sign)
return (1);

saved_char = *equals_sign;
*equals_sign = '\0';

ret = delete_node_at_index(&(info->alias),
get_node_index(info->alias, node_starts_with(info->alias, alias_str, -1)));

*equals_sign = saved_char;
return (ret);
}

