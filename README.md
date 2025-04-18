# Simple Shell

A simple UNIX command line interpreter implementation.

## Description

This shell is a simple command line interpreter that can execute commands entered by the user. It supports both interactive and non-interactive modes.

## Features

- Display a prompt and wait for user input
- Execute commands
- Handle errors
- Handle end-of-file condition (Ctrl+D)
- Supports both interactive and non-interactive modes

## Requirements

- Ubuntu 20.04 LTS
- GCC compiler with options `-Wall -Werror -Wextra -pedantic -std=gnu89`

## Compilation

```bash
gcc -Wall -Werror -Wextra -pedantic -std=gnu89 *.c -o hsh
```

## Usage

### Interactive Mode

```bash
./hsh
$ /bin/ls
hsh main.c main.h shell_utils.c
$ exit
```

### Non-Interactive Mode

```bash
echo "/bin/ls" | ./hsh
hsh main.c main.h shell_utils.c
```

## Learning Objectives

### UNIX History

- **Original Unix Operating System**: Designed and implemented by Ken Thompson and Dennis Ritchie at Bell Labs in the early 1970s.
- **First UNIX Shell**: Written by Ken Thompson.
- **B Programming Language**: Invented by Ken Thompson, it was the direct predecessor to the C programming language.
- **Ken Thompson**: A pioneer in computer science who co-created the Unix operating system, the B programming language, and contributed to the development of the C programming language with Dennis Ritchie.

### Shell Concepts

- **How a Shell Works**: A shell is a program that provides an interface for users to interact with the operating system. It reads commands from input, interprets them, and executes the corresponding programs.
- **PID and PPID**: 
  - PID (Process ID): A unique identifier assigned to each process in the system.
  - PPID (Parent Process ID): The PID of the process that created the current process.
- **Environment Manipulation**: The environment of a process can be accessed and modified through the `environ` global variable or functions like `getenv()` and `setenv()`.
- **Function vs System Call**: 
  - Function: A routine that executes in user space.
  - System Call: A controlled entry point into the kernel, providing access to resources like hardware and file systems.
- **Process Creation**: Processes are created using the `fork()` system call, which creates a copy of the calling process.
- **Main Prototypes**: 
  - `int main(void)`
  - `int main(int argc, char *argv[])`
  - `int main(int argc, char *argv[], char *envp[])`
- **PATH Usage**: The shell uses the PATH environment variable to locate executable programs by searching each directory listed in the PATH.
- **Executing Programs**: Programs are executed using the `execve()` system call, which replaces the current process image with a new one.
- **Process Suspension**: A process can suspend execution until one of its children terminates using functions like `wait()`, `waitpid()`, `wait3()`, or `wait4()`.
- **EOF (End-of-File)**: A condition that indicates no more data can be read from a data source. In terminal input, it's typically triggered by pressing Ctrl+D.

## Authors

[Your Name]
