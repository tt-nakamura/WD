reset
#set terminal aqua
set terminal postscript eps enhanced 24
set output "fig2.eps"
set key left Left reverse
set xrange [3e6:1e12]
set xlabel '{/Symbol r} = density  / g/cm^3'
set ylabel 'N = number of neutrons'
set logscale x
set format x "10^{%T}"
set ytics 10
set mytics 2
set label "Fe" at 4e6,30 font "Helvetica,20"
set label "S"  at 4e6,16 font "Helvetica,20"
set label "Si" at 4e6,14 font "Helvetica,20"
set label "Mg" at 4e6,12 font "Helvetica,20"
set label "Ne" at 4e6,10 font "Helvetica,20"
set label "O"  at 4e6,8 font "Helvetica,20"
set label "C"  at 4e6,6 font "Helvetica,20"
set label "He" at 4e6,2 font "Helvetica,20"
plot\
	'fig2Fe.txt' not w l, 'fig2Fe.txt' u 3:2 not pt 2,\
	'fig2S.txt' not w l, 'fig2S.txt' u 3:2 not pt 2,\
	'fig2Si.txt' not w l, 'fig2Si.txt' u 3:2 not pt 2,\
	'fig2Mg.txt' not w l, 'fig2Mg.txt' u 3:2 not pt 2,\
	'fig2Ne.txt' not w l, 'fig2Ne.txt' u 3:2 not pt 2,\
	'fig2O.txt' not w l, 'fig2O.txt' u 3:2 not pt 2,\
	'fig2C.txt' not w l, 'fig2C.txt' u 3:2 not pt 2,\
	'fig2He.txt' not w l,\
	'fig2He.txt' u 3:2 t 'neutron drip' pt 2
