#include <stdio.h>
#include <unistd.h>
#include <sys/wait.h>

int main() {
    pid_t pid = fork();

    if (pid < 0) {
        perror("fork failed");
        return 1;
    }
    else if (pid == 0) {
        /* Child: simulate some work */
        printf("Child (PID %d, Parent PID %d): working...\n", getpid(), getppid());
        sleep(3);
        printf("Child (PID %d): work done, exiting.\n", getpid());
    }
    else {
        /* Parent: waits for the child instead of exiting early */
        printf("Parent (PID %d): waiting for child (PID %d) to finish before I terminate...\n", getpid(), pid);
        int status;
        waitpid(pid, &status, 0);
        printf("Parent: child has terminated. No orphan was created. Parent exiting.\n");
    }

    return 0;
}