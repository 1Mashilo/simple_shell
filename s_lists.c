#include "shell.h"

/**
* add_node - adds a node to the start of the list
* @head: address of pointer to head node
* @str_value: string value of the node
* @index: node index used by history
*
* Return: pointer to the new node
*/
list_t *add_node(list_t **head, const char *str_value, int index)
{
list_t *new_node;
if (!head)
return (NULL);

new_node = malloc(sizeof(list_t));
if (!new_node)
return (NULL);

setMemory((void *)new_node, 0, sizeof(list_t));
new_node->num = index;

if (str_value)
{
new_node->str = _strdup(str_value);
if (!new_node->str)
{
free(new_node);
return (NULL);
}
}

new_node->next = *head;
*head = new_node;
return (new_node);
}

/**
* add_node_end - adds a node to the end of the list
* @head: address of pointer to head node
* @str_value: string value of the node
* @index: node index used by history
*
* Return: pointer to the new node
*/
list_t *add_node_end(list_t **head, const char *str_value, int index)
{
list_t *new_node, *node;
if (!head)
return (NULL);

node = *head;
new_node = malloc(sizeof(list_t));
if (!new_node)
return (NULL);

setMemory((void *)new_node, 0, sizeof(list_t));
new_node->num = index;

if (str_value)
{
new_node->str = _strdup(str_value);
if (!new_node->str)
{
free(new_node);
return (NULL);
}
}

if (node)
{
while (node->next)
node = node->next;
node->next = new_node;
}
else
*head = new_node;

return (new_node);
}

/**
* print_list_str - prints only the str element of a list_t linked list
* @head: pointer to the first node
*
* Return: size of the list
*/
size_t print_list_str(const list_t *head)
{
size_t count = 0;
while (head)
{
_puts(head->str ? head->str : "(nil)");
_puts("\n");
head = head->next;
count++;
}
return (count);
}

/**
* delete_node_at_index - deletes node at a given index
* @head: address of pointer to the first node
* @index: index of the node to delete
*
* Return: 1 on success, 0 on failure
*/
int delete_node_at_index(list_t **head, unsigned int index)
{
list_t *node, *prev_node;
unsigned int i = 0;

if (!head || !*head)
return (0);

if (!index)
{
node = *head;
*head = (*head)->next;
free(node->str);
free(node);
return (1);
}

node = *head;
while (node)
{
if (i == index)
{
prev_node->next = node->next;
free(node->str);
free(node);
return (1);
}
i++;
prev_node = node;
node = node->next;
}
return (0);
}

/**
* free_list - frees all nodes of a list
* @head_ptr: address of pointer to the head node
*
* Return: void
*/
void free_list(list_t **head_ptr)
{
list_t *node, *next_node, *head;

if (!head_ptr || !*head_ptr)
return;

head = *head_ptr;
node = head;
while (node)
{
next_node = node->next;
free(node->str);
free(node);
node = next_node;
}

*head_ptr = NULL;
}

