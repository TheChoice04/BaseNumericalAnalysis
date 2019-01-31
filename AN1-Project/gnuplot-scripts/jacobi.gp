set xlabel "no. iter"
set ylabel "error norm"
set title "Jacobi iterative method"

plot "results/iteratives/jacobi.txt" w l title "error norm"