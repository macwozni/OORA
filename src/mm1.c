#include <stdio.h>
#include <stdlib.h>
#include <sys/time.h>
#include <time.h>
#include <papi.h>

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
    int i, j, k;
    double sum = 0;
    for (i = 0; i < SIZE; i++) { //rows in multiply
        for (j = 0; j < SIZE; j++) { //columns in multiply
            for (k = 0; k < SIZE; k++) { //columns in first and rows in second
                sum = sum + first[i][k] * second[k][j];
            }
            multiply[i][j] = sum;
            sum = 0;
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

    int measure;
    int events[2];
    int numevents;
    int retval, check;
    float real_time, proc_time, mflops;
    long long flpins;
    char * errorstring;



    for (i = 0; i < SIZE; i++) { //rows in first
        for (j = 0; j < SIZE; j++) { //columns in first
            first[i][j] = i + j;
            second[i][j] = i - j;
            multiply[i][j] = 0.0;
        }
    }

    measure = 1;
    /*      Setup PAPI library and begin collecting data from the counters */
    numevents = 2;
    events[1] = PAPI_LD_INS;
    events[2] = PAPI_SR_INS;
    if (measure == 2) {
        retval = PAPI_flops(&real_time, &proc_time, &flpins, &mflops);
        if (retval != PAPI_OK) {
            errorstring = PAPI_strerror(retval);
            fprintf(stderr, errorstring);
            fprintf(stderr, "\n");
            free(errorstring);
            exit(1);
        }
        printf("PAPI started");
    }
    if (measure == 2) {
        PAPI_library_init(check);
        retval = PAPI_start_counters(events, numevents);
        if (retval != PAPI_OK) {
            errorstring = PAPI_strerror(retval);
            fprintf(stderr, errorstring);
            fprintf(stderr, "\n");
            free(errorstring);
            exit(1);
        }
        printf("PAPI started");
    }


    dtime = dclock();
    iret = mm(first, second, multiply);
    dtime = dclock() - dtime;
    printf("Time: %le \n", dtime);

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

