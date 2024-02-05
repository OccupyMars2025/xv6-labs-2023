// ==================== implementation 1

/*
https://swtch.com/~rsc/thread/

*/
#include "kernel/types.h"
#include "user/user.h"

void sieve(int fd) {
  int prime, i;
  if(read(fd, &prime, sizeof(prime)) != sizeof(prime)) {
    return;
  }
  printf("prime %d\n", prime);
  // printf("prime %d, pid=%d\n", prime, getpid());

  int pipe_fds[2];
  pipe(pipe_fds);

  int pid = fork();
  if(0 == pid) {
    close(pipe_fds[1]);
    sieve(pipe_fds[0]);
    close(pipe_fds[0]);
  } else {
    close(pipe_fds[0]);
    while (read(fd, &i, sizeof(i)) == sizeof(i))
    {
      if(i % prime != 0) {
        write(pipe_fds[1], &i, sizeof(i));
      }
    }  
    close(pipe_fds[1]);
    wait(0);
  }
}

int main()
{
  int pipe_fds[2];
  pipe(pipe_fds);

  int pid = fork();
  if(0 == pid) {
    close(pipe_fds[1]);
    sieve(pipe_fds[0]);
    close(pipe_fds[0]);
  } else {
    close(pipe_fds[0]);
    for (int i = 2; i < 35; i++)
    {
      write(pipe_fds[1], &i, sizeof(i));
    }
    close(pipe_fds[1]);
    wait(0);
  }

  exit(0);
}



// // ====================== implementation 2

// // primes.c
// #include "kernel/types.h"
// // #include "kernel/stat.h"
// #include "user/user.h"

// void sieve(int in_fd) {
//     int prime, num;

//     // Read the first prime from the input
//     if (read(in_fd, &prime, sizeof(prime)) == 0) {
//         exit(0);
//     }

//     // Print the prime number
//     // printf("prime %d, pid=%d\n", prime, getpid());
//     printf("prime %d\n", prime);

//     // Create a new pipe for the next process
//     int fds[2];
//     pipe(fds);

//     if (fork() == 0) {
//         // Child process
//         close(fds[1]);  // Close write end of the pipe

//         // Recursive call 
//         sieve(fds[0]);
//         close(fds[0]);
//     } else {
//         // Parent process
//         close(fds[0]);  // Close read end of the pipe

//         while (read(in_fd, &num, sizeof(num)) == sizeof(num)) {
//             if (num % prime != 0) {
//                 // Send the number through the pipe if it's not divisible by the prime
//                 write(fds[1], &num, sizeof(num));
//             }
//         }

//         close(fds[1]);
//         wait(0);
//     }
// }

// int main() {
//     int fds[2];

//     // Create the initial pipe
//     pipe(fds);

//     if (fork() == 0) {
//         // Child process
//         close(fds[1]);  // Close write end of the pipe
//         sieve(fds[0]);
//         close(fds[0]);
//     } else {
//         // Parent process
//         close(fds[0]);  // Close read end of the pipe

//         for (int i = 2; i <= 35; i++) {
//             // Write numbers from 2 to 35 to the pipe
//             write(fds[1], &i, sizeof(i));
//         }

//         close(fds[1]);
//         wait(0);
//     }

//     exit(0);
// }


// ========================= implementation 3

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

// ================= implementation 4

// /**
//  * https://pdos.csail.mit.edu/6.1810/2023/labs/util.html
//  * https://swtch.com/~rsc/thread/
//  * 
//  * Write a concurrent prime sieve program for xv6 using pipes and 
//  * the design illustrated in the picture halfway down this page and
//  *  the surrounding text. This idea is due to Doug McIlroy, 
//  * inventor of Unix pipes. Your solution should be in the file 
//  * user/primes.c.
// */



// /*
// Sieve of Eratosthenes using fork() and pipe()
// version for xv6-riscv
// modified from:
// https://stackoverflow.com/questions/70967998/c-sieve-of-eratosthenes-using-fork

// run the following to test it:
// $ ./grade-lab-util primes
// */
// #include "kernel/types.h"
// #include "user/user.h"


// void filter_out_multiples(int num, int fd_for_read, int fd_for_write){
//     int i;
//     while(read(fd_for_read, &i, sizeof(i)) > 0){
//         if(i % num != 0){
//             write(fd_for_write, &i, sizeof(i));
//         }
//     }
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
//         // printf("fd for pipe: %d, %d\n", primePipe[0], primePipe[1]);
//         // printf("\033[31;1;4mprime %d\n\033[0m", num); //Printing out the numbers
//         printf("prime %d\n", num); //Printing out the numbers
        
//         int pid = fork();
//         // printf("pid: %d\n", pid);
//         if(pid < 0){ // Error with fork
//             fprintf(2, "Fork Failed\n");
//             exit(1);
//         }else if(pid == 0){   
//             close(primePipe[1]);
//             primes(primePipe[0]);
//             close(primePipe[0]);
//         }else{   
//             close(primePipe[0]);
//             filter_out_multiples(num, fd_for_read, primePipe[1]);
//             close(primePipe[1]);
//             wait(0);
//         }
//     }
// }

// int main() {
//     int pd[2];
//     pipe(pd); 
    
//     int pid = fork();
//     // printf("pid=%d\n", pid);
//     if (pid < 0) { //Error with fork
//       fprintf(2, "Fork Failed\n");
//       exit(1);
//     }else if(pid == 0){ 
//         close(pd[1]);
//         primes(pd[0]);  
//         close(pd[0]); 
//     }else{ 
//         close(pd[0]);
//         for(int num = 2; num <= 35; ++num) {
//             write(pd[1], &num, sizeof(num)); 
//         }
//         close(pd[1]);
//         wait(0);
//     }

//     exit(0);
// }
