#ifndef __EOS_h__
#define __EOS_h__

#include "Vec.h"

struct EOS {// equation of state
    static double rho_min;// minimum density / g/cm^3
    static double rho1;// FMT maximum density / g/cm^3
    static double rho2;// Ch maximum density / g/cm^3
    static double P0;// BPS minimum pressure / dyne/cm^2
    static double P_max;// maximum pressure / dyne/cm^2
    static int N1;// FMT number of mesh points
    static int N2;// Ch  number of mesh points
    static int N3;// BPS number of mesh points
    int Z;// atomic number
    double A;// mass number
    double rho_max;// maximum density / g/cm^3
    double P_min;// minimum pressure / dyne/cm^2
    double P1;// FMT maximum pressure / dyne/cm^2
    double P2;// Ch maximum pressure / dyne/cm^2
    Vec_DP xa, ya, x2, y2;// for spline interpolation
    EOS(double);
    double density(double);
    double pressure(double);
};

void FMT_initialize(double);
double FMT_EOS(double rho, double A, int Z);
double Ch_EOS(double rho, double A, int Z);
void BPS_EOS(double& rho, int& Z, double P, int A);

void spline(const Vec_DP &x, const Vec_DP &y, double yp1, double ypn, Vec_DP &y2);
void splint(const Vec_DP &xa, const Vec_DP &ya, const Vec_DP &y2a, double x, double &y);

#endif // __EOS_h__
