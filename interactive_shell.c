#include "shell.h"

/**
 * interactive_shell - Handles the shell in interactive mode.
 *
 * Return: The exit status of the shell.
 */
int interactive_shell(void)
{
    int exit_status = 0;
    char *command_line = NULL;
    env_node_t *env_list = NULL;
    
    char *parsed_input[2];

    env_list = ss_convert_to_env_node_t(environ);

    while (1)
    {
        ssize_t read_result;

        display_prompt("($) ");
        read_result = read_command_line(STDIN_FILENO, &command_line);

        if (read_result != -1)
        {
            if (ss_strncmp(command_line, "exit", 4) == 0)
            {
                free(command_line);
                break;
            }

            parsed_input[0] = command_line;
            parsed_input[1] = NULL;
            handle_input(parsed_input, env_list);
            free(command_line);
        }
        else
        {
            break;
        }
    }

    ss_free_env_list(env_list);
    return (exit_status);
}

