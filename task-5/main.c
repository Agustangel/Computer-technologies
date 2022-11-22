#include <stdio.h>
#include <fcntl.h>
#include <sys/time.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <dirent.h>
#include <assert.h>
#include <stdlib.h>
#include <unistd.h>
#include <errno.h>
#include <string.h>
#include <sys/mman.h>
#include <pthread.h>
#include <math.h>
 
enum ERROR
{
    ERROR_INVALID_ARGC   = -1,
    ERROR_PTHREAD_CREATE = -2,
    ERROR_PTHREAD_JOIN   = -3,
};
 
struct Integral
{
    double a;
    double b;
    int n_points;
 
    double sum;
};
 
void* integral(void* info);
 
int main(int argc, char* argv[])
{
    if (argc != 3)
    {
        printf("Please, enter numbers of threads and points!\n");
        return ERROR_INVALID_ARGC;
    }
 
    int n_threads = strtol(argv[2], &argv[2], 10);
    int n_points  = strtol(argv[1], &argv[1], 10);
 
    pthread_t*       threads   = (pthread_t*)       calloc(n_threads, sizeof(pthread_t));
    struct Integral* integrals = (struct Integral*) calloc(n_threads, sizeof(struct Integral)); 
 
    double step = 2.0 / n_points;
 
    for (int i = 0; i < n_threads; ++i)
    {
        integrals[i].n_points = n_points / n_threads;
    }
 
    for (int i = 0; i < n_points % n_threads; ++i)
    {
        integrals[i].n_points++;
    }
 
    double a_0 = 0;
 
    for (int i = 0; i < n_threads; ++i)
    {
        integrals[i].a = a_0;
        integrals[i].b = a_0 + step * integrals[i].n_points;
        a_0 = a_0 + step * integrals[i].n_points;
    }
 
    struct timeval tv1, tv2;
    gettimeofday(&tv1, NULL);
 
    for (int i = 0; i < n_threads; ++i)
    {
        if (pthread_create(&threads[i], NULL, integral, &integrals[i]) == -1)
        {
            perror("ERROR: pthread_create");
            free(threads);
            free(integrals);
            return  ERROR_PTHREAD_CREATE;
        }
    }
 
    for (int i = 0; i < n_threads; ++i)
    {
        if (pthread_join(threads[i], NULL) == -1)
        {
            perror("ERROR: pthread_create");
            free(threads);
            free(integrals);
            return  ERROR_PTHREAD_JOIN;
        }
    }
 
    double summa = 0;
 
    for (int i = 0; i < n_threads; ++i)
    {
        summa += integrals[i].sum;
    }
 
    printf("Integral sqrt(4 - x * x) from 0 to 2 is equal to %lg\n", summa);
    gettimeofday(&tv2, NULL);
    printf ("Time = %f\n", (double) (tv2.tv_usec - tv1.tv_usec) / 1000000 + (double) (tv2.tv_sec - tv1.tv_sec));
}
 
void* integral(void* info)
{
    struct Integral* chunk = info;
 
    double x    = chunk->a;
    double step = (chunk->b - chunk->a) / chunk->n_points; 
 
    for (int i = 0; i < chunk->n_points; ++i)
    {
        chunk->sum += sqrt(4 - x * x) * step;
        x += step;
    }
 
    pthread_exit(chunk);
}
