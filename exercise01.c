#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/time.h>
#include <sys/types.h>

#define NUM_EXCHANGES 100000

int main() {
    int pipe_a[2], pipe_b[2];
    pid_t child_pid;

    if (pipe(pipe_a) == -1 || pipe(pipe_b) == -1) {
        perror("pipe");
        exit(EXIT_FAILURE);
    }

    child_pid = fork();

    if (child_pid == -1) {
        perror("fork");
        exit(EXIT_FAILURE);
    }

    /*
              pipe_a
    parent  ========>>>  child

              pipe_b
            <<<========
    
    */
    if (child_pid == 0) {
        // Child process
        close(pipe_a[1]);  // Close write end of pipe_a
        close(pipe_b[0]);  // Close read end of pipe_b

        for (int i = 0; i < NUM_EXCHANGES; ++i) {
            char buffer;
            read(pipe_a[0], &buffer, 1);
            write(pipe_b[1], &buffer, 1);
        }

        close(pipe_a[0]);
        close(pipe_b[1]);
    } else {
        // Parent process
        close(pipe_a[0]);  // Close read end of pipe_a
        close(pipe_b[1]);  // Close write end of pipe_b

        struct timeval start, end;
        gettimeofday(&start, NULL);

        for (int i = 0; i < NUM_EXCHANGES; ++i) {
            char buffer = 'A';
            write(pipe_a[1], &buffer, 1);
            read(pipe_b[0], &buffer, 1);
        }

        gettimeofday(&end, NULL);

        close(pipe_a[1]);
        close(pipe_b[0]);

        double elapsed_time = (end.tv_sec - start.tv_sec) + (end.tv_usec - start.tv_usec) / 1e6;
        printf("start time:%ld s, %ld us -- %ld s, %ld us\n", start.tv_sec, start.tv_usec, end.tv_sec, end.tv_usec);
        printf("Elapsed time: %.3f seconds\n", elapsed_time);
        double exchanges_per_second = NUM_EXCHANGES / elapsed_time;
        printf("Performance: %.2f exchanges per second\n", exchanges_per_second);
    }

    return 0;
}
