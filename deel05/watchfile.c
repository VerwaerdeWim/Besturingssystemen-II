#include <unistd.h>
#include <fcntl.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <stdlib.h>
#include <stdio.h>

int main(int argc, char **argv) {
    if (argc != 2) {
        fprintf(stderr, "No file provided!\n");
        exit(1);
    }

    struct stat sb;
    if (stat(argv[1], &sb) == -1) {
        perror(argv[1]);
        exit(1);
    }

    if (!S_ISREG(sb.st_mode)) {
        fprintf(stderr, "%s is not a regular file\n", argv[1]);
        exit(1);
    }

    int orig = sb.st_mtime;
    while (1) {
        stat(argv[1], &sb);
        if (orig != sb.st_mtime) {
            printf("Gewijzigd...\n");
            orig = sb.st_mtime;
        }
    }
    exit(0);
}
