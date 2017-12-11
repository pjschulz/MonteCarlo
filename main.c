#include <stdio.h>
#include "omp.h"
#include <time.h>
#include <stdlib.h>



double randFrom(double, double);

int main()
{
    long long int numberInCircle = 0; //Count of darts in circle
    long long int numberOfTosses = 1000000000; //number of dart tosses, greater the number, better the estimation
    int threadCount = 100; //number of threads for parallelizing
    double minNumber = -1.0;//min number for random number generator
    double maxNumber = 1.0;//max number for random number generator
    double x = 0.0;
    double y = 0.0;
    double distanceSquared = 0.0;
    double piEstimate = 0.0;
    srand(time(NULL));

#pragma omp parallel for num_threads(threadCount) reduction(+:numberInCircle) private(x, y, distanceSquared)
    for (long long int toss = 0; toss < numberOfTosses; toss++)
    {
        x = randFrom(minNumber, maxNumber);
        y = randFrom(minNumber, maxNumber);
        distanceSquared = x * x + y * y;

        if (distanceSquared <= 1)
            numberInCircle++;
    }

    piEstimate = 4 * numberInCircle/(double) numberOfTosses;
    printf("%f\r\n", piEstimate);

    return 0;
}

/* generate a random floating point number from min to max */
double randFrom(double min, double max)
{
    double range = (max - min);
    double div = RAND_MAX / range;
    return min + (rand() / div);
}

