reset
#set terminal aqua
set terminal postscript eps enhanced 24
set output "fig1.eps"
set key left Left reverse
set xrange [10:1e12]
set yrange [1e12:1e30]
set xlabel '{/Symbol r} = density  / g/cm^3'
set ylabel 'P = pressure  / Pascal'
set logscale xy
set format xy "10^{%T}"
set label "A=12 (Carbon)" at graph 0.07,graph 0.18 rotate by 36
set label "A=56 (Iron)" at graph 0.12,graph 0.09 rotate by 38
set ytics 1e4
plot\
	'fig1C_fmt.txt' u 1:($2/10) t 'Feynman-Metropolis-Teller' lt 5 w l,\
	'fig1C_ch.txt' u 1:($2/10)  t 'Chandrasekhar' lt 3 w l,\
	'fig1C_bps.txt' u 1:($2/10)  t 'Baym-Pethick-Sutherland' lt 1 w l,\
	'fig1Fe_fmt.txt' u 1:($2/10) not lt 5 w l,\
	'fig1Fe_ch.txt' u 1:($2/10)  not lt 3 w l,\
	'fig1Fe_bps.txt' u 1:($2/10)  not lt 1 w l
