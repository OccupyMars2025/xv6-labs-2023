// ex4.c: replace a process with an executable file

#include "kernel/types.h"
#include "user/user.h"

int
main()
{
  char *argv[] = { "echo", "this", "is", "echo", 0 };

  exec("echo", argv);

  printf("exec failed!\n");

  exit(0);
}


// #include "kernel/types.h"
// #include "user/user.h"

// int main(int argc, char const *argv[])
// {
//   // Caution: don't forget to add "0"
//   char* argument_array[] = {"echo", "hello", "ex4", 0};
//   exec("echo", argument_array);

//   printf("exec() failed!\n");

//   exit(0);
// }
