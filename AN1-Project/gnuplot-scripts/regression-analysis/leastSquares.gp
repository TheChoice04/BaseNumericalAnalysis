set xlabel "x"
set ylabel "y"
set xzeroaxis
set yzeroaxis
set title "Least Squares Approximation"

plot "results/regression-analysis/leastSquares.txt" w l title "Regression",\
     "results/regression-analysis/dataCloud.txt" title "Points"