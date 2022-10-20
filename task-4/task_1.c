
#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <unistd.h>

int main() {

    int t, n, sum = 0;
    int ret = 0;
    int fd[2];
    pipe(fd);

    pid_t pid = fork();
    if (pid != 0) {

        close(fd[0]);

        ret = scanf("%d", &n);
        if (ret != 1) {
            printf("ERROR in scanf\n");
            exit(EXIT_FAILURE);
        }

        write(fd[1], &n, sizeof(int));
        for (int idx = 0; idx < n; idx++) {
            scanf("%d", &t);
            write(fd[1], &t, sizeof(int));
        }

        close(fd[1]);

    } else {

        close(fd[1]);
        read(fd[0], &n, sizeof(int));
        for (int idx = 0; idx < n; idx++) {
            read(fd[0], &t, sizeof(int));
            sum += t;
        }

        printf("%d\n", sum);
        close(fd[0]);
    }
    return 0;
}
