#include<cmath>
#include "constants.h"

double semf(int A, int Z)
// semi-empirical mass formula for nucleus
// input:
//   A = mass number
//   Z = atomic number
// return:
//   mass of nucleus / gram
// reference: A. de Shalit and H. Feshbach
//   "Theoretical Nuclear Physics" vol. 1, p126
{
    static double c1(15.68*MeV/c/c);
    static double c2(18.56*MeV/c/c);
    static double c3(0.717*MeV/c/c);
    static double c4(28.1*MeV/c/c);
    static double c5(34*MeV/c/c);
    int N(A-Z);
    double A13,asym,pair,B;
    A13 = pow(A, 1/3.);
    asym = pow(N-Z, 2)/A;
    pair = (A&1 ? 0 : (Z&1 ? 1:-1))/pow(A, 0.75);
    // binding energy
    B = c1*A - c2*A13*A13 - c3*Z*Z/A13 - c4*asym - c5*pair;
    return mp*Z + mn*N - B;
}

double BPS_mu_n;// neutron chemical potential / gram

void BPS_EOS(double& rho, int& Z, double P, int A)
// Baym-Pethick-Sutherland equation of state
// input:
//   P = pressure / dyne/cm^2
//   A = mass number
// output:
//   rho = density / g/cm^3
//   Z = atomic number of minimum energy state
// reference: G. Baym, C. Pethick and P. Sutherland
//   The Astrophysical Journal 170 (1971) 299
{
    static double EPS(1e-9), x(1);
    static double P0(me*c*c*pow(me*c/hbar,3)/3/PI/PI);
    static double n0(pow(me*c/hbar, 3)/3/PI/PI);
    static double rho0(me*n0);
    static double c1(0.3*pow(4/9./PI, 1/3.)*e2);
    static double c2(3*c1*rho0);

    int z;
    double v(P/P0),x0,g,x2,y,f,dx,cL1,cL2;

    BPS_mu_n = 1e300;
    for(z=1; z<=A; z++) {
        cL1 = c1*pow(z, 2./3);
        do {// solve for x (electron relativity parameter)
            x2 = x*x; y = sqrt(1+x2);
            f = 0.375*(x*y*(2*x2/3-1) + log(x+y)) - cL1*x2*x2;
            dx = (v-f)/x2/(x2/y - 4*x*cL1);
            x += dx;
        } while(fabs(dx) > EPS*fabs(x));
        // minimize Gibbs free energy
        g = (semf(A,z) + z*me*(y - cL1*4*x))/A - mn;
        if(g >= BPS_mu_n) continue;
        BPS_mu_n = g;
        x0 = x;
        Z = z;
    }
    x = x0; x2 = x*x; y = sqrt(1+x2);
    cL2 = c2*pow(Z, 2./3);
    rho = 0.375*rho0*(x*y*(2*x2+1) - log(x+y));
    rho += n0*x2*x/Z*semf(A,Z) - cL2*x2*x2;
}