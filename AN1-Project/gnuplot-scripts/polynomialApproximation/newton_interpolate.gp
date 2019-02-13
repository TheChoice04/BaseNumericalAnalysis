set xlabel "x"
set ylabel "y=f(x)"
set xzeroaxis
set yzeroaxis
set title "Newton Interpolate"

plot "results/polynomialApproximation/newton_interpolate.txt" u 1:2 w l title "interpolate",\
     "" u 1:3 w l title "real",\
     "" u 1:4 w l title "error",\
     "results/polynomialApproximation/knot_values.txt" title "knots"