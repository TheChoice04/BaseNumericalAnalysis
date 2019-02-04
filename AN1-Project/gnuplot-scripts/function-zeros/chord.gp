set xlabel "x"
set ylabel "f(x)"
set xzeroaxis
set yzeroaxis
set title "Chord method"

plot "results/function-zeros/chord_display.txt" w l title "chord",\
     "results/function-plot/functionData.txt" w l title "f(x)"