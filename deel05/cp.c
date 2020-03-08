#include <unistd.h>
#include <fcntl.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <stdlib.h>

#include <stdio.h>

#define MAX 8 * 1024

int main(int argc, char **argv) {
    char buffer[MAX];
    int rd;
    if ((rd = open(argv[1], O_RDONLY)) == -1) {
        perror(argv[0]);
        exit(1);
    }

    int wd;
    if ((wd = open(argv[2], O_WRONLY | O_TRUNC)) == -1) {
        perror(argv[0]);
        exit(1);
    }

    int n;
    while ((n = read(rd, buffer, MAX)) > 0) {
        if (n == -1) {
            perror(argv[0]);
            close(rd);
            close(wd);
            exit(1);
        }
        write(wd, buffer, n);
    }

    if (close(rd) == -1) {
        perror(argv[0]);
        exit(1);
    }
    if (close(wd) == -1) {
        perror(argv[0]);
        exit(1);
    }

    exit(0);
}
