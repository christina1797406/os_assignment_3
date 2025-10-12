/**
 * This file implements parallel mergesort.
 */

#include "mergesort.h"
#include <stdio.h>
#include <stdlib.h> /* for malloc */
#include <string.h> /* for memcpy */

/* this function will be called by mergesort() and also by parallel_mergesort().
 * Christina */
void merge(int leftstart, int leftend, int rightstart, int rightend) {}

/* this function will be called by parallel_mergesort() as its base case. Minh
 */
void my_mergesort(int left, int right) {}

/* this function will be called by the testing program. Samira */
void *parallel_mergesort(void *arg) {
  struct argument *a = (struct argument *)arg;
  int left = a->left;
  int right = a->right;
  int level = a->level;

  /* do normal mergesort if cutoff is reached */
  if (level >= cutoff) {
    my_mergesort(left, right);
    return NULL;
  }

  /* otherwise, split and recurse with threads */
  int mid = left + (right - left) / 2;

  /* build arguments for left and right halves*/
  struct argument *leftArg = buildArgs(left, mid, level + 1);
  struct argument *rightArg = buildArgs(mid + 1, right, level + 1);

  pthread_t leftThread, rightThread;
  int rc;

  rc = pthread_create(&leftThread, NULL, parallel_mergesort, leftArg);
  if (rc) {
    printf("ERROR: return code from pthread_create() is %d\n", rc);
    exit(EXIT_FAILURE);
  }
  rc = pthread_create(&rightThread, NULL, parallel_mergesort, rightArg);
  if (rc) {
    printf("ERROR: return code from pthread_create() is %d\n", rc);
    exit(EXIT_FAILURE);
  }

  /* wait for both threads to finish */
  pthread_join(leftThread, NULL);
  pthread_join(rightThread, NULL);

  /* merge two halves*/
  merge(left, mid, mid + 1, right);

  /* free the arguments */
  free(leftArg);
  free(rightArg);

  return NULL;
}

/* we build the argument for the parallel_mergesort function. TBD */
struct argument *buildArgs(int left, int right, int level) { return NULL; }
