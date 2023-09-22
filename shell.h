#ifndef _SHELL_H_
#define _SHELL_H_

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <sys/stat.h>
#include <limits.h>
#include <fcntl.h>
#include <errno.h>

/* for read/write buffers */
#define READ_BUF_SIZE 1024
#define WRITE_BUF_SIZE 1024
#define BUF_FLUSH -1

/* for command chaining */
#define CMD_NORM 0
#define CMD_OR 1
#define CMD_AND 2
#define CMD_CHAIN 3

#define CONVERT_LOWERCASE 1
#define CONVERT_UNSIGNED 2

#define USE_GETLINE 0
#define USE_STRTOK 0

#define HIST_FILE ".simple_shell_history"
#define HIST_MAX 4096
#define WRITE_BUFFER_SIZE 1024
#define BUFFER_FLUSH -1
extern char **environ;

typedef struct alias {
    char *name;
    char *value;
    struct alias *next;
} alias_t;


/**
 * struct liststr - singly linked list
 * @num: the number field
 * @str: a string
 * @next: points to the next node
 */
typedef struct liststr
{
    int num;
    char *str;
    struct liststr *next;
} list_t;

/**
 * struct passinfo - contains pseudo-arguments to pass into a function,
 * allowing a uniform prototype for a function pointer struct
 * @history_file: history file path
 * @history: history linked list
 * @lineCountFlag: flag for line count
 * @err_num: the error code for exit()s
 * @argv: array of strings generated from arguments
 * @path: current command path
 * @lineCount: line count
 * @histcount: history count
 * @get_environ: environment variables
 * @status: return status of the last exec'd command
 * @arguments: additional arguments
 * @program_name: program name
 * @executable_path: executable path
 * @argument_vector: argument vector
 * @cmd_buf_type: command buffer type
 * @alias:the  alias node
 * @arg: a string generated from getline containing arguements
 * @env: linked list environ 
 * @environ:custom modified copy of environ fromm LL env 
 * fname: the program filename
 * @argc:the argument count
 * @environment: environment variables
 * @environment_changed: environment change flag
 */
typedef struct passinfo
{
    char *history_file;
    list_t *history;
    int lineCountFlag;
    char **argv;
    int argc;
    char *arg;
    char *path;
    char *fname;
    int linecount;
    int histcount;
    char **environ;
    int err_num;
    char **get_environ;
    int status;
    char *arguments;
    char *program_name;
    char *executable_path;
    char **argument_vector;
    int cmd_buf_type;
    list_t *alias;
    list_t *env;
    char **environment;
    int env_changed;
    int environment_changed;
    char **cmd_buf;
    int readfd;
} info_t;

#define INFO_INIT \
{ \
    NULL,        /* history_file */ \
    NULL,        /* history */ \
    0,           /* lineCountFlag */ \
    NULL,        /* argv */ \
    0,           /* argc */ \
    NULL,        /* arg */ \
    NULL,        /* path */ \
    NULL,        /* fname */ \
    0,           /* linecount */ \
    0,           /* histcount */ \
    NULL,        /* environ */ \
    0,           /* err_num */ \
    NULL,        /* get_environ */ \
    0,           /* status */ \
    NULL,        /* arguments */ \
    NULL,        /* program_name */ \
    NULL,        /* executable_path */ \
    NULL,        /* argument_vector */ \
    0,           /* cmd_buf_type */ \
    NULL,        /* alias */ \
    NULL,        /* env */ \
    NULL,        /* environment */ \
    0,           /* env_changed */ \
    0,           /* environment_changed */ \
    NULL,        /* cmd_buf */ \
    0            /* readfd */ \
}


/**
 * struct builtin - contains a built-in command string and related function
 * @type: the built-in command string
 * @func: the associated function
 */
typedef struct builtin
{
    char *type;
    int (*func)(info_t *);
} builtin_table;

int hsh(info_t *, char **);
int loophsh(char **);
int s_set_alias(info_t *info, char *alias_str);
int s_print_alias(list_t *node);
int s_myalias(info_t *info);
int s_exit(info_t *info);
int s_cd(info_t *info);
int s_help(info_t *info);
int s_history(info_t *info);
int s_unset_alias(info_t *info, char *alias_str);
int s_erratoi(char *str);
void s_print_error(info_t *info, char *error_str);
int s_print_d(int d, int fd);
char *s_convert_number(long int num, int base, int flags);
void s_remove_comments(char *str);
char *_strdup(const char *str);
void _puts(char *str);
int _putchar(char c);
int _putsfd(char *str, int fd);
int _putfd(char c, int fd);
int _eputchar(char c);
void _eputs(char *str);
void s_sigint_handler(__attribute__((unused)) int sig_num);
ssize_t s_input_buffer(info_t *info, char **command_buffer, size_t *buffer_length);
char *startsWith(const char *haystack, const char *needle);
char *s_strncpy(char *destination, char *source, int num);
char *s_strncat(char *destination, char *source, int num);
int stringCompare(char *s1, char *s2);
int stringLength(char *s);
char *stringConcatenate(char *dest, char *src);
char *s_strchr(char *str, char c);
char **s_get_environment(info_t *info);
int _unset_environment_variable(info_t *info, char *var);
int s_set_environment_variable(info_t *info, char *variable, char *value);
void initialize_info(info_t *info);
void populate_info(info_t *info, char **av);
void free_info(info_t *info, int free_environ);
 ssize_t s_get_input_line(info_t *info);
ssize_t s_read_buffer(info_t *info, char *buff, size_t *len);
 int s_get_line(info_t *info, char **ptr, size_t *length);
size_t list_len(const list_t *list);
char **list_to_strings(list_t *head);
size_t print_list(const list_t *list);
list_t *node_starts_with(list_t *node, char *prefix, char next_char);
ssize_t get_node_index(list_t *head, list_t *node);
list_t *add_node(list_t **list, const char *str, int num);
list_t *add_node_end(list_t **list, const char *str, int num);
size_t print_list_str(const list_t *list);
int delete_node_at_index(list_t **list, unsigned int index);
void free_list(list_t **list);
int is_interactive(info_t *info);
int is_delimiter(char c, char *delimiters);
int is_alpha(int c);
int string_to_integer(char *s);
int find_buitin(info_t *info);
void find_cmd(info_t *info);
void fork_cmd(info_t *info);

int _strlen(char *s);
int _strcmp(char *string1, char *s2);
char *_strcat(char *destination, char *src);
char *_strcpy(char *dest, char *src);
char *_strdup(const char *str);
int _putchar(char c);
char **splitString(char *str, char *delimiters);
int _strlen(char *s);
int bfree(void **);
void ffree(char **ptr);



char *get_history_file(info_t *info);
int write_history(info_t *info);
int read_history(info_t *info);
int build_history_list(info_t *info, char *buf, int linecount);
int renumber_history(info_t *info);
int isChainDelimiter(info_t *info, char *buf, size_t *p);
void checkChain(info_t *info, char *buf, size_t *p, size_t i, size_t len);
int replaceAlias(info_t *info);
int replaceVars(info_t *info);
int replaceString(char **old, char *new);
void *customRealloc(void *previousBlock, unsigned int oldSize, unsigned int newSize);
void freeStringArray(char **stringArray);
char *setMemory(char *memoryBlock, char byteValue, unsigned int byteCount);
int s_env(info_t *info);
char *s_get_env_value(info_t *info, const char *name);
int s_mysetenv(info_t *info);
int s_myunsetenv(info_t *info);
int s_populate_env_list(info_t *info);
int isExecutableCommand(info_t *info, char *filePath);
char *copyCharacters(char *sourceString, int startIndex, int stopIndex);
char *findExecutablePath(info_t *info, char *pathString, char *command);



#endif


