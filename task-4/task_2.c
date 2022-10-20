
#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <unistd.h>

void transfer_data_to_pipe(char* buffer, FILE* fp , int* fd) {
    while (!feof(fp)) {
        if (fgets(buffer, BUFSIZ - 1 ,fp)) {
            write(fd[1], buffer, BUFSIZ);
        }
    }
}

int main(int argc, char** argv)
{
    FILE* fp;

    int fd[2];
    pipe(fd);
    pid_t pid = fork();

    char buffer[BUFSIZ];
    if (argc != 3) {
        printf("ERORR launching program\n");
        exit(EXIT_FAILURE);
    }

    if (pid != 0) {
        close(fd[0]);
        if ((fp = fopen(argv[1], "r")) == NULL) {
            printf("Cannot open file to read\n");
            return 0;
        }
        transfer_data_to_pipe(buffer, fp, fd);
        fclose(fp);
        close(fd[1]);
    }
    else {
        close(fd[1]);
        if ((fp = fopen(argv[2], "w")) == NULL) {
            printf("Cannot open file to write\n");
            return 0;
        }
        while (read(fd[0], buffer, BUFSIZ)) {
            fputs(buffer, fp);
        }
        fclose(fp);
        close(fd[0]);
    }
    return 0;
}
