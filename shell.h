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

typedef struct env_node {
    char *data;
    struct env_node *next;
} env_node_t;

void display_prompt(const char *prompt);
void ss_free_env_list(env_node_t *env_list);
ssize_t read_command_line(int file_descriptor, char **output_line);
void ss_exit();
int ss_find_builtin(char **argv, env_node_t *env_list);
void ss_env(env_node_t *env_list);
int ss_execute_command(char **argv, env_node_t *env_list);
char *ss_find_command(const char *pathstring, const char *command);
char *ss_getenv(env_node_t *env_list, const char *var_name);
env_node_t *ss_convert_to_env_node_t(char **environ);
size_t ss_print_env_list(env_node_t *env_list);
void ss_add_to_env_list(env_node_t **env_list, const char *env_var);
char **env_list_to_char_array(env_node_t *env_list);

int ss_strncmp(const char *string1, const char *string2, size_t n);
size_t ss_strlen(const char *string);
char *ss_strcpy(char *dest, const char *src);
int ss_strcmp(const char *string1, const char *string2);
char *ss_strdup(const char *string);
char *ss_strconcat(const char *string1, const char *sep, const char *string2);
void ss_int_string(int num, char *str);
int ss_command(const char *file_path);

size_t count_words(const char *str);
void free_parsed_input(char **parsed_input);
int execute_shell(int input_fd);
void handle_input(const char *command_line, env_node_t *env_list);
char **ss_parse_input(const char *input);
char *ss_find_path(const char *pathstring, const char *command);
void handle_builtin_commands(char **parsed_input, env_node_t *env_list, int *builtin_return);

#endif

