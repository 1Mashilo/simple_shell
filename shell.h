#ifndef SHELL_H
#define SHELL_H

#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>
#include <stdarg.h>
#include <fcntl.h>
#include <unistd.h>
#include <sys/stat.h>
#include <sys/wait.h>

#define BUF_FLUSH '\0'
#define MAX_INPUT_SIZE 1024
#define WRITE_BUF_SIZE 1024
extern char **environ;

/**
 * struct env_node - Represents a node in the environment variable
 * linked list.
 * @data: The data (environment variable) stored in the node.
 * @next: A pointer to the next node in the linked list.
 */

typedef struct env_node
{
char *data;
struct env_node *next;
}
env_node_t;

int interactive_shell(void);

char *ss_strdup(const char *string);
char *ss_strconcat(const char *string1, const char *sep, const char *string2);
char *ss_strcpy(char *dest, const char *src);
size_t ss_strlen(const char *string);
int ss_strcmp(const char *string1, const char *string2);
int ss_strncmp(const char *string1, const char *string2, size_t n);
void free_parsed_input(char **parsed_input);
char **env_list_to_char_array(env_node_t *env_list);
char *ss_strcat(const char *string1, const char *string2);


void ss_exit(void);
int ss_find_builtin(char **argv, env_node_t *env_list);
void ss_env(env_node_t *env_list);
int ss_execute_command(char **argv, env_node_t *env_list);
char *ss_find_command(const char *pathstring, const char *command);
char *ss_getenv(env_node_t *env_list, const char *var_name);
env_node_t *ss_convert_to_env_node_t(char **environ);
size_t ss_print_env_list(env_node_t *env_list);
void ss_add_to_env_list(env_node_t **env_list, const char *env_var);

int ss_command(const char *file_path);
size_t count_words(const char *str);

int execute_shell(int input_fd);
int handle_input(char **parsed_input, env_node_t *env_list);
char **ss_parse_input(const char *input);
char *ss_find_path(const char *pathstring, const char *command);
void s_builtin(char **parsed_input, env_node_t *env_list, int *builtin_return);

void display_prompt(const char *prompt);
ssize_t read_command_line(int file_descriptor, char **output_line);
void ss_int_string(int num, char *str);

void ss_free_env_list(env_node_t *env_list);

#endif

