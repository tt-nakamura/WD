#include<cmath>
#include "nr.h"
#include "WD.h"
#include "constants.h"

static WD *wd;
static void wd_ov_eq(double r, const Vec_DP& y, Vec_DP& f) { wd->ov_eq(r,y,f); }

WD::WD(double A) : eos(A), radius(3e6) { wd = this; }

void WD::build(double Pc, double Ps)
// compute mass and radius
// Pc = pressure at center / dyne/cm^2
// Ps = pressure at surface / dyne/cm^2
{
    static double EPS(1e-9);
    Vec_DP y(3),dy(3);
    double R(radius),R1(0);
    double& M = y[m_idx];
    double& P = y[P_idx];
    double& Phi = y[Phi_idx];
a:
    M = 0;// boundary condition at center
    P = Pc;
    Phi = 0;
    do {
        try { odeint(y, wd_ov_eq, R1, R); }
        catch(NRError) { R *= 0.9; goto a; }// retry
        if(P<Ps) { R *= 0.9; goto a; }// retry
        ov_eq(R,y,dy);
        R1 = R;
        R -= (P-Ps)/dy[P_idx];
    } while(fabs(R-R1) > EPS*fabs(R));
    mass = M;
    radius = R;
}

void WD::ov_eq(double r, const Vec_DP& y, Vec_DP& f)
// Oppenheimer-Volkoff equation
// r = distance from center / cm
// y[0] = mass within r / gram
// y[1] = pressure at r / dyne/cm^2
// y[2] = gravitational potential
// output f = dy/dr
// reference: S. L. Shapiro and S. A. Teukolsky
//   "Black Holes, White Dwarfs, and Neutron Stars" section 5.7
{
    if(r<=0) { f=0; return; }
    static double c2(c*c), Gc2(G/c2);
    const double& m = y[m_idx];
    const double& P = y[P_idx];
    double rho, r2(r*r), r3(r2*r);
    rho = eos.density(P);
    f[m_idx] = 4*PI*rho*r2;// dm/dr
    f[Phi_idx] = Gc2*(m + 4*PI*P*r3/c2)/(r2 - 2*Gc2*m*r);// dPhi/dr
    f[P_idx] = -(rho*c2 + P)*f[Phi_idx];// dP/dr
}