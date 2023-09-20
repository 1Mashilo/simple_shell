#include "shell.h"

/**
 * handle_input - Handles the execution of a parsed command line.
 * @parsed_input: An array of strings containing the parsed command line.
 * @env_list: A linked list of environment variables.
 *
 * Return: The exit status of the executed command, or -1 on error.
 */
int handle_input(char **parsed_input, env_node_t *env_list)
{
    char *command;
    int exit_status;
    char error_msg[256];
    int len = 0;

    if (parsed_input == NULL || parsed_input[0] == NULL)
        return 0;

    command = parsed_input[0];

    if (ss_strcmp(command, "exit") == 0)
    {
        ss_exit();
    }
    else if (ss_strcmp(command, "env") == 0)
    {
        ss_env(env_list);
    }
    else
    {
        exit_status = ss_execute_command(parsed_input, env_list);
        if (exit_status == -1)
        {
            char *program_name = "hsh";
            int line_number = 1;
	    char *result;
            char int_string[20];

            int_string[0] = '\0'; 
            ss_int_string(line_number, int_string);
            
            result = ss_strcpy(error_msg, program_name);
            len += ss_strlen(result);
            
            error_msg[len] = ':';
            error_msg[len + 1] = ' ';
            len += 2;

            result = ss_strcpy(error_msg + len, int_string);
            len += ss_strlen(result);

            error_msg[len] = ':';
            error_msg[len + 1] = ' ';
            len += 2;

            result = ss_strcpy(error_msg + len, command);
            len += ss_strlen(result);

            error_msg[len] = ':';
            error_msg[len + 1] = ' ';
            len += 2;

            result = ss_strcpy(error_msg + len, "not found\n");
            len += ss_strlen(result);

            write(2, error_msg, len);
            return -1;
        }
    }
    return 0;
}

