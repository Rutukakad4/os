#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/wait.h>
#include <sys/resource.h>
#include <time.h>

int main(int argc, char *argv[]) {
    if (argc != 2) {
        fprintf(stderr, "Usage: %s <number_of_processes>\n", argv[0]);
        return 1;
    }

    int n = atoi(argv[1]);
    if (n <= 0) {
        fprintf(stderr, "Number of processes must be a positive integer\n");
        return 1;
    }

    struct rusage rusage_start, rusage_end;
    clock_t start_time, end_time;

    // Get starting time
    start_time = clock();
    getrusage(RUSAGE_CHILDREN, &rusage_start);

    // Create 'n' child processes
    for (int i = 0; i < n; i++) {
        pid_t pid = fork();

        if (pid == -1) {
            perror("fork");
            return 1;
        } else if (pid == 0) { // Child process
            // Simulate some work in child process
            sleep(1);
            exit(0);
        }
    }

    // Wait for all child processes to terminate
    for (int i = 0; i < n; i++) {
        wait(NULL);
    }

    // Get ending time
    end_time = clock();
    getrusage(RUSAGE_CHILDREN, &rusage_end);

    // Calculate total user and kernel time
    double user_time = (double)(rusage_end.ru_utime.tv_sec - rusage_start.ru_utime.tv_sec) +
                       (double)(rusage_end.ru_utime.tv_usec - rusage_start.ru_utime.tv_usec) / 1000000.0;
    double sys_time = (double)(rusage_end.ru_stime.tv_sec - rusage_start.ru_stime.tv_sec) +
                      (double)(rusage_end.ru_stime.tv_usec - rusage_start.ru_stime.tv_usec) / 1000000.0;

    printf("Total user time spent by children: %.2f seconds\n", user_time);
    printf("Total kernel time spent by children: %.2f seconds\n", sys_time);
    printf("Total elapsed time: %.2f seconds\n", (double)(end_time - start_time) / CLOCKS_PER_SEC);

    return 0;
}
