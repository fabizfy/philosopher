#include <stdio.h>
#include <sys/types.h>
#include <sys/ipc.h>
#include <sys/sem.h>
#include <sys/stat.h>
#include <stdlib.h>
#include <math.h>
#include <semaphore.h>
#include <pthread.h>
#include <unistd.h>
#include <sys/wait.h>

/* successive calls to randomGaussian produce integer return values */
/* having a gaussian distribution with the given mean and standard  */
/* deviation.  Return values may be negative.                       */

int randomGaussian(int mean, int stddev)
{
    double mu = 0.5 + (double)mean;
    double sigma = fabs((double)stddev);
    double f1 = sqrt(-2.0 * log((double)rand() / (double)RAND_MAX));
    double f2 = 2.0 * 3.14159265359 * (double)rand() / (double)RAND_MAX;
    if (rand() & (1 << 5))
        return (int)floor(mu + sigma * cos(f2) * f1);
    else
        return (int)floor(mu + sigma * sin(f2) * f1);
}
/*---------------------------------------------------------------------*/

int main()
{
    for (int i = 0; i < 5; i++) // loop will run 5 times creating 5 child
    {
        if (fork() == 0)
        {
            printf("[son][%d] pid %d from [parent] pid %d\n", i, getpid(), getppid());
            exit(0);
        }
    }
    for (int i = 0; i < 5; i++) // loop will run 5 times
        wait(NULL);
}