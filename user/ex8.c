
#include "kernel/types.h"
#include "user/user.h"

// ex8.c: communication between two processes

int
main()
{
  int n, pid;
  int fds[2];
  char buf[100];
  
  // create a pipe, with two FDs in fds[0], fds[1].
  pipe(fds);

  pid = fork();
  if (pid == 0) {
    // child
    write(fds[1], "this is ex8\n", 12);
  } else {
    // parent
    n = read(fds[0], buf, sizeof(buf));
    write(1, buf, n);
  }

  exit(0);
}








// #include "kernel/types.h"
// #include "user/user.h"

// int main()
// {
//   int pipe_fd[2];
//   pipe(pipe_fd);

//   int pid = fork();
//   if(0 == pid) {
//     close(pipe_fd[1]);
//     char buf[100];
//     int num_bytes = read(pipe_fd[0], buf, sizeof(buf));
//     write(1, buf, num_bytes);
//   } else {
//     close(pipe_fd[0]);
//     char buf2[] = "hello ex8";
//     write(pipe_fd[1], buf2, strlen(buf2));

//     int exit_status;
//     pid = wait(&exit_status);
//     printf("\nparent: child(pid=%d, exit status=%d) is done\n", pid, exit_status);
//   }

//   exit(0);
// }
