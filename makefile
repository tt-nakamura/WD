OBJ = FMT_EOS.o Ch_EOS.o BPS_EOS.o EOS.o spline.o odeint.o newt.o ludcmp.o

fig1: fig1.o $(OBJ)
	g++ fig1.o $(OBJ)
fig2: fig2.o $(OBJ)
	g++ fig2.o $(OBJ)
fig3-4: fig3-4.o WD.o $(OBJ)
	g++ fig3-4.o WD.o $(OBJ)
