set xlabel "no. iter"
set ylabel "error norm"
set title "Successive Over Relaxation iterative method"

plot "results/iteratives/SOR.txt" w l title "error norm"