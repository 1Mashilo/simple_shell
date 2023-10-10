# 0x16. C - Simple Shell

## Description

This project is an implementation of a simple shell created as a Milestone Project for the C code at ALX Africa Software Engineering. The "Gates of Shell" is a project in the first trimester that helps students understand the advanced concepts behind the shell program, including process management, system calls, bit manipulation, file management, and error handling. This shell is a simple UNIX command interpreter that replicates the functionalities of the simple shell (sh). The program was written entirely in the C language.

## COPYRIGHT

Copyright (C) 2023 by Mashilo Kgaladi. All rights reserved.

## Environment

Shell was built and tested on Ubuntu 14.04 LTS.

## Features

- Display a prompt and wait for the user to type a command. A command line always ends with a new line.
- If an executable cannot be found, print an error message and display the prompt again.
- Handle errors.
- Handle the "end of file" condition (Ctrl+D).
- Handle the command line with arguments.
- Handle the PATH.
- Support the exit feature and the exit status.
- Handle Ctrl-C to not terminate the shell.
- Handle the command separator `;`.
- Handle `&&` and `||` logical operators.
- Handle variable replacements `$?` and `$$`.
- Handle comments `#`.
- Support the history feature.
- Support file input.

## Builtins

Shell has support for the following built-in commands:

| Command          | Definition                                                      |
|------------------|------------------------------------------------------------------|
| `exit [n]`       | Exit the shell, with an optional exit status, n.                |
| `env`            | Print the environment.                                           |
| `setenv [var][value]` | Set an environment variable and value. If the variable exists, the value will be updated. |
| `alias[name[='value]]` | Reads aliases name.                                        |
| `unsetenv [var]` | Remove an environment variable.                                   |
| `cd [dir]`       | Change the directory.                                            |
| `help [built-in]` | Read documentation for a built-in.                              |

## Installation: Getting Simple Shell

Clone the repository using the following command:

```shell
git clone https://github.com/1Mashilo/simple_shell.git

Compile the files into an executable using the GCC compiler:
gcc -Wall -Werror -Wextra -pedantic *.c -o hsh

To run the shell, use the following command:
./hsh

**Example**

```shell
$ ls -la
total 112
drwxrwxr-x 3 user user   4096 Sep 26 10:00 .
drwxrwxr-x 8 user user   4096 Sep 26 09:55 ..
-rw-rw-r-- 1 user user    819 Sep 26 10:00 file1.c
-rw-rw-r-- 1 user user    820 Sep 26 10:00 file2.c
-rw-rw-r-- 1 user user    818 Sep 26 10:00 file3.c
-rw-rw-r-- 1 user user   1738 Sep 26 10:00 holberton.h
-rw-rw-r-- 1 user user    780 Sep 26 10:00 README.md
-rwxrwxr-x 1 user user  15544 Sep 26 10:00 simple_shell
-rw-rw-r-- 1 user user   1142 Sep 26 10:00 string_functions.c
-rw-rw-r-- 1 user user    431 Sep 26 10:00 string_functions.h
$

**Contributors**

Mashilo Kgaladi

**Acknowledgments**

- The creators of the C language.
- Our software engineer-in-residence.
- Holberton college| Alx-Africa.

