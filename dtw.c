#include <math.h>
#include <stdio.h>
#include <stdlib.h>
#include "dtw.h"

double dtw(double *x, double *y, int xsize, int ysize, double window_frac)
{
    /* DTW distance algorithm based on
    https://en.wikipedia.org/wiki/Dynamic_time_warping */
    const double LARGE_VALUE = 1e30;
    const int min_window = abs(xsize - ysize);
    int i, j, minj, maxj, window;
    double dist, min;
    double **distances = malloc((xsize + 1) * sizeof(double *));
    for(i = 0; i < xsize + 1; ++i)
        distances[i] = malloc((ysize + 1) * sizeof(double));

    window = window_frac*ysize;
    if(window < min_window)
        window = min_window;

    for(i = 0; i <= xsize; ++i)
        for(j = 0; j <= ysize; ++j)
            distances[i][j] = LARGE_VALUE;
    distances[0][0] = 0.0;

    for(i = 0; i < xsize; ++i)
    {
        minj = i - window;
        if(minj < 0)
            minj = 0;
        maxj = i + window;
        if(maxj > ysize)
            maxj = ysize;
        for(j = minj; j < maxj; ++j)
        {
            dist = sqrt(pow(x[i] - y[j], 2.0));
            min = distances[i][j];
            if(min > distances[i][j+1])
                min = distances[i][j+1];
            if(min > distances[i+1][j])
                min = distances[i+1][j];
            distances[i+1][j+1] = dist + min;
        }
    }

    dist = distances[xsize][ysize];

    for(i = 0; i < xsize + 1; ++i)
        free(distances[i]);
    free(distances);

    return dist;
}