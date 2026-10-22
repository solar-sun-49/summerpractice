#include <stdio.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>
int main() {
pid_t pid;
pid = fork();
if (pid < 0) {
printf("Process creation failed.\n");
return 1;
}
else if (pid == 0) {
printf("This is the Child Process.\n");
printf("Child Process ID: %d\n"
, getpid());
printf("Parent Process ID: %d\n"
, getppid());
}
else {
wait(NULL);
printf("This is the Parent Process.\n");
printf("Parent Process ID: %d\n"
, getpid());
printf("Child Process ID: %d\n"
, pid);
}
return 0;
}