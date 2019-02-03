set xlabel "x"
set ylabel "f(x)"
set xzeroaxis
set yzeroaxis
set title "Chord method"

plot "results/function-zeros/chord.txt" w histeps title "successive iterations",\
"results/function-plot/functionData.txt" w l title "f(x)"