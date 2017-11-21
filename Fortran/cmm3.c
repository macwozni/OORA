#include <stdio.h>
#include <stdlib.h>
#include <sys/time.h>
#include <time.h>
#include <math.h>

#define SIZE 512

static double gtod_ref_time_sec = 0.0;

/* Adapted from the bl2_clock() routine in the BLIS library */
double dclock() {
    double the_time, norm_sec;
    struct timeval tv;
    gettimeofday(&tv, NULL);
    if (gtod_ref_time_sec == 0.0)
        gtod_ref_time_sec = (double) tv.tv_sec;
    norm_sec = (double) tv.tv_sec - gtod_ref_time_sec;
    the_time = norm_sec + tv.tv_usec * 1.0e-6;
    return the_time;
}

int mm(double first[][SIZE], double second[][SIZE], double multiply[][SIZE]) {
    register unsigned int i, j, k;
    int jj, kk;
    register double sum = 0;
    int ichunk;

    ichunk = 8; //512 // I have a 3MB cache size (real*4)
    for (jj = 0; jj < SIZE; jj += ichunk) {
        for (kk = 0; kk < SIZE; kk += ichunk) {

            for (j = jj; j <= fmin(jj + ichunk - 1, SIZE); j++) {
                for (k = kk; k <= fmin(kk + ichunk - 1, SIZE); k++) {
                    for (i = 0; i < SIZE; i++) {
                        multiply[i][j] = multiply[i][j] + first[i][k] * second[k][j];
                    }
                }
            }

        }
    }


    return 0;
}

int main(int argc, const char* argv[]) {
    int i, j, iret;
    double first[SIZE][SIZE];
    double second[SIZE][SIZE];
    double multiply[SIZE][SIZE];
    double dtime;

    /* Initalize matrices */
    for (i = 0; i < SIZE; i++) { //rows in first
        for (j = 0; j < SIZE; j++) { //columns in first
            first[i][j] = i + j;
            second[i][j] = i - j;
            multiply[i][j] = 0.0;
        }
    }

    /* Measure execution time */
    dtime = dclock();

    /* Here is call to matrix multiplication functionality */
    iret = mm(first, second, multiply);

    dtime = dclock() - dtime;
    printf("Time: %le \n", dtime);


    /* Checking part of the code. Proper value is 2.932020e+12 */
    double mcheck = 0.0;
    for (i = 0; i < SIZE; i++) {
        for (j = 0; j < SIZE; j++) {
            mcheck += multiply[i][j];
        }
    }
    printf("check %le \n", mcheck);
    fflush(stdout);

    return iret;
}

