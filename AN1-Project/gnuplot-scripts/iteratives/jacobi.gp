set xlabel "no. iter"
set ylabel "error norm"

set xzeroaxis
set yzeroaxis
set title "Jacobi iterative method"

plot "results/iteratives/jacobi.txt" w l title "error norm"