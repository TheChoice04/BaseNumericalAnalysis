set xlabel "no. iter"
set ylabel "error norm"
set title "jacobi iterative method"

plot "results/iteratives/jacobi.txt" w l title "error norm"