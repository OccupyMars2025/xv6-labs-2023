
// ex7.c: communication over a pipe

#include "kernel/types.h"
#include "user/user.h"

int
main()
{
  int fds[2];
  char buf[100];
  int n;

  // create a pipe, with two FDs in fds[0], fds[1].
  pipe(fds);
  
  // write to the pipe
  write(fds[1], "xyz\n", 4);

  // read from the pipe
  n = read(fds[0], buf, sizeof(buf));

  // display the results on the terminal
  write(1, buf, n);

  exit(0);
}









// #include "kernel/types.h"
// #include "user/user.h"


// int main()
// {
//   int pipe_fd[2];

//   pipe(pipe_fd);

//   char message01[64] = "hello ex7";
//   char message02[64];
//   write(pipe_fd[1], message01, strlen(message01));
//   read(pipe_fd[0], message02, sizeof(message02));

//   printf("The received message:\n%s\n", message02);

//   exit(0);
// }
