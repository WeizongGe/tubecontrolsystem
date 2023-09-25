#include "motorimpulse.h"

using std::min;
using std::abs;

auto MotorImpulse::MinVal() const
{
    return min(a - a0, min(b - b0, min(c - c0, min(d - d0, min(e - e0, f - f0)))));
}

float MotorImpulse::toLength(const float & ratio) const
{
    return  ratio * static_cast<float>(MinVal());
}

void MotorImpulse::SetZero()
{
    a0 = a;
    b0 = b;
    c0 = c;
    d0 = d;
    e0 = e;
    f0 = f;
}
