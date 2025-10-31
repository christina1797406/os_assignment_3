#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/times.h> /* for times system call */
#include <sys/time.h>  /* for gettimeofday system call */
#include <unistd.h>
#include <error.h>     /* On MacOS you won't need this line */
#include "mergesort.h"

/* the number of levels of threads, specified by the user */
int cutoff = 0;

/* the array we want to sort */
int *A;

/* when merge, we need a temp array (named B) to temporarily store elements of the original array */
int *B;

// function prototypes
int check_if_sorted(int A[], int n);
void generate_random_array(int A[], int n, int seed);
double getMilliSeconds(void);

/*
---------------------------------------------------------------------------
clock_t times(struct tms *buffer);
times() fills the structure pointed to by buffer with
time-accounting information.  The structure defined in
<sys/times.h> is as follows:
struct tms {
    clock_t tms_utime;       user time
    clock_t tms_stime;       system time
    clock_t tms_cutime;      user time, children
    clock_t tms_cstime;      system time, children
The time is given in units of 1/CLK_TCK seconds where the
value of CLK_TCK can be determined using the sysconf() function
with the agrgument _SC_CLK_TCK.
---------------------------------------------------------------------------
*/


/* we do not really use this function anymore, but somehow we still keep it here. */
float report_cpu_time(void)
{
	struct tms buffer;
	float cputime;

	times(&buffer);
	cputime = (buffer.tms_utime)/ (float) sysconf(_SC_CLK_TCK);
	return (cputime);
}

/* we do not really use this function anymore, but somehow we still keep it here. */
float report_sys_time(void)
{
	struct tms buffer;
	float systime;

	times(&buffer);
	systime = (buffer.tms_stime)/ (float) sysconf(_SC_CLK_TCK);
	return (systime);
}

double getMilliSeconds(void)
{
    struct timeval now;
    gettimeofday(&now, (struct timezone *)0);
    return (double) now.tv_sec*1000.0 + now.tv_usec/1000.0;
}


/*
 * generate_random_array(int A[], int n, int seed):
 *
 * description: Generate random integers in the range [0,RANGE]
 *              and store in A[0..n-1]
 */

#define RANGE 1000000

void generate_random_array(int A[], int n, int seed)
{
	int i;
	srandom(seed);
	for (i=0; i<n; i++)
        	A[i] = random()%RANGE;
}


/*
 * check_if_sorted(int A[], int n):
 *
 * description: returns TRUE if A[1..n] are sorted in nondecreasing order
 *              otherwise returns FALSE
 */

int check_if_sorted(int A[], int n)
{
	int i;
	for (i=0; i<n-1; i++) {
		if (A[i] > A[i+1]) {
			return FALSE;
		}
	}
	return TRUE;
}

/* this function prints A, but we only print the first 100 elements */
void printA(void){
	int i;
	printf("Array A:");
	/* FIXME: we assume the size of A is at least 100, and this will fail if it is lower than 100 */
	for(i=0;i<100;i++){
		printf(" %d",A[i]);
	}
	printf("\n");
}

/* this function prints B, but we only print the first 100 elements */
void printB(void){
	int i;
	printf("Array B:");
	/* FIXME: we assume the size of B is at least 100, and this will fail if it is lower than 100 */
	for(i=0;i<100;i++){
		printf(" %d",B[i]);
	}
	printf("\n");
}

// Add this helper function above main()
void generate_input_array(int A[], int n, int seed, const char *mode) {
    if (mode == NULL || strcmp(mode, "random") == 0) {
        generate_random_array(A, n, seed);
    } else if (strcmp(mode, "sorted") == 0) {
		int i;
        for (i = 0; i < n; i++) A[i] = i;
    } else if (strcmp(mode, "reversed") == 0) {
		int i;
        for (i = 0; i < n; i++) A[i] = n - i;
    } else if (strcmp(mode, "equal") == 0) {
		int i;
        for (i = 0; i < n; i++) A[i] = 1;
    } else {
        fprintf(stderr, "Unknown mode '%s'. Valid modes: random, sorted, reversed, equal.\n", mode);
        exit(1);
    }
}

int main(int argc, char **argv) {

    if (argc < 4) {
        fprintf(stderr, "Usage: %s <input size> <cutoff level> <seed> [mode]\n", argv[0]);
        fprintf(stderr, "Modes: random (default), sorted, reversed, equal\n");
        exit(1);
    }

    int n = atoi(argv[1]);
    if (n <= 1) {
        printf("the input size must be at least 2!\n");
        exit(1);
    }

    cutoff = atoi(argv[2]);
    int seed = atoi(argv[3]);
    const char *mode = (argc > 4) ? argv[4] : "random";

    A = (int *) malloc(sizeof(int) * n);
    B = (int *) malloc(sizeof(int) * n);

    // Generate array based on mode
    generate_input_array(A, n, seed, mode);

    double start_time;
    double sorting_time;

    start_time = getMilliSeconds();
    struct argument *arg = buildArgs(0, n - 1, 0);
    parallel_mergesort(arg);
    sorting_time = getMilliSeconds() - start_time;

    if (check_if_sorted(A, n)) {
        printf("Sorting %d elements (%s) took %4.2lf seconds.\n", n, mode, sorting_time / 1000.0);
    } else {
        printf("%s: sorting failed!!!! (mode=%s)\n", argv[0], mode);
        free(arg);
        free(B);
        free(A);
        exit(EXIT_FAILURE);
    }

    free(arg);
    free(B);
    free(A);
    exit(EXIT_SUCCESS);
}
