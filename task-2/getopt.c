#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define NUMOPS 4

enum ops {
    ADD = 1,
    SUB = 2,
    MUL = 3,
    DIV = 4
};

int get_op(char* ops, int ops_len, int op_type) 
{
    if (op_type == ADD) 
    {
        if (strcmp(ops, "-a")) 
        {
            return 1;
        } 
        else 
        {
            return 0;
        }
    }
    if (op_type == SUB) 
    {
        if (strcmp(ops, "-s")) 
        {
            return 1;
        }
        else 
        {
            return 0;
        }
    }
    if (op_type == MUL) 
    {
        if (strcmp(ops, "-m"))
        {
            return 1;
        }
        else
        {
            return 0;
        }
    }
    if (op_type == DIV)
    {
        if (strcmp(ops, "-d"))
        {
            return 1;
        }
        else
        {
            return 0;
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
    
    int first_op = atoi((argv + optind)[0]);
    int second_op = atoi((argv + optind)[1]);
    int third_op = atoi((argv + optind)[2]);
    int first_pass = 0;
    int res = 0;

    printf("%d %d %d\n", first_op, second_op, third_op);
    for (int ops_num = 0; ops_num < NUMOPS; ++ops_num)
    {
        if (get_op(*(argv + 1), optind -2, ADD))
        {
            if (first_pass == 0)
            {
                res = (first_op + second_op);
                first_pass = 1;
            }
            else
            {
                res += third_op;
            }
        }
        if (get_op(*(argv + 1),optind -2, SUB))
        {
            if (first_pass == 0)
            {
                res = (first_op + second_op);
                first_pass = 1;
            }
            else
            {
                res += third_op;
            }
        }
        if (get_op(*(argv + 1), optind -2, MUL))
        {
            if (first_pass == 0)
            {
                res = (first_op + second_op);
                first_pass = 1;
            }
            else
            {
                res += third_op;
            }
        }
        if (get_op(*(argv + 1), optind -2, DIV))
        {
            if (first_pass == 0)
            {
                res = (first_op + second_op);
                first_pass = 1;
            }
            else
            {
                res += third_op;
            }
        }
        printf("res = %d\n", res);
    }
    
    return 0;
}
