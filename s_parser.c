#include "shell.h"

/**
* isExecutableCommand - determines if a file is an executable command
* @info: the info struct
* @filePath: path to the file
*
* Return: 1 if true, 0 otherwise
*/
int isExecutableCommand(info_t *info, char *filePath)
{
struct stat fileStat;
(void)info;

if (!filePath || stat(filePath, &fileStat))
return (0);

if (fileStat.st_mode & S_IFREG)
{
return (1);
}
return (0);
}

/**
* copyCharacters - duplicates characters from a string
* @sourceString: the source string
* @startIndex: starting index
* @stopIndex: stopping index
*
* Return: pointer to new buffer
*/
char *copyCharacters(char *sourceString, int startIndex, int stopIndex)
{
static char buffer[1024];
int j = 0;
int i = 0;
for (i = startIndex; i < stopIndex; i++)
{
if (sourceString[i] != ':')
{
buffer[j++] = sourceString[i];
}
}
buffer[j] = '\0';
return (buffer);
}

/**
* findExecutablePath - finds the executable command in the PATH string
* @info: the info struct
* @pathString: the PATH string
* @command: the command to find
*
* Return: full path of the command if found, or NULL
*/
char *findExecutablePath(info_t *info, char *pathString, char *command)
{
int i = 0, currentPosition = 0;
char *path;

if (!pathString)
return (NULL);

if ((_strlen(command) > 2) && startsWith(command, "./"))
{
if (isExecutableCommand(info, command))
return (command);
}

while (1)
{
if (!pathString[i] || pathString[i] == ':')
{
path = copyCharacters(pathString, currentPosition, i);

if (!*path)
_strcat(path, command);
else
{
_strcat(path, "/");
_strcat(path, command);
}

if (isExecutableCommand(info, path))
return (path);

if (!pathString[i])
break;

currentPosition = i;
}
i++;
}
return (NULL);
}

