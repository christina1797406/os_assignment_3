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

This section should tell the user how to build your code.  If you are
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

This section should detail how you tested your code. Simply stating "I ran
it a few times and it seems to work" is not sufficient. Your testing needs
to be detailed here.

## Known Bugs

List known bugs that you weren't able to fix (or ran out of time to fix).

## Reflection and Self Assessment

Discuss the issues you encountered during development and testing. What
problems did you have? What did you have to research and learn on your own?
What kinds of errors did you get? How did you fix them?

What parts of the project did you find challenging? Is there anything that
finally "clicked" for you in the process of working on this project? How well
did the development and testing process go for you?

## Sources Used

If you used any sources outside of the textbook, you should list them here. 
If you looked something up on stackoverflow.com or you use help from AI, and 
fail to cite it in this section, it will be considered plagiarism and dealt 
with accordingly. So be safe CITE!
