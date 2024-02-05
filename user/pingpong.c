// #include "kernel/types.h"
// #include "user/user.h"

// int main() {
//   int pipe_from_parent_to_child[2];
//   int pipe_from_child_to_parent[2];
//   pipe(pipe_from_child_to_parent);
//   pipe(pipe_from_parent_to_child);

//   int pid = fork();
//   if(0 == pid) {
//     // child process
//     close(pipe_from_parent_to_child[1]);
//     close(pipe_from_child_to_parent[0]);

//     char byte;
//     int num_bytes = read(pipe_from_parent_to_child[0], &byte, sizeof(byte));
//     if(1 == num_bytes) {
//       printf("%d: received ping\n", getpid());
//       write(pipe_from_child_to_parent[1], &byte, sizeof(byte));
//     } else {
//       printf("%d: NOT received ping\n", getpid());
//       exit(1);
//     }
//   } else {
//     // parent process
//     close(pipe_from_parent_to_child[0]);
//     close(pipe_from_child_to_parent[1]);

//     write(pipe_from_parent_to_child[1], "A", 1);
//     char byte;
//     int num_bytes = read(pipe_from_child_to_parent[0], &byte, sizeof(byte));
//     if(1 == num_bytes) {
//       printf("%d: received pong\n", getpid());
//     } else {
//       printf("%d: NOT received pong\n", getpid());
//       exit(1);
//     }
//   }

//   exit(0);
// }




#include "kernel/types.h"
#include "user/user.h"

int main() {
    int parentToChild[2], childToParent[2];
    char buffer;

    // Create pipes
    if (pipe(parentToChild) < 0 || pipe(childToParent) < 0) {
        fprintf(2, "Pipe creation failed\n");
        exit(1);
    }

    // Fork to create a child process
    int pid = fork();

    if (pid < 0) {
        fprintf(2, "Fork failed\n");
        exit(1);
    }

    if (pid == 0) {
        // Child process
        close(parentToChild[1]);  // Close write end of parentToChild pipe
        close(childToParent[0]);  // Close read end of childToParent pipe

        // Receive byte from parent
        int num_bytes = read(parentToChild[0], &buffer, 1);

        if(1 == num_bytes) {
          // Print received message
          printf("%d: received ping\n", getpid());
          // Write the byte on the pipe to the parent
          write(childToParent[1], &buffer, 1);

          // Close pipes
          close(parentToChild[0]);
          close(childToParent[1]);

          exit(0);
        } else {
          printf("%d: NOT received ping\n", getpid());

          // Close pipes
          close(parentToChild[0]);
          close(childToParent[1]);

          exit(1);
        }
    } else {
        // Parent process
        close(parentToChild[0]);  // Close read end of parentToChild pipe
        close(childToParent[1]);  // Close write end of childToParent pipe

        // Send byte to child
        write(parentToChild[1], "A", 1);

        // // Wait for child to respond
        // wait(0);

        // Read the byte from the child
        int num_bytes = read(childToParent[0], &buffer, 1);

        if(1 == num_bytes) {
          // Print received message
          printf("%d: received pong\n", getpid());

          // Close pipes
          close(parentToChild[1]);
          close(childToParent[0]);

          exit(0);
        } else {
          printf("%d: NOT received pong\n", getpid());

          // Close pipes
          close(parentToChild[1]);
          close(childToParent[0]);

          exit(1);
        }
    }
}
