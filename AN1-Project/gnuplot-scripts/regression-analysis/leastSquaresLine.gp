set xlabel "x"
set ylabel "y"
set xzeroaxis
set yzeroaxis
set title "Least Squares Straight Line Approximation"

f(x) = m*x + q
fit f(x) "results/regression-analysis/dataCloud.txt" u 1:2 via m,q

plot "results/regression-analysis/leastSquaresLine.txt" u 1:2 w l title "Regression",\
     "" u 1:3 w p title "Points",\
     "" u 1:4 w i title "Error"
     
#f(x) title "Gnu-Plot approximation"