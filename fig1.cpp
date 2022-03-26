#include<cmath>
#include<fstream>
#include "EOS.h"

void fig1(double A, const char *fn) {
    int i,n(128);
    double rho,P,dr;
    std::string s(fn);
    std::ofstream f;
    EOS e(A);

    f.open((s + "_fmt.txt").c_str());
    dr = pow(e.rho1/e.rho_min, 1./n);
    for(i=0; i<=n; i++) {
        rho = e.rho_min*pow(dr,i);
        P = e.pressure(rho);
        f << rho << ' ' << P << '\n';
    }
    f.close();

    f.open((s + "_ch.txt").c_str());
    dr = pow(e.rho2/e.rho1, 1./n);
    for(i=0; i<=n; i++) {
        rho = e.rho1*pow(dr,i);
        P = e.pressure(rho);
        f << rho << ' ' << P << '\n';
    }
    f.close();

    f.open((s + "_bps.txt").c_str());
    dr = pow(e.rho_max/e.rho2, 1./n);
    for(i=0; i<=n; i++) {
        rho = e.rho2*pow(dr,i);
        P = e.pressure(rho);
        f << rho << ' ' << P << '\n';
    }
    f.close();
}

main() {
    fig1(12.011, "fig1C");
    fig1(55.845, "fig1Fe");
}
