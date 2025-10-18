/**
 * This file implements parallel mergesort.
 */

#include "mergesort.h"

#include <stdio.h>
#include <stdlib.h> /* for malloc */
#include <string.h> /* for memcpy */

/* this function will be called by mergesort() and also by parallel_mergesort().
 * Christina */
void merge(int leftstart, int leftend, int rightstart, int rightend) {
  int i, j, k;
  i = leftstart;   // start index for the left subarray
  j = rightstart;  // start index for the right subarray
  k = leftstart;   // start index for the merged subarray in B

  // Merge the two subarrays into B
  while (i <= leftend && j <= rightend) {
    if (A[i] <= A[j]) {
      B[k++] = A[i++];
    } else {
      B[k++] = A[j++];
    }
  }

  // Copy remaining values from left subarray
  while (i <= leftend) {
    B[k++] = A[i++];
  }
  // Copy remaining values from right subarray
  while (j <= rightend) {
    B[k++] = A[j++];
  }
  // Use memcpy to copy the merged elements back to A from B (src, dest, size)
  memcpy(&A[leftstart], &B[leftstart],
         (rightend - leftstart + 1) * sizeof(int));
}

/* this function will be called by parallel_mergesort() as its base case. Minh
 */
void my_mergesort(int left, int right) {
  if (left >= right) return;

  int mid = left + (right - left) / 2;
  my_mergesort(left, mid);
  my_mergesort(mid + 1, right);
  merge(left, mid, mid + 1, right);
}

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

  pthread_t t1, t2;
  int rc;

  rc = pthread_create(&t1, NULL, parallel_mergesort, leftArg);
  if (rc) {
    fprintf(stderr, "pthread_create failed: %d\n", rc);
    exit(EXIT_FAILURE);
  }
  rc = pthread_create(&t2, NULL, parallel_mergesort, rightArg);
  if (rc) {
    fprintf(stderr, "pthread_create failed: %d\n", rc);
    exit(EXIT_FAILURE);
  }

  /* wait for both threads to finish */
  pthread_join(t1, NULL);
  pthread_join(t2, NULL);

  /* merge two halves*/
  merge(left, mid, mid + 1, right);

  /* free the arguments */
  free(leftArg);
  free(rightArg);

  return NULL;
}

/* we build the argument for the parallel_mergesort function. TBD */
struct argument *buildArgs(int left, int right, int level) {
    struct argument *arg = (struct argument *)malloc(sizeof(struct argument));
    if (arg == NULL) {
        fprintf(stderr, "Error: malloc failed in buildArgs\n");
        exit(EXIT_FAILURE);
    }

    arg->left = left;
    arg->right = right;
    arg->level = level;

    return arg;
}

