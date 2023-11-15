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

/* Constants for read/write buffers */
#define READ_BUF_SIZE 1024
#define WRITE_BUF_SIZE 1024
#define BUF_FLUSH -1

/* Constants for command chaining */
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

/* External environment variable declaration */
extern char **environ;

/**
 * struct alias - Represents an alias in the shell program.
 * @name: The name of the alias.
 * @value: The value associated with the alias.
 * @next: Pointer to the next alias in the linked list.
 */
typedef struct alias
{
    char *name;
    char *value;
    struct alias *next;
} alias_t;

/**
 * struct liststr - Singly linked list structure.
 * @num: The number field.
 * @str: A string.
 * @next: Pointer to the next node.
 */
typedef struct liststr
{
    int num;
    char *str;
    struct liststr *next;
} list_t;

/**
 * struct passinfo - Contains pseudo-arguments to pass into a function,
 * allowing a uniform prototype for a function pointer struct.
 * @history_file: History file path.
 * @history: History linked list.
 * @lineCountFlag: Flag for line count.
 * @err_num: Error code for exit()s.
 * @argv: Array of strings generated from arguments.
 * @path: Current command path.
 * @lineCount: Line count.
 * @histcount: History count.
 * @get_environ: Environment variables.
 * @status: Return status of the last exec'd command.
 * @arguments: Additional arguments.
 * @program_name: Program name.
 * @executable_path: Executable path.
 * @argument_vector: Argument vector.
 * @cmd_buf_type: Command buffer type.
 * @alias: The alias node.
 * @arg: A string generated from getline containing arguments.
 * @env: Linked list environment.
 * @environ: Custom modified copy of environ from linked list env.
 * @fname: The program filename.
 * @argc: The argument count.
 * @environment: Environment variables.
 * @env_changed: Environment change flag.
 * @environment_changed: Environment change flag.
 * @cmd_buf: Command buffer.
 * @readfd: File descriptor for reading.
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

/* Initialization macro for info_t structure */
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
 * struct builtin - Contains a built-in command string and related function.
 * @type: The built-in command string.
 * @func: The associated function.
 */
typedef struct builtin
{
    char *type;
    int (*func)(info_t *);
} builtin_table;

/* Main shell function */
int hsh(info_t *, char **);

/* Loop to continuously process shell commands */
int loophsh(char **);

/* Built-in command functions */
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

/* String manipulation functions */
int stringCompare(char *s1, char *s2);
int stringLength(char *s);
char *stringConcatenate(char *dest, char *src);
char *s_strchr(char *str, char c);
char **s_get_environment(info_t *info);

/* Environment variable functions */
int _unset_environment_variable(info_t *info, char *var);
int s_set_environment_variable(info_t *info, char *variable, char *value);

/* Initialization and memory functions */
void initialize_info(info_t *info);
void populate_info(info_t *info, char **av);
void free_info(info_t *info, int free_environ);
ssize_t s_get_input_line(info_t *info);

/* Linked list operations */
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

/* Input and output operations */
int is_interactive(info_t *info);
int is_delimiter(char c, char *delimiters);
int is_alpha(int c);
int string_to_integer(char *s);
int find_buitin(info_t *info);
void find_cmd(info_t *info);
void fork_cmd(info_t *info);

/* Standard C library functions */
int _strlen(char *s);
int _strcmp(char *string1, char *s2);
char *_strcat(char *destination, char *src);
char *_strcpy(char *dest, char *src);
char *_strdup(const char *str);
int _putchar(char c);

/* String manipulation and parsing */
char **splitString(char *str, char *delimiters);
int _strlen(char *s);
bfree(void **);

/* File I/O functions */
ssize_t s_read_buffer(info_t *info, char *buff, size_t *len);
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

