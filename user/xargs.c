// ====================== implementation 1
/*
$ (echo 1; echo 2) | xargs echo ok
*/

#include "kernel/types.h"
#include "kernel/stat.h"
#include "user/user.h"
#include "kernel/fs.h"
#include "kernel/fcntl.h"
#include "kernel/param.h"


int main(int argc, char *argv[])
{
  if (argc < 2) {
    fprintf(2, "Usage: xargs <command> [args...]\n");
    exit(1);
  }
  char buf[512];
  char *p = buf;
  char ch;

  char* new_argv[MAXARG];
  if(argc + 1 >= MAXARG) {
    fprintf(2, "xargs: too many arguments\n");
    exit(1);
  }
  for(int i = 1; i < argc; ++i) {
    new_argv[i-1] = argv[i];
  }
  // Caution: content of buf may change
  new_argv[argc - 1] = buf;
  new_argv[argc] = 0;

  while (read(0, &ch, 1) == 1)
  {
    if('\n' != ch) {
      *p++ = ch;
    } else {
      *p = '\0';
      int pid = fork();
      if(0 == pid) {
        exec(argv[1], new_argv);

        printf("exec() failed\n");
        exit(1);
      } else {
        wait(0);
      }

      p = buf;
    }
  }
  
  exit(0);
}


// ====================== implementation 2

// #include "kernel/types.h"
// #include "kernel/stat.h"
// #include "user/user.h"
// #include "kernel/fs.h"
// #include "kernel/fcntl.h"
// #include "kernel/param.h"


// int main(int argc, char *argv[]) {
//     if (argc < 2) {
//         fprintf(2, "Usage: xargs <command> [args...]\n");
//         exit(1);
//     }

//     // // Wrong! You cannot concatenate all arguments with " " as the separator
//     // char command[512];
//     // strcpy(command, argv[1]);
//     // // Copy additional command-line arguments
//     // for (int i = 2; i < argc; i++) {
//     //     strcpy(command + strlen(command), " ");
//     //     strcpy(command + strlen(command), argv[i]);
//     // }
//     // strcpy(command + strlen(command), " ");
//     // char *p = command + strlen(command);

//     char line[512];

//     char* new_argv[MAXARG];
//     if(argc + 1 >= MAXARG) {
//       fprintf(2, "xargs: too many arguments\n");
//       exit(1);
//     }
//     for(int i = 1; i < argc; ++i) {
//       new_argv[i-1] = argv[i];
//     }
//     // Caution: content of buf may change
//     new_argv[argc - 1] = line;
//     new_argv[argc] = 0;
    

//     // Read lines from standard input and run the command for each line
//     while (1) {
//         gets(line, sizeof(line));
//         if((line[0] == '\n') || (line[0] == '\r') || (line[0] == '\0')) {
//           break;
//         }
//         // Remove newline character from the end of the line
//         line[strlen(line) - 1] = 0;

//         // Fork a new process to execute the command
//         int pid = fork();
//         if (pid < 0) {
//             fprintf(2, "xargs: fork() failed\n");
//             exit(1);
//         } else if (pid == 0) {
//             // Child process: execute the command
//             exec(argv[1], new_argv);

//             fprintf(2, "xargs: exec() failed\n");
//             exit(1);
//         } else {
//             // Parent process: wait for the child to complete
//             wait(0);
//         }
//     }

//     exit(0);
// }
