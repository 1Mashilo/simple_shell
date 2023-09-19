#include "shell.h"

/**
 * ss_exit - Exits the shell.
 */
void ss_exit()
{
    exit(0);
}

int exit_status = 0;

/**
 * ss_set_status - Set the exit status of the shell.
 * @status: The exit status to set.
 */
void ss_set_status(int status) 
{
    exit_status = status;
}
