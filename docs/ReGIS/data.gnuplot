set size square

set ylabel "Pageviews"
set xlabel "Time"

set terminal regis
plot "data.dat" using 1:2 with lines
