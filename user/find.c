// ====================== implementation 1
#include "kernel/types.h"
#include "kernel/stat.h"
#include "user/user.h"
#include "kernel/fs.h"
#include "kernel/fcntl.h"

void find(const char *path, const char* filename) {

  struct stat st;
  if(stat(path, &st) < 0) {
    fprintf(2, "find: cannot stat %s\n", path);
    // exit(1);
    return;
  }

  if((st.type == T_DEVICE) || (st.type == T_FILE)) {
    if(strlen(path) >= strlen(filename)) {
      if(strcmp(path + strlen(path) - strlen(filename), filename) == 0) {
        printf("%s\n", path);
      }
    }
  } else {
    // "path" refers to a directory
    struct dirent de;
    char deeper_path[512];
    if(strlen(path) + 1 + DIRSIZ + 1 > sizeof(deeper_path)) {
      printf("find: path too long!\n");
      return;
    }
    char *p;
    strcpy(deeper_path, path);
    p = deeper_path + strlen(deeper_path);
    *p++ = '/';

    int fd = open(path, O_RDONLY);
    if(fd < 0) {
      fprintf(2, "find: cannot open the directory %s\n", path);
      exit(1);
    }
    while (read(fd, &de, sizeof(de)) == sizeof(de))
    {
      if(de.name[0] != '\0') {
        if((strcmp(de.name, ".") == 0) || (strcmp(de.name, "..") == 0)) {
          continue;
        }
        strcpy(p, de.name);
        // printf("go into deeper path: %s\n", deeper_path);
        // recursive call
        find(deeper_path, filename);
      }
    }
    close(fd);
  }

}


int main(int argc, char const *argv[])
{
  if(3 != argc) {
    fprintf(2, "Usage: find <path> <filename>\n");
    exit(1);
  }

  find(argv[1], argv[2]);

  exit(0);
}


// // ====================== implementation 2 

// #include "kernel/types.h"
// #include "kernel/stat.h"
// #include "user/user.h"
// #include "kernel/fs.h"
// #include "kernel/fcntl.h"

// void find(char *path, const char *target) {
//     char buf[512], *p;
//     int fd;
//     struct dirent de;
//     struct stat st;

//     if ((fd = open(path, O_RDONLY)) < 0) {
//         fprintf(2, "find: cannot open %s\n", path);
//         return;
//     }

//     if (fstat(fd, &st) < 0) {
//         fprintf(2, "find: cannot stat %s\n", path);
//         close(fd);
//         return;
//     }

//     switch (st.type) {
//         case T_DEVICE:
//         case T_FILE:
//             if(strlen(path) >= strlen(target)) {
//               if(strcmp(path + strlen(path) - strlen(target), target) == 0) {
//                 printf("%s\n", path);
//               }
//             }
//             break;

//         case T_DIR:
//             if (strlen(path) + 1 + DIRSIZ + 1 > sizeof(buf)) {
//                 printf("find: path too long\n");
//                 break;
//             }
//             strcpy(buf, path);
//             p = buf + strlen(buf);
//             *p++ = '/';
//             while (read(fd, &de, sizeof(de)) == sizeof(de)) {
//                 if (de.inum == 0 || strcmp(de.name, ".") == 0 || strcmp(de.name, "..") == 0) {
//                     continue;
//                 }
//                 memmove(p, de.name, DIRSIZ);
//                 p[DIRSIZ] = 0;
//                 find(buf, target);
//             }
//             break;
//     }

//     close(fd);
// }

// int main(int argc, char *argv[]) {
//     if (argc != 3) {
//         fprintf(2, "Usage: find <path> <target>\n");
//         exit(1);
//     }

//     find(argv[1], argv[2]);

//     exit(0);
// }
