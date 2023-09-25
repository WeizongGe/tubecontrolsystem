#ifndef CURRENTSWITCH_H
#define CURRENTSWITCH_H

#include <stdint.h>
#include <QtMath>
///
/// \brief The currentswitch class
/// This Class is Used for Instantiating
/// a Current Data
class currentswitch
{
public:
    currentswitch();
    currentswitch(double a): currentswitch{a, a, a, a, a, a}{};
    currentswitch( double curA, double curB, double curC, double curD, double curE, double curF );
    currentswitch(const currentswitch &cur);

    double curA;
    double curB;
    double curC;
    double curD;
    double curE;
    double curF;

    double MinAbs() const;
    const currentswitch& operator=(const currentswitch& c);
    const currentswitch& operator-=(double* bias);
    friend double* operator+=(double * d, const currentswitch & c);
    friend const currentswitch operator/(const currentswitch &c, double div);
    friend const currentswitch operator-(const currentswitch &c, double* bias);
    friend const currentswitch operator+(const currentswitch &a, const currentswitch &b);
    friend const currentswitch operator*(double d, const currentswitch & a);
};

#endif // CURRENTSWITCH_H
