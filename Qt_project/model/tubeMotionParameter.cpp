#include "tubeMotionParameter.h"

/*****************************************************
类名称：MotorData
类功能：待整定
类参数：特别多
*****************************************************/
const MotorData & MotorData::operator=(const MotorData& d)
{
    if(&d == this) return *this;
    i = d.i;
    v = d.v;
    T = d.T;
    return *this;
}

/*****************************************************
类名称：tubeMotionParameter
类功能：待整定
类参数：特别多
*****************************************************/
tubeMotionParameter::tubeMotionParameter():
    time(0),
    velocityA(0), velocityB(0), velocityC(0), velocityD(0), velocityE(0), velocityF(0),
    accA(0),accB(0),accC(0), accD(0),accE(0),accF(0),
    torqueA(0),torqueB(0),torqueC(0), torqueD(0),torqueE(0),torqueF(0),
    currentA(0),currentB(0),currentC(0), currentD(0),currentE(0),currentF(0),
    enableA(false),enableB(false),enableC(false), enableD(false),enableE(false),enableF(false),
    directionA(0),directionB(0),directionC(0), directionD(0),directionE(0),directionF(0)
{}

tubeMotionParameter::tubeMotionParameter(double time,
                                         double velA, double velB, double velC, double velD, double velE, double velF,
                                         double accA, double accB, double accC, double accD, double accE, double accF,
                                         double torA, double torB, double torC, double torD, double torE, double torF,
                                         double curA, double curB, double curC, double curD, double curE, double curF,
                                         bool enA, bool enB, bool enC, bool enD, bool enE, bool enF,
                                         int dirA, int dirB, int dirC, int dirD, int dirE, int dirF):
    time(time),
    velocityA(velA), velocityB(velB), velocityC(velC), velocityD(velD), velocityE(velE), velocityF(velF),
    accA(accA),accB(accB),accC(accC), accD(accD),accE(accE),accF(accF),
    torqueA(torA), torqueB(torB), torqueC(torC), torqueD(torD), torqueE(torE), torqueF(torF),
    currentA(curA),currentB(curB),currentC(curC), currentD(curD),currentE(curE),currentF(curF),
    enableA(enA),enableB(enB),enableC(enC), enableD(enD),enableE(enE),enableF(enF),
    directionA(dirA),directionB(dirB),directionC(dirC), directionD(dirD),directionE(dirE),directionF(dirF)
{}

tubeMotionParameter::tubeMotionParameter(const tubeMotionParameter& m):
    tubeMotionParameter{m.time,
                        m.velocityA, m.velocityB, m.velocityC, m.velocityD, m.velocityE, m.velocityF,
                        m.accA, m.accB, m.accC, m.accD, m.accE, m.accF,
                        m.torqueA, m.torqueB, m.torqueC,m.torqueD, m.torqueE, m.torqueF,
                        m.currentA, m.currentB, m.currentC, m.currentD, m.currentE, m.currentF,
                        m.enableA, m.enableB, m.enableC,m.enableD, m.enableE, m.enableF,
                        m.directionA, m.directionB, m.directionC, m.directionD, m.directionE, m.directionF}
{}

///
/// \brief tubeMotionParameter::setDirection
/// \param m
/// 辅助设置方向函数
void tubeMotionParameter::setDirection(mode m)
{
    static auto setDir= [](int &dir, double &judge){
        if(judge > 1e-5)
        {
            dir = 1;
        }
        else if(judge > -1e-5)
        {
            dir =0;
        }
        else
        {
            dir = -1;
        }
    };
    if(m == velocity)
    {
        setDir(directionA, velocityA);
        setDir(directionB, velocityB);
        setDir(directionC, velocityC);
        setDir(directionD, velocityD);
        setDir(directionE, velocityE);
        setDir(directionF, velocityF);
    }
    else if(m == torque)
    {
        setDir(directionA, torqueA);
        setDir(directionB, torqueB);
        setDir(directionC, torqueC);
        setDir(directionD, torqueD);
        setDir(directionE, torqueE);
        setDir(directionF, torqueF);
    }
}

void tubeMotionParameter::setEnable(bool flag)
{
    enableA = flag;
    enableB = flag;
    enableC = flag;
    enableD = flag;
    enableE = flag;
    enableF = flag;
}

///
/// \brief tubeMotionParameter::operator =
/// \param m
/// \return
///这里不知道有没有更好的写法，加一个wrapper Function？
const tubeMotionParameter& tubeMotionParameter::operator=(const tubeMotionParameter& m)
{
    if(this == &m) return *this;
    time =  m.time;
    velocityA = m.velocityA;
    velocityB = m.velocityB;
    velocityC = m.velocityC;
    velocityD = m.velocityD;
    velocityE = m.velocityE;
    velocityF = m.velocityF;
    accA = m.accA;
    accB = m.accB;
    accC = m.accC;
    accD = m.accD;
    accE = m.accE;
    accF = m.accF;
    torqueA = m.torqueA;
    torqueB = m.torqueB;
    torqueC = m.torqueC;
    torqueD = m.torqueD;
    torqueE = m.torqueE;
    torqueF = m.torqueF;
    currentA = m.currentA;
    currentB = m.currentB;
    currentC = m.currentC;
    currentD = m.currentD;
    currentE = m.currentE;
    currentF = m.currentF;
    enableA = m.enableA;
    enableB = m.enableB;
    enableC = m.enableC;
    enableD = m.enableD;
    enableE = m.enableE;
    enableF = m.enableF;
    directionA = m.directionA;
    directionB = m.directionB;
    directionC = m.directionC;
    directionD = m.directionD;
    directionE = m.directionE;
    directionF = m.directionF;
    return *this;
}

double tubeMotionParameter::MinVel()
{
    return std::min(std::abs(velocityA),
                    std::min( std::abs(velocityB),
                              std::min( std::abs(velocityC),
                                        std::min( std::abs(velocityD),
                                                  std::min( std::abs(velocityE), std::abs(velocityF))))));
}

double tubeMotionParameter::MinVel(int i)
{
    if(i == 1)
        return std::min(std::abs(velocityA),
                    std::min( std::abs(velocityB),std::abs(velocityC)));
    if(i == 2)
        return std::min(std::abs(velocityD),
                    std::min( std::abs(velocityE),std::abs(velocityF)));
}

double tubeMotionParameter::MinAcc()
{
    return std::min(accA, std::min( accB, std::min( accC, std::min( accD, std::min( accE, accF)))));
}

double tubeMotionParameter::MaxTor()
{
    return std::max(std::abs(torqueA),
                    std::max(std::abs(torqueB),
                             std::max(std::abs(torqueC),
                                      std::max(std::abs(torqueD),
                                               std::max(std::abs(torqueE), std::abs(torqueF))))));
}

double tubeMotionParameter::MaxVel()
{
    return std::max(std::abs(velocityA),
                    std::max(std::abs(velocityB),
                             std::max(std::abs(velocityC),
                                      std::max(std::abs(velocityD),
                                               std::max(std::abs(velocityE), std::abs(velocityF))))));
}

double tubeMotionParameter::MaxVel(int i)
{
    if(i == 1)
        return std::max(std::abs(velocityA),
                    std::max( std::abs(velocityB),std::abs(velocityC)));
    if(i == 2)
        return std::max(std::abs(velocityD),
                    std::max( std::abs(velocityE),std::abs(velocityF)));
}
//Friend Function
tubeMotionParameter operator*(double a, const tubeMotionParameter& m)
{
    return {m.time,
            m.velocityA * a, m.velocityB * a, m.velocityC * a, m.velocityD * a, m.velocityE * a, m.velocityF * a,
            m.accA * a, m.accB * a, m.accC * a, m.accD * a, m.accE * a, m.accF * a,
            m.torqueA * a, m.torqueB * a, m.torqueC * a, m.torqueD * a, m.torqueE * a, m.torqueF * a,
            m.currentA * a, m.currentB * a, m.currentC * a, m.currentD * a, m.currentE * a, m.currentF * a,
            m.enableA, m.enableB, m.enableC, m.enableD, m.enableE, m.enableF,
            m.directionA, m.directionB, m.directionC, m.directionD, m.directionE, m.directionF};
}

///
/// \brief operator +
/// \param m1
/// \param m2
/// \return
/// 同Force仅保留第一个时间
/// 此类未做任何封装细节过多
tubeMotionParameter operator+(const tubeMotionParameter& m1, const tubeMotionParameter& m2)
{
    return {m1.time,
            m1.velocityA + m2.velocityA, m1.velocityB + m2.velocityB, m1.velocityC + m2.velocityC, m1.velocityD + m2.velocityD, m1.velocityE + m2.velocityE, m1.velocityF + m2.velocityF,
            m1.accA + m2.accA, m1.accB + m2.accB, m1.accC + m2.accC, m1.accD + m2.accD, m1.accE + m2.accE, m1.accF + m2.accF,
            m1.torqueA + m2.torqueA, m1.torqueB + m2.torqueB, m1.torqueC + m2.torqueC, m1.torqueD + m2.torqueD, m1.torqueE + m2.torqueE, m1.torqueF + m2.torqueF,
            m1.currentA + m2.currentA, m1.currentB + m2.currentB, m1.currentC + m2.currentC, m1.currentD + m2.currentD, m1.currentE + m2.currentE, m1.currentF + m2.currentF,
            m1.enableA, m1.enableB, m1.enableC,m1.enableD, m1.enableE, m1.enableF,
            m1.directionA, m1.directionB, m1.directionC,  m1.directionD, m1.directionE, m1.directionF};
}
