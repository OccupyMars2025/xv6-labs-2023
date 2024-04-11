#include "kernel/types.h"
#include "kernel/stat.h"
#include "kernel/fcntl.h"
#include "user/user.h"

int
statistics(void *buf, int sz)
{
  int fd, i, n;
  // Is "statistics" a device ? After debugging open(), I'm sure it is a device located in the root directory. Execute "ls" command in the root directory, you should see "statistics" with other files like "cat", "README", "ls" and so on.
  fd = open("statistics", O_RDONLY);
  if(fd < 0) {
      fprintf(2, "stats: open failed\n");
      exit(1);
  }
  for (i = 0; i < sz; ) {
    if ((n = read(fd, buf+i, sz-i)) < 0) {
      break;
    }
    i += n;
  }
  close(fd);
  return i;
}
