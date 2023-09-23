#include "shell.h"

/**
* hsh - main shell loop
* @info: the parameter & return info struct
* @argv: the argument vector from main()
*
* Return: 0 on success, 1 on error, or error code
*/

int hsh(info_t *info, char **argv)
{
ssize_t readResult = 0;
int builtinResult = 0;

while (readResult != -1 && builtinResult != -2)
{
initialize_info(info);
if (is_interactive(info))
_puts("$ ");
_eputchar(BUF_FLUSH);
readResult = s_get_input_line(info);
if (readResult != -1)

{
populate_info(info, argv);
builtinResult =  find_buitin(info);
if (builtinResult == -1)
find_cmd(info);
}
else if (is_interactive(info))
_putchar('\n');
free_info(info, 0);
}
write_history(info);
free_info(info, 1);
if (!is_interactive(info) && info->status)
exit(info->status);
if (builtinResult == -2)
{
if (info->err_num == -1)
exit(info->status);
exit(info->err_num);
}
return (builtinResult);
}

/**
* find_buitin - finds a builtin command
* @info: the parameter & return info struct
*
* Return: -1 if builtin not found,
* 0 if builtin executed successfully,
* 1 if builtin found but not successful,
* 2 if builtin signals exit()
*/
int find_buitin(info_t *info)
{
int i, builtinRet = -1;
builtin_table builtintbl[] = {
{"exit", s_exit},
{"env",  s_env},
{"help", s_help},
{"history", s_history},
{"setenv", s_mysetenv},
{"unsetenv",  s_myunsetenv},
{"cd", s_cd},
{"alias", s_myalias},
{NULL, NULL}
};

for (i = 0; builtintbl[i].type; i++)
if (_strcmp(info->argv[0], builtintbl[i].type) == 0)
{
info->linecount++;
builtinRet = builtintbl[i].func(info);
break;
}
return (builtinRet);
}

/**
* find_cmd - finds a command in PATH
* @info: the parameter & return info struct
*
* Return: void
*/
void find_cmd(info_t *info)
{
char *path = NULL;
int i, j;
info->path = info->argv[0];
if (info->lineCountFlag == 1)
{
info->linecount++;
info->lineCountFlag = 0;
}
for (i = 0, j = 0; info->arg[i]; i++)
if (!is_delimiter(info->arg[i], " \t\n"))
j++;

if (!j)
return;

path = findExecutablePath(info, s_get_env_value(info, "PATH="), info->argv[0]);
if (path)
{
info->path = path;
fork_cmd(info);
}
else
{
if ((is_interactive(info) || s_get_env_value(info, "PATH=") || info->argv[0][0] == '/') && isExecutableCommand(info, info->argv[0]))
fork_cmd(info);
else if (*(info->arg) != '\n')
{
info->status = 127;
s_print_error(info, "not found\n");
}
}
}

/**
* fork_cmd - forks an exec thread to run a command
* @info: the parameter & return info struct
*
* Return: void
*/
void fork_cmd(info_t *info)
{
pid_t childPid;
childPid = fork();
if (childPid == -1)
{
perror("Error:");
return;
}

if (childPid == 0)
{
if (execve(info->path, info->argv, s_get_environment(info)) == -1)
{
free_info(info, 1);
if (errno == EACCES)
exit(126);
exit(1);
}
}
else
{
wait(&(info->status));
if (WIFEXITED(info->status))
{
info->status = WEXITSTATUS(info->status);
if (info->status == 126)
s_print_error(info, "Permission denied\n");
}
}
}

