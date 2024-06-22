
imax = 100
i = 0

set term gif size 1200, 1200  animate delay 50
set output "jeu_de_la_vie.gif"

unset xtics
unset ytics
# set xtics 1,1
# set ytics 1,1
set grid

set xrange [0:52]
set yrange [0:52]

load "script.gnu"