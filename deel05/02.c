#include <unistd.h>
#include <fcntl.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <stdlib.h>

#include <pthread.h>
#include <stdio.h>

#define MAX 8 * 1024

int main(int argc, char **argv) {
    int i;
    char buffer[MAX];
    for (i = 1; i < MAX * 2; i <<= 1) {
        double start = clock();
        int fd;
        if ((fd = open(argv[1], O_RDONLY)) == -1) {
            perror(argv[0]);
            exit(1);
        }

        int n;
        while ((n = read(fd, buffer, i) == i));
        if (n == -1) {
            perror(argv[0]);
            close(fd);
            exit(1);
        }

        if (close(fd) == -1) {
            perror(argv[0]);
            exit(1);
        }
        double time = (clock() - start) / CLOCKS_PER_SEC;
        printf("BUF_SIZ=%4d Time=%.2f\n", i, time);
    }

    exit(0);
}
