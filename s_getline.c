#include "shell.h"


/**
* s_input_buffer - buffers chained commands
* @info: parameter struct
* @command_buffer: address of buffer
* @buffer_length: address of length variable
*
* Return: bytes read
*/
ssize_t s_input_buffer(info_t *info, char **command_buffer, size_t *buffer_length)
{
ssize_t bytes_read = 0;
size_t length_p = 0;

if (!*buffer_length)
{
free(*command_buffer);
*command_buffer = NULL;
signal(SIGINT, s_sigint_handler);

#if USE_GETLINE
bytes_read = getline(command_buffer, &length_p, stdin);
#else
bytes_read = s_get_line(info, command_buffer, &length_p);
#endif

if (bytes_read > 0)
{
if ((*command_buffer)[bytes_read - 1] == '\n')
{
(*command_buffer)[bytes_read - 1] = '\0';
bytes_read--;
}

info->lineCountFlag = 1;
s_remove_comments(*command_buffer);
build_history_list
(info, *command_buffer, info->histcount++);


{
*buffer_length = bytes_read;
info->cmd_buf = command_buffer;
}
}
}

return (bytes_read);
}

/**
* s_get_input_line - gets a line minus the newline
* @info: parameter struct
*
* Return: bytes read
*/
ssize_t s_get_input_line(info_t *info)
{
static char *command_buffer;
static size_t i, j, length;
ssize_t bytes_read = 0;
char **current_command = &(info->arg);
char *current_position;
_putchar(BUF_FLUSH);
bytes_read = s_input_buffer(info, &command_buffer, &length);

if (bytes_read == -1)
return (-1);

if (length)
{
j  = i;
current_position = command_buffer + i;
checkChain(info, command_buffer, &j, i, length);

while (j < length)
{
if (isChainDelimiter(info, command_buffer, &j))
break;

j++;
}

i = j + 1;

if (i >= length)
{
i = length = 0;
info->cmd_buf_type = CMD_NORM;
}

*current_command = current_position;
return _strlen(current_position);
}

*current_command = command_buffer;
return (bytes_read);
}

/**
* s_read_buffer - reads a buffer
* @info: parameter struct
* @buf: buffer
* @i: size
*
* Return: r
*/
ssize_t s_read_buffer(info_t *info, char *buff, size_t *len)
{
ssize_t bytes_read = 0;

if (*len)
return (0);

bytes_read = read(info->readfd, buff, READ_BUF_SIZE);

if (bytes_read >= 0)
*len = bytes_read;

return (bytes_read);
}

/**
* s_get_line - gets the next line of input from STDIN
* @info: parameter struct
* @ptr: address of pointer to buffer, preallocated or NULL
* @length: size of preallocated ptr buffer if not NULL
*
* Return: s
*/
int s_get_line(info_t *info, char **ptr, size_t *length)
{
static char buffer[READ_BUF_SIZE];
static size_t buffer_index, buffer_length;
size_t buffer_offset;
ssize_t read_result = 0, line_length = 0;
char *current_ptr = NULL, *new_ptr = NULL, *newline_ptr;

current_ptr = *ptr;

if (current_ptr && length)
line_length = *length;

if (buffer_index == buffer_length)
{
buffer_index = buffer_length = 0;
read_result = s_read_buffer(info, buffer, &buffer_length);

if (read_result == -1 || (read_result == 0 && buffer_length == 0))
return (-1);

newline_ptr = s_strchr(buffer + buffer_index, '\n');
buffer_offset = newline_ptr ? 1 + (size_t)(newline_ptr - buffer) : buffer_length;

new_ptr = customRealloc(current_ptr, line_length, line_length ? line_length + buffer_offset : buffer_offset + 1);

if (!new_ptr)
return (current_ptr ? free(current_ptr), -1 : -1);

if (line_length)
s_strncat(new_ptr, buffer + buffer_index, buffer_offset - buffer_index);
else
s_strncpy(new_ptr, buffer + buffer_index, buffer_offset - buffer_index + 1);

line_length += buffer_offset - buffer_index;
buffer_index = buffer_offset;
current_ptr = new_ptr;

if (length)
*length = line_length;
}

*ptr = current_ptr;
return (line_length);
}

/**
* s_sigint_handler - handles the SIGINT signal (Ctrl-C)
* @sig_num: the signal number
*
* Return: void
*/
void s_sigint_handler(__attribute__((unused)) int sig_num)
{
_puts("\n");
_puts("$ ");
_putchar(BUF_FLUSH);
}

