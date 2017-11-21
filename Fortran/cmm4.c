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
    /*register unsigned*/ int i, j, k; //<- OPT 1
    register double sum = 0.0;
    for (i = 0; i < SIZE; i++) { //rows in multiply <- OPT 3
        for (j = 0; j < SIZE;) {
            for (k = 0; k < SIZE;) {

                sum = sum + first[i][k] * second[j][k];
                sum = sum + first[i][k + 1] * second[j][k + 1];
                sum = sum + first[i][k + 2] * second[j][k + 2];
                sum = sum + first[i][k + 3] * second[j][k + 3];
                sum = sum + first[i][k + 4] * second[j][k + 4];
                sum = sum + first[i][k + 5] * second[j][k + 5];
                sum = sum + first[i][k + 6] * second[j][k + 6];
                sum = sum + first[i][k + 7] * second[j][k + 7];
                multiply[i][j] += sum;
                sum = 0.0;

                sum = sum + first[i][k] * second[j + 1][k];
                sum = sum + first[i][k + 1] * second[j + 1][k + 1];
                sum = sum + first[i][k + 2] * second[j + 1][k + 2];
                sum = sum + first[i][k + 3] * second[j + 1][k + 3];
                sum = sum + first[i][k + 4] * second[j + 1][k + 4];
                sum = sum + first[i][k + 5] * second[j + 1][k + 5];
                sum = sum + first[i][k + 6] * second[j + 1][k + 6];
                sum = sum + first[i][k + 7] * second[j + 1][k + 7];
                multiply[i][j + 1] += sum;
                sum = 0.0;

                sum = sum + first[i][k] * second[j + 2][k];
                sum = sum + first[i][k + 1] * second[j + 2][k + 1];
                sum = sum + first[i][k + 2] * second[j + 2][k + 2];
                sum = sum + first[i][k + 3] * second[j + 2][k + 3];
                sum = sum + first[i][k + 4] * second[j + 2][k + 4];
                sum = sum + first[i][k + 5] * second[j + 2][k + 5];
                sum = sum + first[i][k + 6] * second[j + 2][k + 6];
                sum = sum + first[i][k + 7] * second[j + 2][k + 7];
                multiply[i][j + 2] += sum;
                sum = 0.0;

                sum = sum + first[i][k] * second[j + 3][k];
                sum = sum + first[i][k + 1] * second[j + 3][k + 1];
                sum = sum + first[i][k + 2] * second[j + 3][k + 2];
                sum = sum + first[i][k + 3] * second[j + 3][k + 3];
                sum = sum + first[i][k + 4] * second[j + 3][k + 4];
                sum = sum + first[i][k + 5] * second[j + 3][k + 5];
                sum = sum + first[i][k + 6] * second[j + 3][k + 6];
                sum = sum + first[i][k + 7] * second[j + 3][k + 7];
                multiply[i][j + 3] += sum;
                sum = 0.0;

                sum = sum + first[i][k] * second[j + 4][k];
                sum = sum + first[i][k + 1] * second[j + 4][k + 1];
                sum = sum + first[i][k + 2] * second[j + 4][k + 2];
                sum = sum + first[i][k + 3] * second[j + 4][k + 3];
                sum = sum + first[i][k + 4] * second[j + 4][k + 4];
                sum = sum + first[i][k + 5] * second[j + 4][k + 5];
                sum = sum + first[i][k + 6] * second[j + 4][k + 6];
                sum = sum + first[i][k + 7] * second[j + 4][k + 7];
                multiply[i][j + 4] += sum;
                sum = 0.0;

                sum = sum + first[i][k] * second[j + 5][k];
                sum = sum + first[i][k + 1] * second[j + 5][k + 1];
                sum = sum + first[i][k + 2] * second[j + 5][k + 2];
                sum = sum + first[i][k + 3] * second[j + 5][k + 3];
                sum = sum + first[i][k + 4] * second[j + 5][k + 4];
                sum = sum + first[i][k + 5] * second[j + 5][k + 5];
                sum = sum + first[i][k + 6] * second[j + 5][k + 6];
                sum = sum + first[i][k + 7] * second[j + 5][k + 7];
                multiply[i][j + 5] += sum;
                sum = 0.0;


                sum = sum + first[i][k] * second[j + 6][k];
                sum = sum + first[i][k + 1] * second[j + 6][k + 1];
                sum = sum + first[i][k + 2] * second[j + 6][k + 2];
                sum = sum + first[i][k + 3] * second[j + 6][k + 3];
                sum = sum + first[i][k + 4] * second[j + 6][k + 4];
                sum = sum + first[i][k + 5] * second[j + 6][k + 5];
                sum = sum + first[i][k + 6] * second[j + 6][k + 6];
                sum = sum + first[i][k + 7] * second[j + 6][k + 7];
                multiply[i][j + 6] += sum;
                sum = 0.0;

                sum = sum + first[i][k] * second[j + 7][k];
                sum = sum + first[i][k + 1] * second[j + 7][k + 1];
                sum = sum + first[i][k + 2] * second[j + 7][k + 2];
                sum = sum + first[i][k + 3] * second[j + 7][k + 3];
                sum = sum + first[i][k + 4] * second[j + 7][k + 4];
                sum = sum + first[i][k + 5] * second[j + 7][k + 5];
                sum = sum + first[i][k + 6] * second[j + 7][k + 6];
                sum = sum + first[i][k + 7] * second[j + 7][k + 7];
                multiply[i][j + 7] += sum;
                sum = 0.0;

                k += 8;

            }
            j += 8;
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

