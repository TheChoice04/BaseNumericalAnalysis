# BaseNumericalAnalysis

This `C` repository, developed during the course of [**AN410** _Numerical Analysis_ - A.A.2019/19](http://www.mat.uniroma3.it/users/ferretti/bacheca.html), is a collection of programs for scientific calculus application.

## Dependecies

Even if it is not necessary, an useful tool called by the program is [`GnuPlot`](http://www.gnuplot.info).
To change the path to the executable of `GnuPlot` it is necessary to change the macro defined in
`src/utils/an1.utils.h`.

## Programs Implemented
  
  - Direct methods for solving linear systems
    - [X] Gauss Elimination
    - [ ] LU Factorization
      - [ ] Cholesky Factorization
      - [ ] Doolittle Factorization
    - [ ] QR factorization
  - Iteratives methods for solving linear systems
    - [X] Jacobi method
    - [X] Gauss-Seidel method
    - [X] Sor method
    - [X] Richardson
  - Recursive methods for function zeros
    - [X] Bisection
    - [X] Chord
    - [ ] Muller
    - [X] Newton
    - [X] Newton Quotient
    - [X] Secantes
    - [X] Steffensen
  - Interpolation methods for function approximation over equidistant/chebyshev knots
    - [X] Lagrange interpolate
    - [ ] Newton interpolate
    - [ ] Hermite interpolate
  - Least-square method for function approximation
    - [ ] Least-square systems


## Structure of the Repository

 - gnuplot-scripts: Contains the `GnuPlot` scripts called from inside the C code.
 - results: Contains the computation output of the program.
 - source: Contains all the default parsing `.txt` files.
 - src: Source folder of the `.c` and `.h` files:
   - direct: direct methods implementation
   - function-zeros: function zeros evaluation methods implementation
   - interpolation: interpolation methods implementation
   - iteratives: iteratives methods implementation
   - utils: all the utilities usefull for the program
     - utils_functions.c
     - utils_matrices.c
     - utils_systems.c
     - utils_utility.c
     - utils_vectors.c


## Author
 - [Elia Onofri](https://github.com/eOnofri04) - [Ln](https://www.linkedin.com/in/elia-onofri-80b403173/) (elia.onofri4@gmail.com)
 
## Bibliography Link
 - [AN410 lecture notes](http://www.mat.uniroma3.it/users/ferretti/corso.pdf) by R. Ferretti;
 - **Matematica Numerica ed.3** by _A. Quarteroni - R. Sacco - F. Saleri_ [QSS08](https://www.researchgate.net/publication/45627395_Matematica_Numerica);
