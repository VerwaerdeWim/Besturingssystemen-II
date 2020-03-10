#include <unistd.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <stdlib.h>
#include <stdio.h>
#define MAX 50

int main(int argc, char **argv) {
    int pids[MAX];
    if (argc != 2) {
        printf("(Only) One argument expected!\n");
        exit(1);
    }
    int fd_C_P[MAX][2];
    int fd_P_C[MAX][2];
    int i;
    for (i = 0; i < atoi(argv[1]); i++) {
        if (pipe(fd_C_P[i]) == -1) {
            perror(argv[0]);
            exit(1);
        }

        if (pipe(fd_P_C[i]) == -1) {
            perror(argv[0]);
            exit(1);
        }

        if ((pids[i] = fork()) == -1) {
            perror(argv[0]);
        }
        if (pids[i] == 0) {
            // child i
            close(fd_C_P[i][0]); // schrijven naar parent dus leeskant sluiten
            close(fd_P_C[i][1]); // lezen van parent dus schrijfkant sluiten

            srand(getpid());

            unsigned int number = rand();
            write(fd_C_P[i][1], &number, sizeof(unsigned int));
            printf("I created %u! Grt Child (%d)\n", number, getpid());

            int pid_winner;
            read(fd_P_C[i][0], &pid_winner, sizeof(int));
            if (pid_winner == getpid()) {
                printf("I am the winner! Grt Child (%d)\n", pid_winner);
            }
            else {
                printf("Process %d is the winner! Grt Child (%d)\n", pid_winner, getpid());
            }

            exit(0);
        }
        // parent
        close(fd_C_P[i][1]); // luisteren naar kind dus schrijfkant sluiten
        close(fd_P_C[i][0]); // schrijven naar kind dus leeskant sluiten
    }
    int index = 0;
    unsigned int n;
    read(fd_C_P[0][0], &n, sizeof(unsigned int));

    for (i = 1; i < atoi(argv[1]); i++) {
        unsigned int temp;
        read(fd_C_P[i][0], &temp, sizeof(unsigned int));
        if (n < temp) {
            index = i;
            n = temp;
        }
    }
    printf("Child %d created the largest number %u, Grt Parent\n", pids[index], n);

    for (i = 0; i < atoi(argv[1]); i++) {
        write(fd_P_C[i][1], &pids[index], sizeof(int));
    }

    for (i = 0; i < atoi(argv[1]); i++) {
        waitpid(pids[i], NULL, 0);
    }
    return 0;
}
