set xlabel "x"
set ylabel "f(x)"
set xzeroaxis
set yzeroaxis
set title "Bisection method"

plot "results/function-zeros/bisection.txt" w i title "successive iterations",\
"results/function-plot/functionData.txt" w l title "f(x)"