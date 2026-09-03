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
        /* Child process: replace its image with "ls -l" */
        printf("Child (PID %d): about to exec 'ls -l'\n", getpid());
        execlp("ls", "ls", "-l", NULL);

        /* This line only runs if execlp() FAILS,
           because a successful exec() never returns */
        perror("exec failed");
        _exit(1);
    }
    else {
        /* Parent process */
        printf("Parent (PID %d): waiting for child to finish...\n", getpid());
        wait(NULL);
        printf("Parent: child's exec'd program has finished. Parent exiting.\n");
    }

    return 0;
}
