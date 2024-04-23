#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <sys/time.h>
#include <sys/resource.h>
#include <unistd.h>

int main(int argc, char *argv[]) {
    if (argc != 2) {
        printf("Usage: %s <number_of_children>\n", argv[0]);
        return 1;
    }

    int n = atoi(argv[1]);
    if (n <= 0) {
        printf("Number of children must be a positive integer.\n");
        return 1;
    }

    struct rusage rusage;
    struct timeval start, end;
    gettimeofday(&start, NULL);

    for (int i = 0; i < n; ++i) {
        pid_t pid = fork();
        if (pid == -1) {
            perror("fork");
            return 1;
        } else if (pid == 0) {
            // Child process
            printf("Child %d (PID: %d) started.\n", i+1, getpid());
            // Simulating some work
            sleep(2);
            printf("Child %d (PID: %d) finished.\n", i+1, getpid());
            exit(0);
        }
    }

    // Wait for all child processes to terminate
    while (wait(NULL) > 0);

    gettimeofday(&end, NULL);

    // Get resource usage statistics
    getrusage(RUSAGE_CHILDREN, &rusage);

    // Calculate total time spent in user and kernel modes
    double user_time = rusage.ru_utime.tv_sec + rusage.ru_utime.tv_usec / 1000000.0;
    double kernel_time = rusage.ru_stime.tv_sec + rusage.ru_stime.tv_usec / 1000000.0;

    // Calculate total elapsed time
    double elapsed_time = (end.tv_sec - start.tv_sec) + (end.tv_usec - start.tv_usec) / 1000000.0;

    printf("Total cumulative time spent in user mode by all children: %.2f seconds\n", user_time);
    printf("Total cumulative time spent in kernel mode by all children: %.2f seconds\n", kernel_time);
    printf("Total elapsed time: %.2f seconds\n", elapsed_time);

    return 0;
}
