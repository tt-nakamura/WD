#include<cmath>
#include "nr.h"
#include "constants.h"

static double beta, x0, slope;
static Vec_DP phi(2);

bool newt(Vec_DP&, void(const Vec_DP&, Vec_DP&));
void odeint(Vec_DP& y, void f(double, const Vec_DP&, Vec_DP&),
            double a, double b, double eps=1e-9);

static void diff_eq(double x, const Vec_DP& y, Vec_DP& dydx) {
    // Thomas-Fermi equation
    dydx[0] = y[1];
    if(x<=0) dydx[1] = slope;
    else dydx[1] = y[1]/x + 0.5*x*pow(sqrt(2*y[0]) + beta*x, 3);
}

static void shoot(const Vec_DP& p, Vec_DP& f) {
    phi[0] = 1; phi[1] = 0;
    slope = p[0];
    odeint(phi, diff_eq, 0, x0);
    f[0] = x0*phi[1] - 2*phi[0];
}

void FMT_initialize(double s) { slope = s; }

double FMT_EOS(double rho, double A, int Z)
// Feynmann-Metropolis-Teller equation of state
// input:
//   rho = density / g/cm^3
//   A = mass number
//   Z = atomic number
// return:
//   P = pressure / dyne/cm^2
// reference: H. A. Bethe and R. Jackiw
//   "Intermediate Quantum Mechanics" 3rd edition, p84--98
{
    static double lambda_e(hbar/me/c);// compton radius of electron
    static double P1(me*c*c/pow(lambda_e, 3)/3/PI/PI);
    static double b1(0.5*pow(0.75*PI, 2/3.)*lambda_e/e2);
    static double c1(2*e2*pow(4./3/PI, 1/3.));
    static double c2(e2/4/PI);
    static double rho1(3*amu/4/PI);
    static double beta1(pow(3*PI/4, 1/3.)/2/PI);
    double w,xe,Z23(pow(Z,2./3));
    Vec_DP p(1);

    w = pow(rho1*A*Z/rho, 1./3)/b1;
    x0 = sqrt(2*w);
    beta = beta1/Z23;
    p[0] = slope;
    if(newt(p, shoot))
        nrerror("shoot failed: bad initial guess");
    xe = c1*(beta1 + Z23*sqrt(phi[0]/w));
    return P1*pow(xe,4)*(0.2*xe - c2);
}