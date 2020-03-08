#include <unistd.h>
#include <fcntl.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <stdlib.h>

int main(int argc, char **argv) {
    srand(time(0));
    int fd;
    if ((fd = open(argv[1], O_CREAT | O_WRONLY, S_IRUSR | S_IRGRP | S_IROTH)) == -1) {
        perror(argv[0]);
        exit(1);
    }

    int i;
    for (i = 0; i < 10 * 1024 * 1024; i++) {
        char ch = rand() % 26 + 'a';
        if ((write(fd, &ch, 1)) != 1) {
            perror(argv[0]);
            exit(1);
        }
    }

    if (close(fd) == -1) {
        perror(argv[0]);
        exit(1);
    }

    exit(0);
}
