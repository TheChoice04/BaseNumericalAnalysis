set xlabel "x"
set ylabel "f(x)"
set xzeroaxis
set yzeroaxis
set title "Steffensen method"

plot "results/function-zeros/steffensen.txt" w l title "successive iterations",\
"results/function-plot/functionData.txt" w l title "f(x)"