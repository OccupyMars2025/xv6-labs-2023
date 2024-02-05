
// ex3.c: create a new process with fork()

#include "kernel/types.h"
#include "user/user.h"

int
main()
{
  int pid;

  pid = fork();

  printf("fork() returned %d\n", pid);

  if(pid == 0){
    printf("child\n");
  } else {
    printf("parent: child pid = %d\n", pid);
  }
  
  exit(0);
}


// #include "kernel/types.h"
// #include "user/user.h"

// int main()
// {
//   int pid = fork();

//   if(0 == pid) {
//     printf("child: \n");
//     exit(23);
//   } else {
//     printf("parent: child pid = %d\n", pid);
//     int status;
//     pid = wait(&status);
//     printf("parent: child (pid=%d, exit status=%d) is done\n", pid, status);
//   }

//   exit(0);
// }

