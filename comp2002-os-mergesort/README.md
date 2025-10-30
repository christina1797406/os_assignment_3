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
1. To clean up compiled files and exectable, run:
```bash
make clean
```

2. To compile the program:
```bash
make
```
This will create an executable called `test-mergesort`.

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

Testing was conducted using an automated Bash script (test.sh) that evaluates the correctness, performance, and stability of the parallel merge sort implementation.
All tests use the provided test-mergesort binary, which generates arrays, runs the algorithm, and verifies results with check_if_sorted().

The script produces a CSV file (test_results.csv) summarizing all tests, including input size, cutoff level, seed, and pass/fail status.

To run the tests, compile the program and run the test suite:
```bash
make clean && make
chmod +x test.sh
./test.sh ./test-mergesort all
```

You can also run individual sections:
```bash
./test.sh ./test-mergesort correctness
./test.sh ./test-mergesort performance
./test.sh ./test-mergesort stress
```

All test results are saved in test_results.csv.

### 1. Correctness testing:
We wanted to verify that the merge sort algorithm correctly sorts arrays under various conditions. This section includes: 

- Random arrays with different seeds (42, 1234, 99991)

- Small to medium sizes (n = 10, 100, 1000, 10000)

- Different cutoffs (0–3) to confirm correctness at different thread depths

- Edge cases: sorted arrays (ascending), reversed arrays (descending), equal arrays (all identical values)

Each test validates that the output is fully sorted using check_if_sorted(). All tests passed successfully (PASS), confirming both serial and parallel correctness. The command to run this test case is:

```bash
./test.sh ./test-mergesort correctness
```

### 2. Performance Testing: 
We wanted to measure runtime and confirm that parallel execution provides a performance speedup. The configuration for this section includes:
- Large input (n = 100,000,000)
- Cutoff levels from 0 to 5
Each run measured wall-clock time using gettimeofday(). Speedup was calculated as: Speedup = T serial / T parallel 
The result shows that peak speedup ≈ 4.6×, meeting the assignment’s requirement of at least 2× faster than serial execution. Beyond cutoff 4, performance plateaus due to thread overhead and hardware limits.

### 3. Stress and Stability Testing: 
- To ensure reliability under extreme workload and repeated runs. In this section, we test the program for very large input (n = 100,000,000, cutoff = 8), and repeated runs with n = 50,000,000, cutoff = 5, seeds 101–105. All stress tests completed successfully without crashes or memory leaks.


## Known Bugs

There are currently no functional bugs in the code implementation. However, please note that macOS users may see a warning during compilation. See [Building the Project](#building-the-project) for details.

## Reflection and Self Assessment

Through this project, our team significantly improved their understanding of multithreading and applications thereof in sorting algorithms. We gained practical experience in using pthread library, which deepened our understanding of thread creation, synchronisation, and resource management. We also gained knowledge about the intricacies of parallel algorithm design, particularly regarding balancing between parallel and serial execution to achieve optimal performance. 

Throughout the development of the prallel merge sort program, our group encountered several challenges that evaluated our understanding and problem-solving skills. One major challenge was implementing the pthread-based parallelism. Initially, managing multiple threads and ensuring proper synchronisation proved to be a complex task. We faced issues regarding race conditions and improper thread joins, which caused inconsistent sorting results. We accessed pthread documentation to gain insights into correct thread management techniques. 

Optimising the merge function for parallel execution was another challenge we faced, since the standard merge operation was designed for serial use, and adapting it to work efficiently in a multithreaded environment necessitated careful analysis of memory access patterns and data-copying methods. We used varying approaches to minimise overhead and ensure thread safety. Through iterative experimentation, such as varying the sizes of sub-arrays processed in parallel, adjusting when to switch to serial merging, and monitoring the impact on timing, we improved the performance of the merge phase under multithreading conditions.

Our team gained valuable insights into the challenges and considerations in parallel programming. Through the enforcement of the importance of reliable design, in-depth testing, and coninuous learning, this task equipped us with beneficial skills and knowledge to be used in future endeavors that involve multithreading and parallel computing.

## Sources Used

We relied exclusively on the textbook assigned for the course, specifically *Chapter 26:  Concurrency: An Introduction* and *Chapter 27: Interlude: Thread API*. All concepts, code structure, and methodologies were derived from these chapters. 
