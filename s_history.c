#include "shell.h"

/**
* get_history_file - gets the history file
* @info: parameter struct
*
* Return: allocated string containing history file
*/
char *get_history_file(info_t *info)
{
    char *history_dir, *history_file_path;
    history_dir = s_get_env_value(info, "HOME=");
    if (!history_dir)
        return (NULL);
    history_file_path = malloc(sizeof(char) * (_strlen(history_dir) + _strlen(HIST_FILE) + 2));
    if (!history_file_path)
        return (NULL);
    history_file_path[0] = 0;
    _strcpy(history_file_path, history_dir);
    _strcat(history_file_path, "/");
    _strcat(history_file_path, HIST_FILE);
    return (history_file_path);
}

/**
* write_history - creates a file, or appends to an existing file
* @info: the parameter struct
*
* Return: 1 on success, else -1
*/
int write_history(info_t *info)
{
    ssize_t history_fd;
    char *history_filename = get_history_file(info);
    list_t *history_node = NULL;
    if (!history_filename)
        return (-1);
    history_fd = open(history_filename, O_CREAT | O_TRUNC | O_RDWR, 0644);
    free(history_filename);
    if (history_fd == -1)
        return (-1);
    for (history_node = info->history; history_node; history_node = history_node->next)
    {
        _putsfd(history_node->str, history_fd);
        _putfd('\n', history_fd);
    }
    _putfd(BUF_FLUSH, history_fd);
    close(history_fd);
    return (1);
}

/**
* read_history - reads history from file
* @info: the parameter struct
*
* Return: histcount on success, 0 otherwise
*/
int read_history(info_t *info)
{
    int i, last = 0, line_count = 0;
    ssize_t history_fd, read_len, file_size = 0;
    struct stat file_stat;
    char *history_buffer = NULL, *history_filename = get_history_file(info);
    if (!history_filename)
        return (0);
    history_fd = open(history_filename, O_RDONLY);
    free(history_filename);
    if (history_fd == -1)
        return (0);
    if (!fstat(history_fd, &file_stat))
        file_size = file_stat.st_size;
    if (file_size < 2)
        return (0);
    history_buffer = malloc(sizeof(char) * (file_size + 1));
    if (!history_buffer)
        return (0);
    read_len = read(history_fd, history_buffer, file_size);
    history_buffer[file_size] = 0;
    if (read_len <= 0)
        return (free(history_buffer), 0);
    close(history_fd);
    for (i = 0; i < file_size; i++)
    {
        if (history_buffer[i] == '\n')
        {
            history_buffer[i] = 0;
            build_history_list(info, history_buffer + last, line_count++);
            last = i + 1;
        }
    }
    if (last != i)
        build_history_list(info, history_buffer + last, line_count++);
    free(history_buffer);
    info->histcount = line_count;
    while (info->histcount-- >= HIST_MAX)
        delete_node_at_index(&(info->history), 0);
    renumber_history(info);
    return (info->histcount);
}

/**
* build_history_list - adds entry to a history linked list
* @info: Structure containing potential arguments. Used to maintain
* @buf: buffer
* @line_count: the history line_count, histcount
*
* Return: Always 0
*/
int build_history_list(info_t *info, char *buf, int line_count)
{
    list_t *history_node = NULL;
    if (info->history)
        history_node = info->history;
    add_node_end(&history_node, buf, line_count);
    if (!info->history)
        info->history = history_node;
    return (0);
}

/**
* renumber_history - renumbers the history linked list after changes
* @info: Structure containing potential arguments. Used to maintain
*
* Return: the new histcount
*/
int renumber_history(info_t *info)
{
    list_t *history_node = info->history;
    int i = 0;
    while (history_node)
    {
        history_node->num = i++;
        history_node = history_node->next;
    }
    return (info->histcount = i);
}

