#ifndef FORCE_H
#define FORCE_H


#include <QtMath>
///
/// \brief The Force class
/// This Class is Used for Instantiate
/// a Force object
class Force
{
public:
    Force();
    Force(double time, double FA, double FB, double FC, double FD, double FE, double FF);
    Force(const Force &ft);

    double time;
    double FA;
    double FB;
    double FC;
    double FD;
    double FE;
    double FF;

    double MaxVal();
    double MinVal();
    const Force& operator=(const double &d);
    const Force& operator=(const Force& f);
    const Force& operator-=(double* bias);
    const Force& operator+=(const Force& f);    
    //operator double*();
    friend double* operator+(double* d,const Force & f);
    friend double* operator+=(double* d, const Force & f);    
    friend const Force operator/(const Force& f, double div);
    friend const Force operator-(const Force& f, double* bias);
    friend const Force operator+(const Force & f1, const Force & f2);
    friend const Force operator*(double a, const Force& f);
    friend const Force operator*(double* eta, const Force& f);
};

#endif // FORCE_H
