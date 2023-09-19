#include "shell.h"

/**
* ss_free_env_list - Frees memory used by the environment list.
* @env_list: Pointer to the head of the linked list.
*/
void ss_free_env_list(env_node_t *env_list)
{
env_node_t *temp;
while (env_list != NULL)
{
temp = env_list;
env_list = env_list->next;
free(temp->data);
free(temp);
}
}

