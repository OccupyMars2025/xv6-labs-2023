// /*
// Sieve of Eratosthenes using fork() and pipe()
// You can compile and run the commented code on Linux, version for Linux
// copied from:
// https://stackoverflow.com/questions/70967998/c-sieve-of-eratosthenes-using-fork

// */

// #include <stdio.h>
// #include <unistd.h>
// #include <stdlib.h>
// #include <sys/types.h>

// void filter_out_multiples(int num, int fd_for_read, int fd_for_write){
//     int i;
//     while(read(fd_for_read, &i, sizeof(i)) > 0){
//         if(i % num != 0){
//             write(fd_for_write, &i, sizeof(i));
//         }
//     }
//     // // Is this line necessary ?
//     // close(fd_for_read);
// }

// void primes(int fd_for_read){
//     int num;
    
//     if(read(fd_for_read, &num, sizeof(num)) > 0){   
//         int primePipe[2];
//         /*
//         when you call pipe(), "fd_for_read" is NOT closed, so 
//         the fd number will increase gradually
//         */
//         pipe(primePipe);
//         printf("fd for pipe: %d, %d\n", primePipe[0], primePipe[1]);
//         printf("\033[31;1;4mprime:%d\n\033[0m", num); //Printing out the numbers
        
//         pid_t pid = fork();
//         printf("pid: %d\n", pid);
//         if(pid < 0){ // Error with fork
//             fprintf(stderr, "Fork Failed");
//             exit(1);
//         }else if(pid){   //Parent
//             close(primePipe[1]);
//             primes(primePipe[0]);
//         }else{   //Child
//             close(primePipe[0]);
//             filter_out_multiples(num, fd_for_read, primePipe[1]);
//             close(primePipe[1]);
//         }
//     }
// }

// int main(int argc, char *argv[]) {
//     int pd[2];
//     pipe(pd); 
    
//     pid_t pid = fork();
//     printf("pid=%d\n", pid);
//     if (pid < 0) { //Error with fork
//       fprintf(stderr, "Fork Failed");
//       exit(1);
//     }else if(pid){ // Parent
//         close(pd[1]);
//         primes(pd[0]);   
//     }else{ // Child
//         close(pd[0]);
//         for(int num = 2; num < 100; ++num) {
//             write(pd[1], &num, sizeof(num)); 
//         }
//         close(pd[1]);
//     }

//     exit(0);
// }


/**
 * https://pdos.csail.mit.edu/6.1810/2023/labs/util.html
 * https://swtch.com/~rsc/thread/
 * 
 * Write a concurrent prime sieve program for xv6 using pipes and 
 * the design illustrated in the picture halfway down this page and
 *  the surrounding text. This idea is due to Doug McIlroy, 
 * inventor of Unix pipes. Your solution should be in the file 
 * user/primes.c.
*/



/*
Sieve of Eratosthenes using fork() and pipe()
version for xv6-riscv
modified from:
https://stackoverflow.com/questions/70967998/c-sieve-of-eratosthenes-using-fork

run the following to test it:
$ ./grade-lab-util primes
*/
#include "kernel/types.h"
#include "user/user.h"


void filter_out_multiples(int num, int fd_for_read, int fd_for_write){
    int i;
    while(read(fd_for_read, &i, sizeof(i)) > 0){
        if(i % num != 0){
            write(fd_for_write, &i, sizeof(i));
        }
    }
    // // Is this line necessary ?
    // close(fd_for_read);
}

void primes(int fd_for_read){
    int num;
    
    if(read(fd_for_read, &num, sizeof(num)) > 0){   
        int primePipe[2];
        /*
        when you call pipe(), "fd_for_read" is NOT closed, so 
        the fd number will increase gradually
        */
        pipe(primePipe);
        // printf("fd for pipe: %d, %d\n", primePipe[0], primePipe[1]);
        // printf("\033[31;1;4mprime %d\n\033[0m", num); //Printing out the numbers
        printf("prime %d\n", num); //Printing out the numbers
        
        int pid = fork();
        // printf("pid: %d\n", pid);
        if(pid < 0){ // Error with fork
            fprintf(2, "Fork Failed\n");
            exit(1);
        }else if(pid){   //Parent
            close(primePipe[1]);
            primes(primePipe[0]);
        }else{   //Child
            close(primePipe[0]);
            filter_out_multiples(num, fd_for_read, primePipe[1]);
            close(primePipe[1]);
        }
    }
}

int main(int argc, char *argv[]) {
    int pd[2];
    pipe(pd); 
    
    int pid = fork();
    // printf("pid=%d\n", pid);
    if (pid < 0) { //Error with fork
      fprintf(2, "Fork Failed\n");
      exit(1);
    }else if(pid){ // Parent
        close(pd[1]);
        primes(pd[0]);   
    }else{ // Child
        close(pd[0]);
        for(int num = 2; num <= 35; ++num) {
            write(pd[1], &num, sizeof(num)); 
        }
        close(pd[1]);
    }

    exit(0);
}
