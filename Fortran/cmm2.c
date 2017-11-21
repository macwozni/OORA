#include <stdio.h>
#include <stdlib.h>
#include <sys/time.h>
#include <time.h>

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
    register unsigned int i, j, k; //<- OPT 1
    register double sum = 0.0;
    for (i = SIZE; i--;) { //rows in multiply <- OPT 3
        for (j = SIZE; j--;) { //columns in multiply
            for (k = 0; k < SIZE;) {
                if (k < SIZE - 8) { //<- OPT 4
                    sum += first[i][k] * second[j][k] //<- OPT 5 (k<->j)
                            + first[i][k + 1] * second[j][k + 1]
                            + first[i][k + 2] * second[j][k + 2]
                            + first[i][k + 3] * second[j][k + 3]
                            + first[i][k + 4] * second[j][k + 4]
                            + first[i][k + 5] * second[j][k + 5]
                            + first[i][k + 6] * second[j][k + 6]
                            + first[i][k + 7] * second[j][k + 7];
                    k = k + 8;
                } else {
                    sum += first[i][k] * second[j][k];
                    k++;
                }
            }
            multiply[i][j] = sum;
            sum = 0.0;
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
            second[j][i] = i - j;
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

