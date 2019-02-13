set xlabel "x"
set ylabel "y=f(x)"
set xzeroaxis
set yzeroaxis
set title "Lagrange Interpolate"

plot "results/polynomialApproximation/lagrange_interpolate.txt" u 1:2 w l title "interpolate",\
     "" u 1:3 w l title "real",\
     "" u 1:4 w l title "error",\
     "results/polynomialApproximation/knot_values.txt" title "knots"