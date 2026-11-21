# Virtual File System

A command-line virtual file system implemented in C++. The project models core Unix file-system concepts entirely in memory and demonstrates how file metadata, file descriptors, permissions, and data blocks are managed.

## Features

- Inode and inode table simulation
- Super block and disk inode list
- User file descriptor table
- Regular file creation and deletion
- Read, write, truncate, seek, and close operations
- File and file-descriptor statistics
- Interactive command-line interface

## Technologies

- C++
- C standard library
- Custom linked-list and table structures
- Unix-like file-system concepts

## Project Structure

```text
Virtual-File-System/
├── CVFS.cpp
└── README.md
```

## Build

Linux or WSL:

```bash
g++ -std=c++17 -Wall -Wextra -pedantic CVFS.cpp -o cvfs
./cvfs
```

MinGW on Windows:

```powershell
g++ -std=c++17 -Wall -Wextra -pedantic CVFS.cpp -o cvfs.exe
.\cvfs.exe
```

## Available Commands

| Command | Description |
|---|---|
| `create <name> <permission>` | Create a regular file. Permissions: `1` read, `2` write, `3` read/write |
| `open <name> <permission>` | Open a file and receive a file descriptor |
| `close <name>` | Close an open file by name |
| `closeall` | Close all open files |
| `read <name> <bytes>` | Read bytes from an open file |
| `write <name>` | Prompt for and write data to an open file |
| `lseek <fd> <offset> <from>` | Change a file descriptor offset |
| `stat <name>` | Display file metadata |
| `fstat <fd>` | Display metadata using a file descriptor |
| `truncate <name>` | Remove file contents |
| `rm <name>` | Delete a file |
| `ls` | List active files |
| `clear` | Clear the terminal |
| `help` | Display command help |
| `man <command>` | Display details for a command |
| `exit` | Exit the program |

## Example

```text
VFS : > create report.txt 3
file is successfully created with file descriptor : 0

VFS : > open report.txt 3
file is successfully opened with file descriptor : 0

VFS : > write report.txt
Enter the data :
Virtual file system test

VFS : > read report.txt 23
Virtual file system test

VFS : > ls
VFS : > stat report.txt
VFS : > close report.txt
VFS : > exit
```

## Architecture

The project uses a fixed maximum of 50 inodes and a maximum file size of 1048 bytes.

- `INODE` stores file metadata and an allocated data buffer.
- `SUPERBLOCK` tracks total and free inode counts.
- `FILETABLE` stores file mode and read/write offsets.
- `UFDTArr` acts as the user file descriptor table.
- `head` links all allocated and available inode records.

## Limitations

- File data exists only in memory and is lost when the program exits.
- The implementation is a simulation rather than a kernel file system.
- Maximum inode count is fixed at 50.
- Maximum file size is fixed at 1048 bytes.
- The interactive interface should receive additional input validation.

## Reference

Linux System Programming by Robert Love
