set term png size 1200, 900
set output "nb_cellules_temps.png"

set ylabel "nombre de cellules"
set xlabel "temps"

plot "resultats.txt" u 2:1 w lines title ""
