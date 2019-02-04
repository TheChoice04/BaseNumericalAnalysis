set xlabel "no. iter"
set ylabel "error norm"
set title "Gauss-Seidel iterative method"

plot "results/iteratives/gaussSeidel.txt" w l title "error norm"