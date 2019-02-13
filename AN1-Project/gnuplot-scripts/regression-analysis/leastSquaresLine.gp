set xlabel "x"
set ylabel "y"
set xzeroaxis
set yzeroaxis
set title "Least Squares Straight Line Approximation"

f(x) = m*x + q
fit f(x) "results/regression-analysis/dataCloud.txt" using 1:2 via m,q

plot "results/regression-analysis/leastSquares.txt" w l title "Regression",\
     "results/regression-analysis/dataCloud.txt" title "Points",\
     f(x) title "Gnu-Plot approximation"