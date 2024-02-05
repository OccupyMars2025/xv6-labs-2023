/**
 * Write a user-level program that uses xv6 system calls to ''ping-pong'' a byte between two processes over a pair of pipes, 
 * one for each direction. The parent should send a byte to the child; the child should print "<pid>: received ping", 
 * where <pid> is its process ID, write the byte on the pipe to the parent, and exit; the parent should read the byte from the child, 
 * print "<pid>: received pong", and exit. 
 * Your solution should be in the file user/pingpong.c.
*/


#include "kernel/types.h"
#include "user/user.h"

int
main(int argc, char *argv[])
{
    int fd_for_ping[2]; // info from parent to child
    int fd_for_pong[2]; // info from child to parent

    int count;
    int status;

    pipe(fd_for_ping);
    pipe(fd_for_pong);

    int pid = fork();
    if(0 == pid) {
        char buffer[100];
        count = read(fd_for_ping[0], buffer, sizeof(buffer));
        // printf("(child pid:%d): received ping, received-message=%s\n", getpid(), buffer);
    
        // use this printf to pass the test: $./grade-lab-util pingpong
        printf("%d: received ping\n", getpid());      
        
        write(fd_for_pong[1], buffer, count);
    } else {
        char buffer[100];
        char message[100] = "X";
        write(fd_for_ping[1], message, strlen(message));
        read(fd_for_pong[0], buffer, sizeof(buffer));
        wait(&status);
        // printf("(parent pid:%d): received pong, received-message=%s, wait-status=%d\n", getpid(), buffer, status);        
        
        // use this printf to pass the test: $./grade-lab-util pingpong
        printf("%d: received pong\n", getpid());        
    }

    exit(0);
}
