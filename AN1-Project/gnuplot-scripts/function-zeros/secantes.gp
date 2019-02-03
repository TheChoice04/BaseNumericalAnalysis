set xlabel "x"
set ylabel "f(x)"
set xzeroaxis
set yzeroaxis
set title "Secantes method"

plot "results/function-zeros/secantes.txt" w l title "successive iterations",\
"results/function-plot/functionData.txt" w l title "f(x)"