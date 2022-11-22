#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <sys/time.h>

pthread_barrier_t barrier;

double** u;
int* hf;
int* ht;
int* inc;
double M;
int N;
int TNUM;
double h;
double T;

void parse_args(char** argv)
{
    N = atoi(argv[1]);
    T = atof(argv[2]);
    TNUM = atoi(argv[3]);
    h = 1 / (double) N;
    M = (T * N * N) / 0.3;
}

void init_compuatational_field()
{
    u = (double**) malloc (2 * sizeof(double*));
    inc = (int*) malloc (TNUM * sizeof(int));
    hf = (int*) malloc (TNUM * sizeof(int));
    ht = (int*) malloc (TNUM * sizeof(int));
}

void* calculate(void *a)
{
    int l = *((int *)a);
    for (int i = 1; i < M; i++)
    {
        pthread_barrier_wait(&barrier);

        for (int j = hf[l]; j < ht[l]; j++)
        {
            u[i % 2][j] = u[(i - 1) % 2][j] + 0.3 * (u[(i - 1) % 2][j + 1] - 2 * u[(i - 1) % 2][j] + u[(i - 1) % 2][j - 1]);
        }
    }
    pthread_exit(NULL);

    return NULL;
}

int main(int argc, char* argv[])
{
    struct timeval tv1, tv2;
    gettimeofday(&tv1, NULL);

    init_compuatational_field();

    parse_args(argv);

    for (int i = 0; i < 2; i++)
    {
        u[i] = (double*) malloc (N * sizeof(double));
    }

    for (int i = 0; i < N; i++)
    {
        u[0][i] = 0;
    }
    
    u[0][0] = 0;
    u[1][0] = 0;
    u[0][N - 1] = 1;
    u[1][N - 1] = 1;

    pthread_barrier_init(&barrier, NULL, TNUM);
    pthread_t tt[TNUM];

    for (int i = 0; i < TNUM; i++)
    {
        inc[i] = i;
        hf[i] = (N * i) / TNUM;
        ht[i] = (N * (i + 1)) / TNUM;

        if (i == 0)
        {
            hf[i]++;
        }
        if (i == TNUM - 1)
        {
            ht[i]--;
        }
        pthread_create(&tt[i], NULL, calculate, &inc[i]);
    }
    
    for (int i = 0; i < TNUM; i++)
    {
        pthread_join(tt[i], NULL);
    }

    gettimeofday(&tv2, NULL);
    printf ("Time = %f\n", (double) (tv2.tv_usec - tv1.tv_usec) / 1000000 + (double) (tv2.tv_sec - tv1.tv_sec));
    
    FILE* f = fopen("result.txt", "w");
    for (int i = 0; i < N; i++)
    {
        fprintf(f,"%f\t%f\n", i*h, u[(int)M % 2][i]);
    }

    fclose(f);
    free(inc);
    free(hf);
    free(ht);

    for (int i = 0; i < 2; i++)
    {
        free(u[i]);
    }
    free(u);

    return 0;
}
