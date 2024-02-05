/*
https://pdos.csail.mit.edu/6.1810/2023/labs/util.html
*/

#include "kernel/types.h"
#include "user/user.h"

int main(int argc, char const *argv[])
{
  if(argc != 2) {
    fprintf(2, "Usage: sleep <ticks>\n");
    exit(1);
  }

  int ticks = atoi(argv[1]);
  // printf("sleep %d ticks\n", ticks);
  sleep(ticks);

  exit(0);
}
