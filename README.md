# Unix-like Shell (Zombie Child Shell)

## Overview

This project is a simple Unix-like shell, known as the "Zombie Child Shell" (ZCS), implemented in C. The shell supports internal commands like `word`, `dir`, and `date`, `ls`, as well as the ability to execute external commands. It provides various functions for command parsing, file operations, argument validation, and process management.

## Commands

### 1. Word Command

- **Description**: Counts words in a text file.
- **Syntax**: `word [-n|-d] [file_name]`
- **Options**:
  - `-n`: Ignores newline characters.
  - `-d`: Calculates the difference between word counts in two text files.

### 2. Dir Command

- **Description**: Creates a new directory and changes the current path.
- **Syntax**: `dir [-r|-v] [dir_name]`
- **Options**:
  - `-r`: Removes the directory if it exists and creates a new one.
  - `-v`: Displays messages for each step.

### 3. Date Command

- **Description**: Returns the last modified date and time of a file.
- **Syntax**: `date [-d|-R] [file_name]`
- **Options**:
  - `-d`: Display time described by STRING.
  - `-R`: Output date and time in RFC 5322 format.

### 4. Ls Command

- **Description**: Lists content of the current working directory
- **Syntax**: `ls [-a|-l]`
- **Options**:
  - `-l`: Lists the directory contents in a long listed format.
  - `-a`: Lists all the directory contents, including hidden files.

## Examples

- Count words in a file: `word file.txt`
- Count words ignoring newline characters: `word -n file.txt`
- Find the difference in word counts: `word -d file1.txt file2.txt`
- Create a directory: `dir new_dir`
- Create with removal if exists and verbose: `dir -rv existing_dir`
- Get last modified date and time: `date file.txt`
- Display time in a custom format: `date -d "2023-09-23 14:30:00" file.txt`
- Output in RFC 5322 format: `date -R file.txt`
- List contents of current working directory: `ls`
- List contents of current working directory with information: `ls -l`
- List all contents, including hidden files: `ls -a`
