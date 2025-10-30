# Operating Systems Assignment 3 - GROUP 14

## Authors

This project was developed by students of Group 14:
- Christina Nguyen a1797406
- Hong Minh Nguyen a1894168
- Samira Hazara a1852922

## Overview

This program implements a parallel merge sort using the *pthread* library to sort an integer array. Given a randomly generated integer array, it divides the sorting task across multiple threads according to a user-specified cutoff level. The user can specify a *cutoff* to control the number of recursive splitting levels to spawn new threads. When the cutoff is reached, further recursion is handles serially. The program is designed to showcase how multithreading and inter-thread synchronisation can accelerate the same divide-and-conquer merge sort algorithm, and it reports timing results to quantify speedups over the serial version.

## Manifest

- `mergesort.c`: Contains the implementations of merge(), my_mergesort(), parallel_mergesort(), and buildArgs() functions
- `mergesort.h`: Header file that declares global variables, data structures, and function prototypes used by merge modules
- `test-mergesort.c`: Test harness that sets up random arrays, invokes parallel_mergesort(), measures timing and verifies correctness
- `Makefile`: Build rules (compilation, linking with pthread, ect.)
- `README.md`: Documentation of the project, usage, design, and setup instructions

## Building the project

### Building instructions
1. To build the project, simply clone the repository to your local device.
```bash
git clone https://github.com/christina1797406/os_assignment_3.git
```
2. Change to directory named `comp2002-os-mergesort`.
```bash
cd comp2002-os-mergesort
```
3. Compile and run the program as specified in [Usage instructions](#usage-instructions) below.  
  
  
### Please note: Compilation discrepancy
The sorting logic works correctly on both Linux and macOS environments. However, a compilation discrepancy between Linux and macOS environments was observed when testing, related to the `-lpthread` flag in the `Makefile`. 

When compiling on macOS with Clang, the following warning was observed
```bash
clang: warning: -lpthread: 'linker' input unused [-Wunused-command-line-argument]
```
This happens because `-lpthread` is a linker flag, not a compiler flag. This triggers a warning, but does not affect the program's core functionality and performance. 

To avoid the warning on macOS, users may consider modifying the `Makefile` to only apply the linker flag when necessary. See [macOS warning and changes](#macos-warning-and-changes) for details.  


### macOS warning and changes 
For macOS users, please note that some changes are required for the implementation to run smoothly.

1. In file `test-mergesort.c`: Comment out or remove line 7.
```bash
// #include <error.h>     /* On MacOS you won't need this line */
```

2. In file `Makefile`: Split CFLAGS and LDFLAGS for compilation and linking respectively.

    Add:
    ```bash
    LDFLAGS = -lpthread
    ```

    Edit `test-mergesort` executable to reflect changes.
    ```bash
    test-mergesort: test-mergesort.o mergesort.o
    $(CC) -o $@ $^ $(LDFLAGS)
    ```

## Features and usage

### Key features include:
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
./test-mergesort <input_size> <cutoff_level> <seed>
```
where:
- `input_size` is the number of elements to be sorted
- `cutoff` is the depth of threads generated
- `seed` is the random seed to generate input array  
  

#### For example: 
The following line of code will run the parallel mergesort on 1000000 elements, creating threads up to level 2, with a random seed of 42.
```bash
./test-mergesort 1000000 2 42
```
The expected output should read:
```bash
Sorting 1000000 elements took 0.05 seconds.
```

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

There are currently no functional bugs in the code implementation. However, please note that macOS users may see a warning during compilation. See [Building the Project](#building-the-project) for details.

## Reflection and Self Assessment

Through this project, our team significantly improved their understanding of multithreading and applications thereof in sorting algorithms. We gained practical experience in using pthread library, which deepened our understanding of thread creation, synchronisation, and resource management. We also gained knowledge about the intricacies of parallel algorithm design, particularly regarding balancing between parallel and serial execution to achieve optimal performance. 

Throughout the development of the prallel merge sort program, our group encountered several challenges that evaluated our understanding and problem-solving skills. One major challenge was implementing the pthread-based parallelism. Initially, managing multiple threads and ensuring proper synchronisation proved to be a complex task. We faced issues regarding race conditions and improper thread joins, which caused inconsistent sorting results. We accessed pthread documentation to gain insights into correct thread management techniques. 

Optimising the merge function for parallel execution was another challenge we faced, since the standard merge operation was designed for serial use, and adapting it to work efficiently in a multithreaded environment necessitated careful analysis of memory access patterns and data-copying methods. We used varying approaches to minimise overhead and ensure thread safety. Through iterative experimentation, such as varying the sizes of sub-arrays processed in parallel, adjusting when to switch to serial merging, and monitoring the impact on timing, we improved the performance of the merge phase under multithreading conditions.

Our team gained valuable insights into the challenges and considerations in parallel programming. Through the enforcement of the importance of reliable design, in-depth testing, and coninuous learning, this task equipped us with beneficial skills and knowledge to be used in future endeavors that involve multithreading and parallel computing.

## Sources Used

We relied exclusively on the textbook assigned for the course, specifically *Chapter 26:  Concurrency: An Introduction* and *Chapter 27: Interlude: Thread API*. All concepts, code structure, and methodologies were derived from these chapters. 
