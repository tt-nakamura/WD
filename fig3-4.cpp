#include<cmath>
#include<fstream>
#include "WD.h"
#include "constants.h"
#include<iostream>
void fig34(double A, const char *fname) {
    int i,n(256);
    double rho1(1e2), rho2(3e11);
    double rho, P, d_rho(pow(rho2/rho1, 1./n));
    std::ofstream f(fname);
    WD w(A);
    for(i=0; i<=n; i++) {
        rho = rho1*pow(d_rho,i);
        P = w.eos.pressure(rho);
        w.build(P);
        f << rho << ' ' << P << ' ';
        f << w.mass/M_solar << ' ';
        f << w.radius/R_solar << '\n';
    }
}

main() {
    fig34(4.0026, "fig3-4_He.txt");
    fig34(12.011, "fig3-4_C.txt");
    fig34(15.999, "fig3-4_O.txt");
    fig34(20.180, "fig3-4_Ne.txt");
    fig34(24.305, "fig3-4_Mg.txt");
    fig34(28.086, "fig3-4_Si.txt");
    fig34(32.065, "fig3-4_S.txt");
    fig34(55.845, "fig3-4_Fe.txt");
}
