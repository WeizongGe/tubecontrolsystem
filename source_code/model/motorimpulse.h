#ifndef MOTORIMPULSE_H
#define MOTORIMPULSE_H

#include<QtMath>

using tIs = std::tuple<uint, uint, uint, uint, uint, uint>;

class MotorImpulse
{
/// Fields:
public:
    uint a;
    uint b;
    uint c;
    uint d;
    uint e;
    uint f;

/// MemberFunctions:
public:
/// Constructor and Desturctor:
    MotorImpulse():
        MotorImpulse{0}{};

    explicit MotorImpulse(uint one):
        MotorImpulse{one, one, one, one, one, one}{}

    MotorImpulse(uint ia, uint ib, uint ic, uint id, uint ie, uint iff):
        a(ia), b(ib), c(ic), d(id), e(ie), f(iff){}

    virtual ~MotorImpulse() = default;

/// helpFunction:
    float toLength(const float & ratio) const;
    auto MinVal()const;
    void SetZero();

private:
    uint a0 = 0;
    uint b0 = 0;
    uint c0 = 0;
    uint d0 = 0;
    uint e0 = 0;
    uint f0 = 0;
};


#endif // MOTORIMPULSE_H
