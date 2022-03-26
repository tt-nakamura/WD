#include<cmath>
#include "constants.h"
#include "EOS.h"

double EOS::rho_min = 20;
double EOS::rho1 = 1e4;
double EOS::rho2 = 8e6;
double EOS::P0 = 6e23;
double EOS::P_max = 1e30;
int EOS::N1 = 200;
int EOS::N2 = 200;
int EOS::N3 = 200;
static int N(EOS::N1 + EOS::N2 + EOS::N3 + 1);

EOS::EOS(double A_)
: A(A_), xa(N), ya(N), x2(N), y2(N)
{
    int i,j,k,A1(int(round(A)));
    double dr1 = pow(rho1/rho_min, 1./N1);
    double dr2 = pow(rho2/rho1, 1./N2);
    double dP,rho,P;

    FMT_initialize(-1.625);//low density limit
    BPS_EOS(rho, Z, P0, A1);// determine Z
    P_min = FMT_EOS(rho_min, A, Z);
    xa[0] = log(rho_min);
    ya[0] = log(P_min);
    for(i=k=1; i<=N1; i++, k++) {
        xa[k] = log(rho = rho_min*pow(dr1,i));
        ya[k] = log(P = FMT_EOS(rho,A,Z));
    }
    P1 = P;
    for(i=1; i<=N2; i++, k++) {
        xa[k] = log(rho = rho1*pow(dr2,i));
        ya[k] = log(P = Ch_EOS(rho,A,Z));
    }
    P2 = P;
    dP = pow(P_max/P2, 1./N3);
    for(i=1; i<=N3; i++, k++) {
        ya[k] = log(P = P2*pow(dP,i));
        BPS_EOS(rho, j, P, A1);
        xa[k] = log(rho);
    }
    rho_max = rho;
    spline(xa, ya, 1e30, 1e30, y2);
    spline(ya, xa, 1e30, 1e30, x2);
}

double EOS::density(double P)
// input P = pressure / dyne/cm^2
// return rho = density / g/cm^3
{
    double x;
    // extrapolate
    if(P <= P_min) return rho_min*pow(P/P_min, 0.3);
    if(P >= P_max) return rho_max*pow(P/P_max, 0.75);
    // spline interpolate on log-log scale
    splint(ya, xa, x2, log(P), x);
    return exp(x);
}

double EOS::pressure(double rho)
// input rho = density / g/cm^3
// return P = pressure / dyne/cm^2
{
    double y;
    // extrapolate
    if(rho <= rho_min) return P_min*pow(rho/rho_min, 10/3.);
    if(rho >= rho_max) return P_max*pow(rho/rho_max, 4/3.);
    // spline interpolate on log-log scale
    splint(xa, ya, y2, log(rho), y);
    return exp(y);
}