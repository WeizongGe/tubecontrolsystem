#ifndef TUBEMOTIONPARAMETER_H
#define TUBEMOTIONPARAMETER_H

#include<QtMath>

namespace MOTOR {
    constexpr const double ALPHA = 0.1;
}

enum class Direction{
    forward = 1,
    backward = -1,
    stop = 0
};

struct MotorData
{
// FIELDS:
    uint32_t i;
    int32_t v;
    int16_t T;

// CONSTRUCTOR:
    MotorData():
        MotorData{0, 0, 0} {}
    MotorData(double ii, double iv, double iT):
        i(ii), v(iv), T(iT) {}

// MEMBERFUNCTION:
    const MotorData& operator=(const MotorData& d);
};

// TODO:
//      用TubeData代替原先tubeMotionParameter
//      的参数，重构整个数据用法
struct TubeData
{
    enum Dir{
        forward = 1,
        stop = 0,
        backward= -1
    };
    double v;
    double acc;
    double current;
    bool enable;
    Dir direction;

    TubeData(double iv, double iacc, double icur, bool en, Dir d):
        v(iv), acc(iacc), current(icur), enable(en), direction(stop){}
};

///
/// \brief The TubeMotion class
/// 待完善部分待重构
class TubeMotion{
/// Fields:
public:
    double time;
    TubeData A;
    TubeData B;
    TubeData C;
    TubeData D;
    TubeData E;
    TubeData F;
};

class tubeMotionParameter
{
public:
    enum mode{
        velocity,
        torque
    };
    double time;
    double velocityA;
    double velocityB;
    double velocityC;
    double velocityD;
    double velocityE;
    double velocityF;
    double accA;
    double accB;
    double accC;
    double accD;
    double accE;
    double accF;
    double torqueA;
    double torqueB;
    double torqueC;
    double torqueD;
    double torqueE;
    double torqueF;
    double currentA;
    double currentB;
    double currentC;
    double currentD;
    double currentE;
    double currentF;

    bool enableA;
    bool enableB;
    bool enableC;
    bool enableD;
    bool enableE;
    bool enableF;

    int directionA;
    int directionB;
    int directionC;
    int directionD;
    int directionE;
    int directionF;
/// MEMBERFUNCTION:
public:
    tubeMotionParameter();
    ~tubeMotionParameter(){}
    tubeMotionParameter(const tubeMotionParameter& m);
    tubeMotionParameter(double time,
                        double velA, double velB, double velC, double velD, double velE, double velF,
                        double accA, double accB, double accC, double accD, double accE, double accF,
                        double torA, double torB, double torC, double torD, double torE, double torF,
                        double curA, double curB, double curC, double curD, double curE, double curF,
                        bool enA, bool enB, bool enC, bool enD, bool enE, bool enF,
                        int dirA, int dirB, int dirC, int dirD, int dirE, int dirF);
    void setDirection(mode);
    void setEnable(bool flag);

    double MinVel();
    double MinVel(int i);
    double MinAcc();
    double MaxTor();
    double MaxVel();
    double MaxVel(int i);

    const tubeMotionParameter& operator=(const tubeMotionParameter& m);
    friend tubeMotionParameter operator*(double a, const tubeMotionParameter& m);
    friend tubeMotionParameter operator+(const tubeMotionParameter& m1, const tubeMotionParameter& m2);
};

#endif // TUBEMOTIONPARAMETER_H
