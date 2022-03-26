#include<cmath>
#include "constants.h"

double Ch_EOS(double rho, double A, int Z)
// Chandrasekhar equation of state for
//   degenerate fermion gas at zero-temperature
// input:
//   rho = density / g/cm^3
//   A = mass number
//   Z = atomic number
// return:
//   P = pressure / dyne/cm^2
// reference: S. L. Shapiro and S. A. Teukolsky
//   "Black Holes, White Dwarfs, and Neutron Stars" chapter 2
{
    static double lambda_e(hbar/me/c);// compton radius of electron
    static double epsilon_e(me*c*c/pow(lambda_e, 3));
    static double P1(epsilon_e/8/PI/PI);
    static double rho1(amu/3/PI/PI/pow(lambda_e, 3));
    static double cL1(0.3*pow(4./9/PI, 1/3.)*e2*epsilon_e/3/PI/PI);
    double x,x2,y,phi,cL(cL1*pow(Z,2./3));

    x = pow(rho/rho1*Z/A, 1./3);
    x2 = x*x;
    y = sqrt(1+x2);
    phi = x*y*(2*x2/3-1) + log(x+y);
    return P1*phi - cL*x2*x2;// electrostatic correction
}