#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

int main() {
    pid_t pid = fork();

    if (pid < 0) {
        perror("fork failed");
        return 1;
    }
    else if (pid == 0) {
        /* Child: exits immediately */
        printf("Child (PID %d) exiting now.\n", getpid());
        exit(0);
    }
    else {
        /* Parent: deliberately does NOT wait() for the child */
        printf("Parent (PID %d): child PID %d has exited but I will not call wait().\n", getpid(), pid);
        printf("Parent sleeping for 30 seconds -- check 'ps -el | grep defunct' now.\n");
        sleep(30);
        printf("Parent exiting now (zombie will be cleaned up by init/reaper).\n");
    }

    return 0;
}
