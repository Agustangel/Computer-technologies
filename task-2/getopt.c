
#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>

int op_exists(char** options, int optlen, char op)
{
    char opt = 0;
    while((opt = getopt(optlen, options, "asmd")) != -1)
    {
        printf("opt: %c\n", opt);
        if (opt == op)
        {
            return 1;
        }
    }
}

int main (int argc, char** argv)
{
    char opt = 0;
    while((opt = getopt(argc, argv, "asmd")) != -1)
    {
        printf("opt: %c\n", opt);
    }

    for (int i = 0; i < argc; ++i)
    {
        printf("argv[%d] = %s\n", i, argv[i]);
    }

    printf("optind: %d\n", optind);

    char* lhs = argv[optind];
    printf("lhs: %s\n", lhs);
    for (int i = optind + 1; i < argc; ++i)
    {
        rhs =
    }

    return 0;
}