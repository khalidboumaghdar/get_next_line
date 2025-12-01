# get_next_line

A project from **42 / 1337 Network** to read files **line by line** using C.  
This project teaches **memory management, static variables, file descriptors, and dynamic strings**.

---

## 📖 Description

`get_next_line()` reads a file **one line at a time**, returning a newly allocated string each call.  
The function handles:

- Any valid file descriptor
- Any `BUFFER_SIZE`
- Files of any length
- Multiple file descriptors simultaneously (bonus)

It uses a **static variable** to store leftover data between calls so the function can continue where it left off.

---

## 🎯 Learning Objectives

- Dynamic memory allocation
- String manipulation (`ft_strjoin`, `ft_substr`, `ft_strchr`, etc.)
- Static variables to maintain state
- Reading from file descriptors using `read()`
- Handling multiple file descriptors (bonus)
- Writing robust, leak-free C code

---

## ⚙️ Function Prototype

```c
char *get_next_line(int fd);

## ⭐ Bonus

## Support multiple file descriptors:

get_next_line(fd1);
get_next_line(fd2);
get_next_line(fd1);


## 📁 Project Structure

get_next_line/
│
├── get_next_line.c
├── get_next_line_utils.c
├── get_next_line_bonus.c
├── get_next_line_bonus_utils.c
├── get_next_line.h
├── get_next_line_bonus.h
└── README.md


## 🛠️ Compilation

cc -Wall -Wextra -Werror get_next_line.c get_next_line_utils.c

##  Bonus

cc -Wall -Wextra -Werror get_next_line_bonus.c get_next_line_bonus_utils.c
