set xlabel "x"
set ylabel "f(x)"
set xzeroaxis
set yzeroaxis
set title "Methods comparison"

plot "results/function-zeros/bisection.txt" w i title "bisection",\
     "results/function-zeros/chord_display.txt" w l title "chord",\
     "results/function-zeros/newton_display.txt" w l title "newton",\
     "results/function-zeros/newtonQuotient_display.txt" w l title "newton quotient",\
     "results/function-zeros/secantes_display.txt" w l title "secantes",\
     "results/function-zeros/steffensen.txt" title "steffensen",\
     "results/function-plot/functionData.txt" w l title "f(x)"