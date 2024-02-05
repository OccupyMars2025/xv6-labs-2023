/**
* example: ex2.c, create a file
  open() creates (or opens) a file, returns a file descriptor (or -1 for error)
  FD is a small integer
  FD indexes into a per-process table maintained by kernel
  [user/kernel diagram]
  $ ex2
  $ cat out
  different processes have different FD name-spaces
    e.g. FD 3 usually means different things to different processes
  these examples ignore errors -- don't be this sloppy!
  Figure 1.2 in the xv6 book lists system call arguments/return
    or look at UNIX man pages, e.g. "man 2 open"
*/


// ex2.c: create a file, write to it.

// #include "kernel/types.h"
// #include "user/user.h"
// #include "kernel/fcntl.h"

// int
// main()
// {
//   int fd = open("out", O_WRONLY | O_CREATE | O_TRUNC);

//   printf("open returned fd %d\n", fd);

//   write(fd, "ooo\n", 4);

//   exit(0);
// }



#include "kernel/types.h"
#include "user/user.h"
#include "kernel/fcntl.h"

int main()
{
  printf("Enter the name of a new file:\n");
  char filename[64];
  read(0, filename, sizeof(filename));
  printf("length of filename: %d\n", strlen(filename));
  /*
  delete '\n'
  if you don't do it, use "$ ls", you can see the difference, 
  and "cat" cannot open the file
  */
  filename[strlen(filename) - 1] = '\0'; 

  int fd = open(filename, O_CREATE | O_WRONLY | O_TRUNC);
  printf("open() return fd=%d\n", fd);

  char file_content[] = "hello ex2\n";
  write(fd, file_content, strlen(file_content));
  // write(fd, "hi\n", 3);

  exit(0);
}

