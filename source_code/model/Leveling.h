#ifndef LEVELING_H
#define LEVELING_H

#include "typedef.h"
///Leveling signals
///

class Leveling
{
public:
    Leveling();

    int a;
    int b;
    int c;
    int d;
    int e;
    int f;

    void Readleveling(BYTE byteData1);

};

#endif // LEVELING_H
