Problem Description:  

-> The tri-diagonal matrix system obtained from, say, using implicit finite-difference derivative schemes (like Pade's scheme) can be solved using Thomas algorithm. However, Thomas algorithm cannot be parallelized due to the data-carried dependency.  
-> The recursive doubling algorithm has scope for parallelization as it pushes out the sub/super diagonals out with each phase-step. After the end of the elimination phase, we have a diagonal matrix in hand which can easily be solved for. Hence, recursive doubling algorithm offers partial degree of parallelizm which Thomas algorithm does not provide.  
-> Consider the calculation of the derivative of the following function,  
$$f(x) = sin(5x), \hspace{4mm} 0 \leq x \leq 5$$  
using $4^{th}$ order accurate Pade scheme for the interior and $3^{rd}$ order accurate one-sided Pade scheme near the boundaries.  
-> Pade's scheme is given as:  
$$g_0 + 2g_1 = \frac{1}{h} \left( -\frac{5}{2}f_0 + 2f_1 + \frac{1}{2}f_2 \right)$$  

$$g_{j+1} + 4g_j + g_{j-1} = \frac{3}{h} \left( f_{j+1} - f_{j-1} \right)$$  

$$g_n + 2g_{n-1} = \frac{1}{h} \left( \frac{5}{2}f_n - 2f_{n-1} - \frac{1}{2}f_{n-2} \right)$$  

where $g(x) = f'(x)$, $h$ is the grid spacing, $n$ is the number of grid points in $x$ direction and $j = 1,2,...,n-1$.  
-> The analytical solution is plotted with the obtained numerical solution for $n = 100$, and number of threads $p = 2$.  
-> A speedup curve has also been plotted for $n = 1000$ to observe the parallel performance of the OpenMP-parallelized recursive doubling algorithm.  
