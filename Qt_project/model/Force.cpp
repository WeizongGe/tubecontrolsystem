#include "Force.h"

Force::Force()
    : time(0), FA(0), FB(0), FC(0), FD(0), FE(0), FF(0)
{}

Force::Force(double time, double FA, double FB, double FC, double FD, double FE, double FF)
    : time(time), FA(FA), FB(FB), FC(FC), FD(FD), FE(FE), FF(FF)
{}

Force::Force(const Force &ft)
    : time(ft.time), FA(ft.FA), FB(ft.FB), FC(ft.FC), FD(ft.FD), FE(ft.FE), FF(ft.FF)
{}

double Force::MinVal()
{
    return std::min( std::abs(FA),
                     std::min(std::abs(FB),
                              std::min(std::abs(FC),
                                       std::min(std::abs(FD),
                                                std::min(std::abs(FE), std::abs(FF))))));
}

double Force::MaxVal()
{
    return std::max( std::abs(FA),
                     std::max(std::abs(FB),
                              std::max(std::abs(FC),
                                       std::max(std::abs(FD),
                                                std::max(std::abs(FE), std::abs(FF))))));
}

const Force& Force::operator=(const double &d)
{
    FA = d;
    FB = d;
    FC = d;
    FD = d;
    FE = d;
    FF = d;
    return *this;
}

const Force& Force::operator=(const Force& f)
{
    if(this == &f) return *this;
    time = f.time;
    FA = f.FA;
    FB = f.FB;
    FC = f.FC;
    FD = f.FD;
    FE = f.FE;
    FF = f.FF;
    return *this;
}

const Force& Force::operator-=(double *bias)
{
    FA -= bias[0];
    FB -= bias[1];
    FC -= bias[2];
    FD -= bias[3];
    FE -= bias[4];
    FF -= bias[5];
    return *this;
}

const Force& Force::operator+=(const Force &f)//这里是否应该是 "-="
{
    if(this == &f) return *this;
    FA -= f.FA;
    FB -= f.FB;
    FC -= f.FC;
    FD -= f.FD;
    FE -= f.FE;
    FF -= f.FF;
    return *this;
}

double * operator+=(double * d, const Force & f)
{
    d[0] += f.FA;
    d[1] += f.FB;
    d[2] += f.FC;
    d[3] += f.FD;
    d[4] += f.FE;
    d[5] += f.FF;
    return d;
}

double * operator+(double * d, const Force & f)
{
    d[0] = f.FA;
    d[1] = f.FB;
    d[2] = f.FC;
    d[3] = f.FD;
    d[4] = f.FE;
    d[5] = f.FF;
    return d;
}
///
/// \brief operator +
/// \param f_cur
/// \param f_pre
/// \return
/// Notice:
///        第一个参数必须为现在值，不然时间值设定可能与你想的不符
const Force operator+(const Force & f_cur, const Force & f_pre)
{
    return Force(f_cur.time,
                 f_cur.FA + f_pre.FA,
                 f_cur.FB + f_pre.FB,
                 f_cur.FC + f_pre.FC,
                 f_cur.FD + f_pre.FD,
                 f_cur.FE + f_pre.FE,
                 f_cur.FF + f_pre.FF);
}

const Force operator-(const Force & f,double* bias)
{
    return Force(f.time,
                 f.FA - bias[0],
                 f.FB - bias[1],
                 f.FC - bias[2],
                 f.FD - bias[3],
                 f.FE - bias[4],
                 f.FF - bias[5]);
}

const Force operator/(const Force & f, double div)
{
    return Force(f.time,
                 f.FA/div,
                 f.FB/div,
                 f.FC/div,
                 f.FD/div,
                 f.FE/div,
                 f.FF/div);
}

const Force operator*(double a, const Force& f)
{
    return Force(f.time, a * f.FA, a * f.FB, a* f.FC, a * f.FD, a * f.FE, a* f.FF);
}

const Force operator*(double* eta, const Force& f)
{
    return Force(f.time, eta[0] * f.FA, eta[1] * f.FB, eta[2]* f.FC, eta[3] * f.FD, eta[4] * f.FE, eta[5] * f.FF);
}
