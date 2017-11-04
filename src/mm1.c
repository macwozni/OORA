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

/* Mulitplication of two matrices */
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

    /* PAPI variables */
    int measure;
    int * events;
    long long * values;
    int numevents;
    int retval;
    int check;
    float real_time;
    float proc_time;
    float mflops;
    long long flpins;
    char * errorstring;


    /* Initalize matrices */
    for (i = 0; i < SIZE; i++) { //rows in first
        for (j = 0; j < SIZE; j++) { //columns in first
            first[i][j] = i + j;
            second[i][j] = i - j;
            multiply[i][j] = 0.0;
        }
    }


    measure = 0;
    if (argc > 1) {
        measure = atoi(argv[1]);
    }

    /* Start PAPI counters*/
    if (measure == 1) {
        retval = PAPI_flops(&real_time, &proc_time, &flpins, &mflops);
        if (retval != PAPI_OK) {
            errorstring = PAPI_strerror(retval);
            fprintf(stderr, errorstring);
            fprintf(stderr, "\n");
            free(errorstring);
            exit(1);
        }
        printf("PAPI started\n");
    }
    if (measure == 2) {
        numevents = 2;
        events = malloc(sizeof *events * numevents);
        events[0] = PAPI_LD_INS;
        events[1] = PAPI_SR_INS;
        PAPI_library_init(check);
        retval = PAPI_start_counters(events, numevents);
        if (retval != PAPI_OK) {
            errorstring = PAPI_strerror(retval);
            fprintf(stderr, errorstring);
            fprintf(stderr, "\n");
            free(errorstring);
            exit(1);
        }
        printf("PAPI started\n");
    }

    /* Measure execution time */
    if (measure == 0) {
        dtime = dclock();
    }

    /* Here is call to matrix multiplication functionality */
    iret = mm(first, second, multiply);

    /* Measure execution time */
    if (measure == 0) {
        dtime = dclock() - dtime;
        printf("Time: %le \n", dtime);
    }

    /* Here is PAPI reading and printout */
    if (measure == 1) {
        retval = PAPI_flops(&real_time, &proc_time, &flpins, &mflops);
        if (retval != PAPI_OK) {
            errorstring = PAPI_strerror(retval);
            fprintf(stderr, errorstring);
            fprintf(stderr, "\n");
            free(errorstring);
            exit(1);
        }
        printf("Real_time: %f Proc_time: %f Total flpops: %lld MFLOPS: %f\n", real_time, proc_time, flpins, mflops);
    }
    if (measure == 2) {
        values = malloc(sizeof *values * numevents);
        retval = PAPI_stop_counters(values, numevents);
        if (retval != PAPI_OK) {
            errorstring = PAPI_strerror(retval);
            fprintf(stderr, errorstring);
            fprintf(stderr, "\n");
            free(errorstring);
            exit(1);
        }
        printf("Mem loads: %lld Mem store: %lld\n", values[0], values[1]);
        free(values);
        free(events);
    }

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

