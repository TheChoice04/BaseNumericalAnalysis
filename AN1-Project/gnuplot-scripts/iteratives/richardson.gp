set xlabel "no. iter"
set ylabel "error norm"
set xzeroaxis
set yzeroaxis
set title "Richardson iterative method"

plot "results/iteratives/richardson.txt" w l title "error norm"