Problem Description:  

-> Consider an equation $u(x) = 7 - tan(x)$ that governs the transient heat conduction in a plane wall for $x = [-1,1]$.  
-> The analytical expression for the first derivative of the given equation is  
$$\frac{du}{dx} = -tan(x) - x sec^2x$$  
-> This is an OpenMP program to compute the first derivative using second and fourth-order accurate central-difference formulae.  
-> The grid size is varied as $\Delta x = 0.01, 0.001$  
-> The following are the central-difference formulae to compute the first derivative, along with their corresponding truncation errors:

- $2^{nd}$ order accurate:  
$$\left. \frac{du}{dx} \right|_{1} = \frac{u_2 - u_0}{2 \Delta x}, TE \sim (\Delta x^2)$$,

- $4^{th}$ order accurate:    
$$\left. \frac{du}{dx} \right|_2 = \frac{ u_0 - 8u_1 + 8u_3 - u_4}{ 12 \Delta x}, TE \sim (\Delta x^4)$$,  

where $TE$ denotes the truncation error.  
-> The results are compared with the analytical solution and plotted.  

NOTE: The corresponding $1^{st}$ / $2^{nd}$ order accurate finite-difference formulae is used to compute the first derivative near the boundary location nodes.  
