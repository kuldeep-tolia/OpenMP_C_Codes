Problem Description:  

-> This is an OpenMP program for odd-even transposition sort.  
-> Two arrays of size $N = 10,50$ containing random integers are sorted in non-descending order.  
-> Parallelizing bubble sort results in loop/data-carried dependency. Thus, odd-even transposition sort offers partial degree of parallelism.  
-> It is basically a variation of bubble sort. The algorithm is divided into two phases - Odd and Even Phase.  
-> The algorithm runs until the array elements are sorted and in each iteration two phases occurs- Odd and Even Phases. In the odd phase, we perform a bubble sort on odd indexed elements and in the even phase, we perform a bubble sort on even indexed elements.
