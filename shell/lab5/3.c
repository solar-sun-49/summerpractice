#include <stdio.h>
#include <unistd.h>

int main(int argc, char *argv[]) {
    for (int i = 0; i < 4; i++) {
        int ret = fork();
        if (ret == 0)
            printf("child %d\n", i);
    }
    return 0;
}
