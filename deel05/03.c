#include <unistd.h>
#include <fcntl.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <stdlib.h>

#include <pthread.h>
#include <stdio.h>

#define MAX 8 * 1024

void vul(char *tab, int n) {
    int i;
    for (i = 0; i < n; i++) {
        tab[i] = 'a' + rand() % 26;
    }
}

int main(int argc, char **argv) {
    srand(time(0));
    int i;
    char buffer[MAX];
    for (i = 1; i < MAX * 2; i <<= 1) {
        double start = clock();
        int fd;
        if ((fd = open(argv[1], O_CREAT | O_WRONLY)) == -1) {
            perror(argv[0]);
            exit(1);
        }

        int tot = 0;
        while (tot < (10 * 1024 * 1024 - i)) {
            vul(buffer, i);
            write(fd, buffer, i);
            tot += i;
        }

        vul(buffer, 10 * 1024 * 1024 - tot);
        write(fd, buffer, 10 * 1024 * 1024 - tot);

        if (close(fd) == -1) {
            perror(argv[0]);
            exit(1);
        }
        double time = (clock() - start) / CLOCKS_PER_SEC;
        printf("BUF_SIZ=%4d Time=%.2f\n", i, time);
        unlink(argv[1]);
    }

    exit(0);
}
