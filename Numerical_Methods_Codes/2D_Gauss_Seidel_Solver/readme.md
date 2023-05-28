Problem Description:  

-> In this problem, the objective is to develope the OpenMP version of the Gauss-Seidel iterative method to solve a 2D Poisson equation.  
-> The Jacobi-iterative method uses the older values at a given instant. Thus, there is no loop-carried dependency and it is straight forward to parallelize the Jacobi method solver.  
-> The Gauss-Seidel iterative method uses the updated/latest values at a given instant which creates a loop-carried dependency. So it cannot be parallelized directly.  
-> Consider the following Poisson equation:  
$$\nabla^2 \phi = -q; \hspace{5mm} q = 2 \left(2 - x^2 - y^2 \right); \hspace{5mm} \phi \left(\pm 1,y \right) = 0; \hspace{5mm} \phi \left(x, \pm 1 \right) = 0$$  
-> The discretized equation obtained using Gauss-Seidel method can be written as follows:  
$$\phi_{i,j}^{(k+1)} = \frac{\Delta^2}{4}q_{i,j} + \frac{1}{4} \left( \phi_{i+1,j}^{(k)} + \phi_{i-1,j}^{(k+1)} + \phi_{i,j+1}^{(k)} + \phi_{i,j-1}^{(k+1)} \right)$$  
where $\Delta = \Delta x = \Delta y$.  
-> An initial guess of $\phi(x, y) = 0$ is considered everywhere.  
-> The exact solution of the given problem is given by $\phi = (x^2-1)(y^2-1)$.  
-> As the Gauss-Seidel method cannot be parallelized directly, we can parallelize it if we modify our way of traversing the individual grid points.  
-> So instead of traversing in the Cartesian-like manner, we can traverse the grid points as:  
- Diagonal manner: traverse the points diagonally, which will cut-off the loop-carried dependency as we had earlier.  
- Red-Black coloring approach: in this method, we traverse in Cartesian-like manner only. However, each alternate points are colored as red and black. So in the $1^{st}$ pass, we only traverse through red points and in the next pass, we traverse through only black points. With this type of traversing method, the loop-carried dependency will be gone.  

-> The analytical solution is plotted with the obtained numerical solution of $\phi$ v/s $x$ for $y=0.5$ for $N=200$, $p=8$ for diagonal method and red-black coloring method.  
-> A speedup curve has also been plotted for $N=200$ to observe the parallel performance of the OpenMP-parallelized Gauss-Seidel iterative method.  
