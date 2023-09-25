#include "currentswitch.h"

currentswitch::currentswitch()
    : curA(0), curB(0), curC(0), curD(0), curE(0), curF(0)
{}

currentswitch::currentswitch(double curA, double curB, double curC, double curD, double curE, double curF )
    : curA(curA), curB(curB), curC(curC), curD(curD), curE(curE), curF(curF)
{}

currentswitch::currentswitch(const currentswitch &cur)
    : curA(cur.curA), curB(cur.curB), curC(cur.curC), curD(cur.curD), curE(cur.curE), curF(cur.curF)
{}

double currentswitch::MinAbs() const
{
    return std::min(std::abs(curA),
                    std::min(std::abs(curB),
                             std::min(std::abs(curC),
                                      std::min(std::abs(curD),
                                               std::min(std::abs(curE), std::abs(curF))))));
}

const currentswitch & currentswitch::operator=(const currentswitch &c)
{
    if(this == &c) return *this;
    curA = c.curA;
    curB = c.curB;
    curC = c.curC;
    curD = c.curD;
    curE = c.curE;
    curF = c.curF;
    return *this;
}

const currentswitch & currentswitch::operator-=(double *bias)
{
    curA -= bias[0];
    curB -= bias[1];
    curC -= bias[2];
    curD -= bias[3];
    curE -= bias[4];
    curF -= bias[5];
    return *this;
}

double * operator+=(double * d, const currentswitch & c)
{
    d[0] += c.curA;
    d[1] += c.curB;
    d[2] += c.curC;
    d[3] += c.curD;
    d[4] += c.curE;
    d[5] += c.curF;
    return d;
}

const currentswitch operator/(const currentswitch& c, double div)
{
    return currentswitch{
        c.curA/div,
        c.curB/div,
        c.curC/div,
        c.curD/div,
        c.curE/div,
        c.curF/div
    };
}

const currentswitch operator-(const currentswitch& c, double *bias)
{
    return currentswitch{
      c.curA - bias[0],
      c.curB - bias[1],
      c.curC - bias[2],
      c.curD - bias[3],
      c.curE - bias[4],
      c.curF - bias[5]
    };
}

const currentswitch operator*(double d, const currentswitch& a)
{
    return currentswitch(d * a.curA, d* a.curB, d* a.curC, d * a.curD, d* a.curE, d* a.curF);
}

const currentswitch operator+(const currentswitch& a, const currentswitch & b)
{
    return currentswitch(a.curA + b.curA, a.curB + b.curB, a.curC + b.curC,
                         a.curD + b.curD, a.curE + b.curE, a.curF + b.curF);
}
