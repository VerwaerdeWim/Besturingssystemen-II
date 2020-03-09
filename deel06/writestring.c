#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <stdlib.h>
#include <fcntl.h>
#include <stdio.h>

int main(int argc, char **argv) {
    if (argc != 2) {
        exit(1);
    }
    printf("pid=%d string=%s\n", getpid(), argv[1]);
    sleep(10);
    exit(0);
}
