# Operating Systems Assignment 3 - GROUP 14

## Authors

This project was developed by students of Group 14:
- Christina Nguyen a1797406
- Hong Minh Nguyen a1894168
- Samira Hazara a1852922

## Overview

This program implements a parallel merge sort using the *pthread* library to sort an integer array. Given a randomly generated integer array, it divides the sorting task across multiple threads according to a user-specified cutoff level. The user can specify a *cutoff* to control the number of recursive splitting levels to spawn new threads. When the cutoff is reached, further recursion is handles serially. The program is designed to showcase how multithreading and inter-thread synchronization can accelerate the same divide-and-conquer merge sort algorithm, and it reports timing results to quantify speedups over the serial version.

## Manifest

- `mergesort.c`: Contains the implementations of merge(), my_mergesort(), parallel_mergesort(), and buildArgs() functions
- `mergesort.h`: Header file that declares global variables, data structures, and function prototypes used by merge modules
- `test-mergesort.c`: Test harness that sets up random arrays, invokes parallel_mergesort(), measures timing and verifies correctness
- `Makefile`: Build rules (compilation, linking with pthread, ect.)
- `README.md`: Documentation of the project, usage, design, and setup instructions

## Building the project

(Christina) This section should tell the user how to build your code.  If you are
delivering a library, where does it need to be installed, or how do you use
it? Is this an executable, if so, how can a user get up to speed as fast as
possible?

## Features and usage

Key features include:
- Parallelisation with threads: The array is divided recursively across multiple threads to imitate multi-core processors
- Optimised merging: The program merges elements in subarrays using a temp array `B` and `memcpy`
- Recursive mergesort: The program uses standard recursive mergesort to organise the arrays
- Command-line usage: Users can specify input size, cutoff level and random seed from command line

### Usage instructions
1. To compile the program:
```bash
make
```
This will create an executable called `test-mergesort`.

2. To clean up compiled files and exectable, run:
```bash
make clean
```

3. To run the program with arguments:
```bash
./test-mergesort <input_size> <cutoff> <seed>
```
where:
- `input_size` is the number of elements to be sorted
- `cutoff` is the depth of threads generated
- `seed` is the random seed to generate input array


For example: 
```bash
./test-mergesort 10000 2 42
```
will run the parallel mergesort on 10000 elements, creating threads up to level 2, with a random seed of 42.

## Testing

(Minh) Your testing needs to be detailed here.

To test our code, we reviewed the provided test-mergesort.c file. (explain more on how this helped with testing - examining functions available)
- Edge case testing (provide example?? what values are restricted for each argument??) 
- Unit testing (function tested individually)
- Integration testing ()
- Regression testing (verify if order is correct)
- Performance testing??

We also considered adding a separate testing c file in addition to the provided test-mergesort.c file, named `test-mergesort-2.c`.
In this file, we created (number) more functions to help test ..
1. function-1
2. function-2

## Known Bugs

(Christina) List known bugs that you weren't able to fix (or ran out of time to fix).

## Reflection and Self Assessment
Through this project, our team significantly improved their understanding of multithreading and applications thereof in sorting algorithms. We gained practical experience in using pthread library, which deepened our understanding of thread creation, synchronization, and resource management. We also gained knowledge about the intricacies of parallel algorithm design, particularly regarding balancing between parallel and serial execution to achieve optimal performance. 

Throughout the development of the prallel merge sort program, our group encountered several challenges that evaluated our understanding and problem-solving skills. One major challenge was implementing the pthread-based parallelism. Initially, managing multiple threads and ensuring proper synchronization proved to be a complex task. We faced issues regarding race conditions and improper thread joins, which caused inconsistent sorting results. We accessed pthread documentation to gain insights into correct thread management techniques. 

Optimising the merge function for parallel execution was another challenge that we faced since the standard merge operation was designed for serial execution, and adapting it to work efficiently in a multithreaded environment necessitated memory access patterns and data copying methods to be carefully analysed. We used varying approaches to minimise overhead and ensure thread safety. These approaches are exemplified by ....

Our team gained valuable insights into the challenges and considerations in parallel programming. Through the enforcement of the importance of reliable design, in-depth testing, and coninuous learning, this task equipped us with beneficial skills and knowledge to be used in future endeavors that involve multithreading and parallel computing.

## Sources Used
We relied exclusively on the textbook assigned for the course, specifically *Chapter 26:  Concurrency: An Introduction* and *Chapter 27: Interlude: Thread API*. All concepts, code structure, and methodologies were derived from these chapters. 
