# parallel-computing
Parallel Computing for wec task

# Instructions to run:
MPI files on linux(if windows use wsl)
1. mpiCC {filename}.cpp -o exec
2. mpirun -np {no of processors} exec
 
However if using windows then run ```g++ -o mpi_program.exe mpi_program.cpp -lmsmpi```

OpenMP is inbuilt in C++ so just run it as a normal program.

# Observations

The LU Decomposition and Sum of Array have been written using MPI program, while the Inverse of Matrix has been written using OpenMP.

1. The time does not vary much for small sizes < 10<sup>6</sup> and can be somewhat negligible
2. However, for large datasets, the need becomes larger.


