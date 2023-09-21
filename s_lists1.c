#include "shell.h"

/**
 * list_len - determines the length of a linked list
 * @head: pointer to the first node
 *
 * Return: size of the list
 */
size_t list_len(const list_t *head)
{
    size_t count = 0;
    while (head)
    {
        head = head->next;
        count++;
    }
    return (count);
}

/**
 * list_to_strings - returns an array of strings from the list->str
 * @head: pointer to the first node
 *
 * Return: array of strings
 */
char **list_to_strings(list_t *head)
{
    list_t *node = head;
    size_t list_size = list_len(head);
    char **strings;
    char *str;
    size_t j = 0;
    size_t i = 0;

    if (!head || !list_size)
        return (NULL);

    strings = malloc(sizeof(char *) * (list_size + 1));
    if (!strings)
        return (NULL);

    for (i = 0; node; node = node->next, i++)
    {
        str = malloc(_strlen(node->str) + 1);
        if (!str)
        {
            for (j = 0; j < i; j++)
                free(strings[j]);
            free(strings);
            return (NULL);
        }
        _strcpy(str, node->str);
        strings[i] = str;
    }
    strings[list_size] = NULL;
    return (strings);
}

/**
 * print_list - prints all elements of a list_t linked list
 * @head: pointer to the first node
 *
 * Return: size of the list
 */
size_t print_list(const list_t *head)
{
    size_t count = 0;
    while (head)
    {
        _puts(s_convert_number(head->num, 10, 0));
        _putchar(':');
        _putchar(' ');
        _puts(head->str ? head->str : "(nil)");
        _puts("\n");
        head = head->next;
        count++;
    }
    return (count);
}

/**
 * node_starts_with - returns the node whose string starts with a prefix
 * @node: pointer to list head
 * @prefix: string to match
 * @next_char: the next character after the prefix to match
 *
 * Return: matching node or null
 */
list_t *node_starts_with(list_t *node, char *prefix, char next_char)
{
    char *p = NULL;
    while (node)
    {
        p = startsWith(node->str, prefix);
        if (p && ((next_char == -1) || (*p == next_char)))
            return (node);
        node = node->next;
    }
    return (NULL);
}

/**
 * get_node_index - gets the index of a node
 * @head: pointer to list head
 * @node: pointer to the node
 *
 * Return: index of the node or -1
 */
ssize_t get_node_index(list_t *head, list_t *node)
{
    size_t index = 0;
    while (head)
    {
        if (head == node)
            return (index);
        head = head->next;
        index++;
    }
    return (-1);
}

