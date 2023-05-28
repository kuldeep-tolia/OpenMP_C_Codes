Problem Description:  

-> This is an OpenMP program for multiplication of two square matrices of size $N$ x $N$.  
-> While writing the programs for FORTRAN or C, one should keep in mind that FORTRAN has a colum-major layout, while C has a row-major layout.  
-> Thus, one should write the program in such a way to ensure there are maximum cache hits.  
-> Loop-unrolling uses a row-column combination of two matrices and calculates many elements at a given instant. This also reduces the chances of cache misses.  
