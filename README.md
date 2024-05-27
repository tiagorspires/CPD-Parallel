# Distributed and Parallel Computing - Matrix Multiplication Project

This project involves evaluating the performance of single-core and multi-core implementations of matrix multiplication algorithms. The study focuses on the impact of memory hierarchy on processor performance.

## Project Overview

The project implements and compares various matrix multiplication algorithms:
1. Simple Matrix Multiplication
2. Line Matrix Multiplication
3. Block Matrix Multiplication

Additionally, two parallel implementations of the Line Matrix Multiplication are included using OpenMP.

## Algorithms

### Simple Matrix Multiplication
A basic algorithm where each row of the first matrix is multiplied with each column of the second matrix.

### Line Matrix Multiplication
An enhanced version where each element of the first matrix is multiplied with the corresponding row in the second matrix.

### Block Matrix Multiplication
Matrices are divided into sub-matrices or 'blocks', which are then processed independently to improve memory access efficiency.

### Parallel Implementations
Two parallel versions of the Line Matrix Multiplication are implemented:
1. Parallelizing the outer loop (i loop).
2. Parallelizing the middle loop (k loop).

## Performance Metrics

Performance is measured using the Performance API (PAPI) for the C/C++ implementations, focusing on CPU efficiency and cache memory utilization. Metrics include execution time and cache misses at L1 and L2 levels.

## Results and Analysis

1. **Normal vs. Line Multiplication**: Line multiplication is faster and has lower cache misses due to more efficient memory access.
2. **Line vs. Block Multiplication**: Block multiplication shows varying performance based on block size, with 512 block size having the least data cache misses.
3. **Sequential vs. Parallel Line Multiplication**: Parallel implementations show speedup over the sequential version, with the first parallel version being more efficient due to lower overhead.

## Conclusions

The study highlights the importance of memory access patterns on algorithm efficiency and the benefits of parallelization. Different methods of parallelization and their impact on performance are also analyzed.

## Getting Started

### Prerequisites

- JDK 8 or higher
- GCC for C/C++ implementations with OpenMP support

