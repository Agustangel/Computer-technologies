
#include <getopt.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <stdio.h>
#include <assert.h>

int main(int argc, char** argv) {

    int fd[2];
    pipe(fd);
    pid_t pid = fork();
    if (pid != 0) {

        char str[BUFSIZ], name[100];
        int j = 0, i = 0;
        ssize_t len;
        
        len = read(fd[0], str, BUFSIZ);
        write(1, str, len);

        close(fd[0]);
        close(fd[1]);

        while(str[j] != '\0') {

            if (str[j] != '\n') {
                name[i] = str[j];
                i += 1;
                j += 1;
            }

            else {

                printf("Name : \"%s\" \n", name);
                char* buffer = (char*) calloc(BUFSIZ, sizeof(char));
                FILE *f1 = fopen(name, "r");
                assert(f1 != NULL);


                printf("data: \n");
                while (fgets(buffer, BUFSIZ, f1) != NULL) {
                    printf("%s\n", buffer);
                }

                for(int k = 0; k < 100; k ++) {
                    putchar('_');
                }

                putchar('\n');
                free(buffer);

                for (int k = 0; k < 100; k ++) {
                    name[k] = '\0';
                }

                j += 1;
                i = 0;

            }
        }
    }
    else
    {
        close(fd[0]);
        dup2(fd[1], 1);
        execlp("ls", "ls", NULL);
        close(fd[1]);
    }
    return 0;
}
