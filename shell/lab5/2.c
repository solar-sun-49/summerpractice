#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>

void *thread_func(void *arg) {
    printf("Thread created: Thread ID = %lu\n", (unsigned long) pthread_self());
    printf("Thread is doing its work...\n");
    printf("Thread terminating.\n");
    pthread_exit(NULL);
}

int main() {
    pthread_t tid;
    int ret;

    printf("Main: creating thread...\n");
    ret = pthread_create(&tid, NULL, thread_func, NULL);
    if (ret != 0) {
        perror("pthread_create failed");
        exit(1);
    }

    printf("Main: waiting for thread to finish...\n");
    pthread_join(tid, NULL);   /* wait for thread termination */

    printf("Main: thread has terminated. Main process exiting.\n");
    return 0;
}
