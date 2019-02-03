set xlabel "x"
set ylabel "f(x)"
set xzeroaxis
set yzeroaxis
set title "Muller method"

plot "results/function-zeros/muller.txt" w histeps title "successive iterations",\
"results/function-plot/functionData.txt" w l title "f(x)"