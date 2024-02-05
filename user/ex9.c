
#include "kernel/types.h"
#include "user/user.h"
#include "kernel/fs.h"
#include "kernel/fcntl.h"

// ex9.c: list file names in the current directory

int
main()
{
  int fd;
  struct dirent e;

  fd = open(".", O_RDONLY);
  while(read(fd, &e, sizeof(e)) == sizeof(e)){
    if(e.name[0] != '\0'){
      printf("%s\n", e.name);
    }
  }
  exit(0);
}







// #include "kernel/types.h"
// #include "user/user.h"
// #include "kernel/fs.h"
// #include "kernel/fcntl.h"


// int main() {
//   int fd = open(".", O_RDONLY);
//   int num_dirent = 0, num_valid_dirent = 0;
//   struct dirent de;
//   while (read(fd, &de, sizeof(de)) == sizeof(de))
//   {
//     ++num_dirent;
//     if(de.name[0] != '\0') {
//       ++num_valid_dirent;
//       printf("%s\n", de.name);
//     }
//   }
//   close(fd);

//   printf("\n\nnum_dirent = %d \nnum_valid_dirent = %d\n", num_dirent, num_valid_dirent);

//   exit(0);
// }
