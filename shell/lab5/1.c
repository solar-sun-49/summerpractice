#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/wait.h>

int main() {
    pid_t pid = fork();

    if (pid < 0) {
        perror("fork failed");
        exit(1);
    }
    else if (pid == 0) {
        /* Child process */
        printf("Child process: PID = %d, Parent PID = %d\n", getpid(), getppid());
        printf("Child process doing its work...\n");
        printf("Child process terminating.\n");
        exit(0);
    }
    else {
        /* Parent process */
        printf("Parent process: PID = %d, created child with PID = %d\n", getpid(), pid);
        wait(NULL);  /* wait for child to terminate */
        printf("Parent: child has terminated (reaped).\n");
        printf("Parent process terminating.\n");
    }

    return 0;
}
