#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <stdlib.h>
#include <fcntl.h>
#include <stdio.h>

#define N 3

int main(int argc, char **argv) {
    int pid[N];
    int i;
    for (i = 0; i < N; i++) {
        if ((pid[i] = fork()) == -1) {
            perror(argv[0]);
            exit(1);
        }
        else if (pid[i] == 0) {
            sleep(10);
            printf("I'm child %d with pid=%d and my parent is %d\n", i, getpid(), getppid());
            exit(0);
        }
    }

    for (i = 0; i < N; i++) {
        waitpid(pid[i], NULL, 0);
    }
    exit(0);
}
