Problem Description:  

-> This is a program to integrate a given function numerically using the Simpson's rule. Consider evaluation of the following integral:  
$$I = \int_{1}^{\pi} \frac{sin(x)}{2x^3} \hspace{1mm} dx$$  
-> The exact value of the integration $I = 0.198573$.  
-> The Simpson's rule can be expressed using the following equation:  
$$I \approx \frac{h}{3} \left( f_0 + f_n + 4 \left[ \sum_{j=1,3,5,...}^{n-1} f_j \right] + 2 \left[ \sum_{j=2,4,6,...}^{n-2} f_j \right] \right)$$  
-> The computer program is parallelized using reduction clause and omp-for construct.  
