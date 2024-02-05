// ex1.c: copy input to output.

#include "kernel/types.h"
#include "user/user.h"

// int
// main()
// {
//   char buf[64];

//   while(1){
//     int n = read(0, buf, sizeof(buf));
//     if(n <= 0)
//       break;
//     write(1, buf, n);
//   }

//   exit(0);
// }


int main() {
  char buf[512];
  int num_bytes;

  while ((num_bytes = read(0, buf, sizeof(buf))) > 0)
  {
    write(1, buf, num_bytes);
  }

  exit(0);
}
