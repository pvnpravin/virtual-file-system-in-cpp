# 🗂️ Customized Virtual File System (VFS)

![Language](https://img.shields.io/badge/Language-C%2B%2B-blue)
![Type](https://img.shields.io/badge/Project-System%20Programming-orange)
![Platform](https://img.shields.io/badge/Platform-Linux%20%7C%20Windows-lightgrey)
![Status](https://img.shields.io/badge/Status-Stable-success)

---

# 📌 Overview

This project implements a **Customized Virtual File System (VFS)** inspired by how operating systems manage files internally.

The system simulates core operating system file system components including:

* Superblock
* Inodes
* File Tables
* User File Descriptor Table (UFDT)

Users interact with the system using command‑line instructions similar to a real operating system.

The entire file system runs **in memory**, making it useful for learning **Operating System file system architecture and system programming concepts**.

---

# 🧠 Key Operating System Concepts

This project demonstrates:

* Inode based file system
* File descriptor management
* File permissions
* File offset manipulation (lseek)
* Linked list inode management
* Dynamic memory allocation
* Virtual file storage

---

# 🏗️ System Architecture

```
+-------------------+
|   User Commands   |
+-------------------+
          |
          ▼
+-------------------+
| Command Parser    |
+-------------------+
          |
          ▼
+-------------------+
|   UFDT Table      |
| (File Descriptors)|
+-------------------+
          |
          ▼
+-------------------+
|    File Table     |
| (Offsets & Mode)  |
+-------------------+
          |
          ▼
+-------------------+
|      Inodes       |
| (File Metadata)   |
+-------------------+
          |
          ▼
+-------------------+
|   Memory Buffer   |
| (Actual File Data)|
+-------------------+
```

---

# 📂 Core Data Structures

## Superblock

Stores global information about the file system.

```
Total Inodes
Free Inodes
```

---

## Inode

Each file is represented by an inode which stores metadata about the file.

```
FileName
InodeNumber
FileSize
FileActualSize
FileType
LinkCount
ReferenceCount
Permission
Buffer Pointer
```

---

## UFDT (User File Descriptor Table)

Maps file descriptors to file tables.

```
File Descriptor -> File Table
```

---

## File Table

Stores runtime information about file access.

```
Read Offset
Write Offset
Mode
Reference Count
Pointer to Inode
```

---

# ⚙️ Features

The system supports the following commands:

| Command  | Description                                    |
| -------- | ---------------------------------------------- |
| create   | Create a new file                              |
| open     | Open an existing file                          |
| read     | Read file data                                 |
| write    | Write data into file                           |
| ls       | List all files                                 |
| stat     | Display file information using file name       |
| fstat    | Display file information using file descriptor |
| truncate | Remove data from file                          |
| rm       | Delete file                                    |
| close    | Close file                                     |
| closeall | Close all open files                           |
| lseek    | Change file offset                             |
| help     | Display help information                       |
| exit     | Terminate the virtual file system              |

---

# 💻 Example Execution

```
Customized VFS : > create test.txt 3
File successfully created with file descriptor : 0

Customized VFS : > write test.txt
Enter the data:
Hello Virtual File System

Customized VFS : > read test.txt 10
Hello Virt

Customized VFS : > ls

File name   Inode number   File size   Link count
-------------------------------------------------
test.txt    1              100         1
```

---

# 📊 System Limitations

| Parameter         | Value        |
| ----------------- | ------------ |
| Maximum Inodes    | 5            |
| Maximum File Size | 100 bytes    |
| Storage Type      | Memory Based |

---

# 🚀 Build & Run

## Clone Repository

```
git clone https://github.com/yourusername/customized-virtual-file-system.git
```

## Compile

```
g++ vfs.cpp
```

## Run

```
./a.out
```

---

# 🧪 Test Commands

```
create file1.txt 3
write file1.txt
read file1.txt 10
ls
stat file1.txt
rm file1.txt
```

---

# 🎯 Learning Outcomes

After completing this project you will understand:

* File system architecture
* Inode structure
* File descriptor tables
* File offset handling
* System programming concepts
* Memory management in file systems

---

# 📐 Inode Layout Diagram

```
+-----------------------+
| File Name             |
| Inode Number          |
| File Size             |
| Actual File Size      |
| Permission            |
| Link Count            |
| Reference Count       |
| Buffer Pointer        |
+-----------------------+
```

---

# 👨‍💻 Author

Pravin

Backend Developer
React Developer
System Programming Enthusiast

---

# ⭐ Support

If you found this project useful, consider giving the repository a **star ⭐ on GitHub**.

---

# 📜 License

This project is created for **educational purposes** to understand operating system file system concepts.
