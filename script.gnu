title_text = sprintf("Frame %d", i + 1)
set title title_text

plot 'jeu_vie.txt' index (i) using 1:2:(0.5) with circle title "" lc rgb"black" fs transparent solid 0.9 noborder

i = i+1
if (i<=imax) reread