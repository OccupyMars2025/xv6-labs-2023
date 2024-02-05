#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>

int main() {
    pid_t child_pid;

    child_pid = fork();

    if (child_pid == -1) {
        perror("fork");
        return 1;
    }

    if (child_pid == 0) {
        // This code is executed by the child process
        printf("Child process\n");

        /*
        Most programs ignore the first element of the argument array,
        which is conventionally the name of the program.
        so "ls" and "echo" are ignored
        */
        // Replace the child process with a new program using execl
        // execl("/bin/ls", "ls", "-l", (char *)NULL);
        execl("/bin/echo", "echo", "hello", "world", "C++", (char *)NULL);

        // If execl fails
        perror("execl");
        exit(EXIT_FAILURE);
    } else {
        // This code is executed by the parent process
        printf("Parent process: child pid=%d\n", child_pid);

        // Wait for the child process to finish
        int status;
        child_pid = wait(&status);
        printf("Parent process: child %d is done with exit status %d\n", child_pid, status);
    }

    // Both processes continue from here

    return 0;
}
