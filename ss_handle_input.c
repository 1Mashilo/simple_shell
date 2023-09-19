#include "shell.h"

/**
 * handle_input - Process and execute a command line input.
 * @command_line: The input command line.
 * @env_list: The environment variable list.
 */
void handle_input(const char *command_line, env_node_t *env_list)
{
    char **parsed_input;
    char *command;
    int exit_status;

    parsed_input = ss_parse_input(command_line);
    if (parsed_input != NULL) {
        command = parsed_input[0];

        if (command != NULL) {
            if (ss_strcmp(command, "exit") == 0) {
                ss_exit();
            } else if (ss_strcmp(command, "env") == 0) {
                ss_env(env_list);
            } else {
                
                exit_status = ss_execute_command(parsed_input, env_list);
                if (exit_status == -1) {
                    perror("Error executing the command");
                }
                
            }
        }

        free_parsed_input(parsed_input);
    }
}

