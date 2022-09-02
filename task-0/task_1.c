
#include <stdio.h>


int NOD(int a, int b)
{
    while (a != b)
    {
        if(a > b)
        {
            a -= b;
        }
        else
        {
            b -= a;
        }
    }
    
    return a;
}

int main()
{
    int a = 0;
    int b = 0;
    int nod = 0;

    printf("Input two integer numbers: \n");
    scanf("%d %d", &a, &b);

    nod = NOD(a, b);

    printf("NOD = %d\n", nod);

    return 0;
}
