#ifndef __WD_h__
#define __WD_h__

#include "EOS.h"

struct WD {// white dwarf
    enum { m_idx, P_idx, Phi_idx };
    double mass;// gram
    double radius;// cm
    EOS eos;// equation of state
    WD(double);
    void build(double, double=1e9);
    void ov_eq(double r, const Vec_DP& y, Vec_DP& f);
};

void odeint(Vec_DP& y, void f(double, const Vec_DP&, Vec_DP&),
            double a, double b, double eps=1e-9);

#endif // __WD_h__
