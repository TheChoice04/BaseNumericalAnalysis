set xlabel "no. iter"
set ylabel "error norm"
set xzeroaxis
set yzeroaxis
set title "Gauss-Seidel iterative method"

plot "results/iteratives/gaussSeidel.txt" w l title "error norm"