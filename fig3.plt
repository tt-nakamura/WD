reset
#set terminal aqua
set terminal postscript eps enhanced 24
set output "fig3.eps"
set key left Left reverse font "Helvetica,18"
set xrange [1e2:1e12]
set yrange [0:1.5]
set xlabel '{/Symbol r}_c = central density  / g/cm^3'
set ylabel 'M = mass  / solar mass'
set logscale x
set format x "10^{%T}"
set xtics 1e2
plot\
	'fig3-4_He.txt' u 1:3 t 'A=4   (Helium)' w l,\
	'fig3-4_C.txt' u 1:3 t 'A=12 (Carbon)' w l,\
	'fig3-4_O.txt' u 1:3 t 'A=16 (Oxygen)' w l,\
	'fig3-4_Ne.txt' u 1:3 t 'A=20 (Neon)' w l,\
	'fig3-4_Mg.txt' u 1:3 t 'A=24 (Magnesium)' w l,\
	'fig3-4_Si.txt' u 1:3 t 'A=28 (Silicon)' w l,\
	'fig3-4_S.txt' u 1:3 t 'A=32 (Sulfur)' w l,\
	'fig3-4_Fe.txt' u 1:3 t 'A=56 (Iron)' w l
