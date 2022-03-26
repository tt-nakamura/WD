reset
#set terminal aqua
set terminal postscript eps enhanced 24
set output "fig4.eps"
set yrange [0:1.5]
set xrange [0:0.03]
set ylabel 'M = mass  / solar mass'
set xlabel 'R = radius  / solar radius'
set xtics 0.01
set mxtics 5
set label "Sirius B" at 0.0088,1.02
set label "Procyon B" at 0.0034,0.56
set label "40 Eridani B" at 0.014,0.52
set bar 0
plot\
	'fig3-4_He.txt' u 4:3 t 'He' w l,\
	'fig3-4_C.txt' u 4:3 t 'C' w l,\
	'fig3-4_O.txt' u 4:3 t 'O' w l,\
	'fig3-4_Ne.txt' u 4:3 t 'Ne' w l,\
	'fig3-4_Mg.txt' u 4:3 t 'Mg' w l,\
	'fig3-4_Si.txt' u 4:3 t 'Si' w l,\
	'fig3-4_S.txt' u 4:3 t 'S' w l,\
	'fig3-4_Fe.txt' u 4:3 t 'Fe' w l,\
	'sirius.txt' u 3:1:4:2 not w xye lt 1 pt 1
