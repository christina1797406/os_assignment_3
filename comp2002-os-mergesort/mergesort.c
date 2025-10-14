/**
 * This file implements parallel mergesort.
 */

#include <stdio.h>
#include <string.h> /* for memcpy */
#include <stdlib.h> /* for malloc */
#include "mergesort.h"

/* this function will be called by mergesort() and also by parallel_mergesort(). Christina */
void merge(int leftstart, int leftend, int rightstart, int rightend){
    int i, j, k;
    i = leftstart;  // start index for the left subarray 
    j = rightstart; // start index for the right subarray
    k = leftstart;  // start index for the merged subarray in B

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
    memcpy(&A[leftstart], &B[leftstart], (rightend - leftstart + 1) * sizeof(int));

}

/* this function will be called by parallel_mergesort() as its base case. Minh */
void my_mergesort(int left, int right){
	if (left >= right) return;

    int mid = left + (right - left) / 2;
    my_mergesort(left, mid);
    my_mergesort(mid + 1, right);
    merge(left, mid, mid + 1, right);
}

/* this function will be called by the testing program. Samira */
void * parallel_mergesort(void *arg){
		return NULL;
}

/* we build the argument for the parallel_mergesort function. TBD */
struct argument * buildArgs(int left, int right, int level){
		return NULL;
}

