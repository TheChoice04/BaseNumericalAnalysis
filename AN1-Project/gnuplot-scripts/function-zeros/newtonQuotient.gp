set xlabel "x"
set ylabel "f(x)"
set xzeroaxis
set yzeroaxis
set title "Newton Quotient method"

plot "results/function-zeros/newtonQuotient_display.txt" w l title "successive iterations",\
     "results/function-plot/functionData.txt" w l title "f(x)"