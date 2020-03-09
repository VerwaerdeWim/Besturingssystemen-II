#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <stdlib.h>
#include <fcntl.h>
#include <stdio.h>

#define N 5

int main(int argc, char **argv) {
    int pid[N];
    int i;
    for (i = 0; i < N; i++) {
        if ((pid[i] = fork()) == -1) {
            perror(argv[0]);
            exit(1);
        }
        else if (pid[i] == 0) {
            char *array[3] = {"writestring", "hello", 0};
            if (execv("/root/c/deel06/writestring.out", array) < 0) {
                perror(argv[0]);
                exit(1);
            }
        }
    }
    for (i = 0; i < N; i++) {
        waitpid(pid[i], NULL, 0);
    }
    exit(0);
}
