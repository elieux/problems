unset xlabel
set xtics 1
set xzeroaxis
set xrange [0:16]

unset ylabel
set ytics 1
set yzeroaxis
set yrange [0:16]

unset title
set format "%g"
set border 3
unset key

set terminal pngcairo truecolor size 640, 640
set output "analysis.png"

set parametric
set trange [0:2*pi]

