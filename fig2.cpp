#include<fstream>
#include<cmath>
#include "EOS.h"

void fig2(int A, const char *fname) {
    int i,n(256),Z,d(1);
    double rho,P,dP(pow(EOS::P_max/EOS::P0, 1./n));
    std::ofstream f(fname);
    extern double BPS_mu_n;
    for(i=0; i<=n; i++) {
        P = EOS::P0*pow(dP,i);
        BPS_EOS(rho,Z,P,A);
        f << rho << ' ' << (A-Z);
        if(d && BPS_mu_n>=0) {
            f << ' ' << rho;
            d = 0;
        }
        f << '\n';
    }
}

main() {
    fig2(4,  "fig2He.txt");
    fig2(12, "fig2C.txt");
    fig2(16, "fig2O.txt");
    fig2(20, "fig2Ne.txt");
    fig2(24, "fig2Mg.txt");
    fig2(28, "fig2Si.txt");
    fig2(32, "fig2S.txt");
    fig2(56, "fig2Fe.txt");
}
