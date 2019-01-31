# ToDo
#### To do list for the project.

## Methods

	- Direct methods for solving linear systems
		- [Display] Gauss Elimination
		- [todo] LU Factorization
			- [todo] Cholesky Factorization
			- [todo] Doolittle Factorization
		- [todo] QR factorization
	- Iteratives methods for solving linear systems
		- [X] Jacobi method
		- [X] Gauss-Seidel method
		- [X] SOR method
		- [todo] Richardson
	- Recursive methods for function zeros
		- [Display] Bisection
		- [Display] Chord
		- [todo] Muller
		- [Display] Newton
		- [Display] Newton Quotient
		- [Display] Secantes
		- [Display] Steffensen
	- Interpolation methods for function approximation over equidistant/chebyshev knots
		- [Display, change knot value acquisition] Lagrange interpolate
		- [todo] Newton interpolate
		- [todo] Hermite interpolate
	- Least-square method for function approximation
		- [todo] Least-square systems
		
## Tasks

add `fclose()` and `free` in:
 - [ ] `src/direct/*.c`
 - [ ] `src/function-zeros/*.c`
 - [ ] `src/interpolation/*.c`
 - [X] `src/iteratives/*.c`
 - [X] `src/utils/*.c`