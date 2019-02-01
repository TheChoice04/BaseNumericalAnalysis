set xlabel "no. iter"
set ylabel "error norm"
set title "Richardson iterative method"

plot "results/iteratives/richardson.txt" w l title "error norm"