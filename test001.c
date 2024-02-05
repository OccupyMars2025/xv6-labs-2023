/**
 * xv6-riscv-book, page 11, chapter 1
 * 
 * gcc test001.c -o test001
*/

#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <sys/wait.h>

/*
The wait system call returns the PID of an exited (or killed) child of
the current process and copies the exit status of the child to the address passed to wait; if none of
the caller’s children has exited, wait waits for one to do so. If the caller has no children, wait
immediately returns -1. If the parent doesn’t care about the exit status of a child, it can pass a 0
address to wait.
*/
int main(int argc, char const *argv[])
{
    int pid = fork();
    if(pid > 0){
        printf("parent: child=%d\n", pid);
        int status;
        // pid = wait((int *) 0);
        pid = wait(&status);
        printf("parent: child %d is done with status %d\n", pid, status);
    } else if(pid == 0){
        printf("child: exiting\n");
        exit(0);
    } else {
        printf("fork error\n");
    }

    return 0;
}




// #include <stdio.h>
// #include <stdlib.h>
// #include <unistd.h>
// #include <sys/wait.h>

// int main() {
//     pid_t child_pid;

//     child_pid = fork();

//     if (child_pid == -1) {
//         perror("fork");
//         return 1;
//     }

//     if (child_pid == 0) {
//         // This code is executed by the child process
//         printf("Child process\n");
//     } else {
//         // This code is executed by the parent process
//         printf("Parent process\n");

//         // Wait for the child process to finish
//         int status;
//         wait(&status);
//     }

//     // Both processes continue from here

//     return 0;
// }
