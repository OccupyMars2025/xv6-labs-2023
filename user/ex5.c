
#include "kernel/types.h"
#include "user/user.h"

// ex5.c: fork then exec

int
main()
{
  int pid, status;

  pid = fork();
  if(pid == 0){
    char *argv[] = { "echo", "THIS", "IS", "ECHO", 0 };
    exec("echo", argv);
    printf("exec failed!\n");
    exit(1);
  } else {
    printf("parent waiting\n");
    wait(&status);
    printf("the child exited with status %d\n", status);
  }

  exit(0);
}




// #include "kernel/types.h"
// #include "user/user.h"

// int main()
// {
//   int pid = fork();

//   if(0 == pid) {
//     char* argv[] = {"echo", "hello", "ex5", 0};
//     exec("echo", argv);

//     printf("exec() failed\n");
//     exit(1);
//   } else {
//     int exit_status;
//     pid = wait(&exit_status);
//     printf("parent: child(pid=%d, exit status=%d) is done\n", pid, exit_status);
//   }

//   exit(0);
// }
