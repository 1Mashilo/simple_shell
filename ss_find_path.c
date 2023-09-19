#include "shell.h"

/**
* ss_find_path - Finds the full path of a command
* in the PATH variable.
* @pathstring: The PATH variable containing
* directories separated by ':'.
* @command: The command to find.
*
* Return: The full path of the command if found, or NULL if not found.
*/
char *ss_find_path(const char *pathstring, const char *command)
{
char *path = NULL;
char *full_path = NULL;
const char *delimiter = ":";
char *pathstring_copy;
char *token;

if (!pathstring)
{
return (NULL);
}
if (ss_command(command))
{
return (ss_strdup(command));
}
pathstring_copy = ss_strdup(pathstring);
if (pathstring_copy == NULL)
{
perror("Memory allocation failed");
exit(EXIT_FAILURE);
}
token = strtok(pathstring_copy, delimiter);
while (token)
{
if (token[0] != '\0')
{
full_path = ss_strconcat(token, "/", command);
if (ss_command(full_path))
{
path = ss_strdup(full_path);
free(full_path);
free(pathstring_copy);
return (path);
}
free(full_path);
}
token = strtok(NULL, delimiter);
}
free(pathstring_copy);
return (NULL);
}

/**
* ss_command - Check if a file is executable.
* @file_path: The path to the file to check.
*
* Return: 1 if the file is executable, 0 otherwise.
*/
int ss_command(const char *file_path)
{
if (access(file_path, X_OK) == 0)
{
return (1);
}
return (0);
}

