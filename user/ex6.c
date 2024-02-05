
// #include "kernel/types.h"
// #include "user/user.h"
// #include "kernel/fcntl.h"

// // ex6.c: run a command with output redirected

// int
// main()
// {
//   int pid;

//   pid = fork();
//   if(pid == 0){
//     close(1);
//     open("out", O_WRONLY | O_CREATE | O_TRUNC);

//     char *argv[] = { "echo", "this", "is", "redirected", "echo", 0 };
//     exec("echo", argv);
//     printf("exec failed!\n");
//     exit(1);
//   } else {
//     wait((int *) 0);
//   }

//   exit(0);
// }










#include "kernel/types.h"
#include "kernel/fcntl.h"
#include "user/user.h"

int main()
{
  int pid = fork();

  if(0 == pid) {
    close(1);
    open("out", O_CREATE | O_WRONLY | O_TRUNC);
    char* argv[] = {"echo", "hello", "ex6", 0};
    exec("echo", argv);

    printf("exec() failed\n");
    exit(1);
  } else {
    int exit_status;
    pid = wait(&exit_status);
    printf("parent: child(pid=%d, exit status=%d) is done\n", pid, exit_status);
  }

  exit(0);
}
