-> This section discusses about basic OpenMP functions, clauses, constructs like first/last/thread-private variables, parallel-do/for, nested parallelism, scheduling, etc.  
-> The computer programs only demonstrates the behaviour of a particular OpenMP function/clause/construct. To check the syntax/operation of a particular OpenMP clause/construct, you may refer to the following websites which provides description of each clause/construct:
- https://www.openmp.org/
- https://rookiehpc.github.io/openmp/docs/index.html  

-> To compile and run the codes, I have used gcc compiler.  
-> Compiling and running a C program:
- $ gcc -fopenmp file_name.c -g -Wall -lm -o ./output_name.out
- $ ./output_name.out <num_thread>
