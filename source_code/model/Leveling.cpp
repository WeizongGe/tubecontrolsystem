#include "Leveling.h"

Leveling::Leveling()
{

}

void Leveling::Readleveling(BYTE byteData1)
{
    a = (byteData1 & 0x01) == 0x01? 0:1;//bit信号为1，断开,level设为0-false
    b = (byteData1 & 0x02) == 0x02? 0:1;
    c = (byteData1 & 0x04) == 0x04? 0:1;
    d = (byteData1 & 0x08) == 0x08? 0:1;
    e = (byteData1 & 0x10) == 0x10? 0:1;
    f = (byteData1 & 0x20) == 0x20? 0:1;
}
