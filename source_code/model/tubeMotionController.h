#ifndef TUBEMOTIONCONTROLLER_H
#define TUBEMOTIONCONTROLLER_H

#include <QObject>
#include <QMap>
#include <QDebug>
#include <QTimer>
#include <unordered_map>
#include <tuple>
#include <QMutex>
#include "MyLib/Filters/myinterpolation.h"
#include "model/tubeMotionParameter.h"
#include "MyLib/Filters/myFilter.h"
#include "tubeUtils.h"
#include "Force.h"
#include "motorimpulse.h"
#include "zlgcan.h"

class tubeControlSystemApp;
using namespace MyTime;


class tubeMotionController : public QObject
{
    Q_OBJECT
/// DEFINITON:
public:
    enum MotorIndex {
        //三台电机
        MOTOR_A = 0,
        MOTOR_B = 1,
        MOTOR_C = 2,
        MOTOR_D = 3,
        MOTOR_E = 4,
        MOTOR_F = 5
    };
    enum MotorStatus{
        Manual,
        Wait,
        Auto,
        Stop
    };

    Q_ENUM(MotorIndex)
private:
    struct MyMotor{
      MotorData A;
      MotorData B;
      MotorData C;
      MotorData D;
      MotorData E;
      MotorData F;
      MyMotor():A(),B(),C(),D(),E(),F(){}
    };

    enum TubeStatus{
        Zero = 0,
        One  = 1,
        Tow  = 2,
        Three= 3,
        Four = 4,
        Five = 5
    };

/// STATIC CONSTANT
public:
    /// CAN_COMMAND
    constexpr static const uint16_t SDOServerID = 0x601;
    constexpr static const uint32_t StopCommand = 0x006;
    constexpr static const uint32_t StartCommand = 0x00F;
    constexpr static const uint8_t LENGTH_8 = 0x2B;
    constexpr static const uint8_t LENGTH_16  = 0x23;
    constexpr static const uint16_t VelMode = 0x03;
    constexpr static const uint16_t TorMode = 0x0A;

    /// 速度比率
    constexpr static float MOTOR_VEL_RATIO = 411 / 3.1415926 /33 * 60;
    constexpr static float MOTOR_RATIO = 411 / 3.1415926 / 33;
    constexpr static float FORCE_RATIO = 1000.0 / ( 411.0 * 33.8 / 1000 / 0.0165 );
    constexpr static float CURRENT_RATIO = 1000.0 / 1.49;
    constexpr static float eta = 0.6;
    /// MAP_USING
    std::unordered_map<uint32_t, QString> modeString =
    {
        {VelMode, "速度模式"}, {TorMode, "力矩模式"}
    };

    std::unordered_map<MotorStatus, QString> motorStatusString =
    {
        {Manual, "手动模式"}, {Auto, "自动模式"}
    };
/// FILEDS
public:
    //指示灯
    // Interface for Private readOnly:
    CHANNEL_HANDLE CH(){return chHandle0;}
    bool STARTED(){ return DEVICE_START;}
    bool CAN_STARTED(){ return CAN_START;}

    // Interface for Write
    void changeCanStatus(bool flag = true){CAN_START = flag;}
    void changeStartStatus(bool flag = true){DEVICE_START = flag;}

    MotorStatus status;//为了力矩模式手动停止，改为public

private:
    using vd_1 = std::vector<double>;
    using vd_2 = std::vector<std::vector<double>>;
    // 计时器   Warpper Class
    Timer myTimer;
    Timer globalTimer;
    // 方法算法 Template Class
    CubicInter<double> inter;
    lowPassFilter<tubeMotionParameter> filter;

    tubeControlSystemApp *m_app;

    bool CAN_START = false;
    bool DEVICE_START = false;
    bool simpleFlag = true;

    DEVICE_HANDLE m_dhandle0;
    CHANNEL_HANDLE chHandle0;       //设置can0通道句柄
    ZCAN_CHANNEL_INIT_CONFIG cfg0;

    MotorImpulse impulse;
    tubeMotionParameter cur_Para;
    tubeMotionParameter pre_Para;
    uint16_t m_tubestate;

    MyMotor motor;
    MotorData motorA_Read;
    MotorData motorB_Read;
    MotorData motorC_Read;
    MotorData motorD_Read;
    MotorData motorE_Read;
    MotorData motorF_Read;

    Direction dirFlag = Direction::forward;
    double reachedX = 0;
    int16_t torqueLowerBound = 50;
    int16_t desireTorque = 0;
    std::vector<int16_t> desireTorques = std::vector(6, static_cast<int16_t>(0));
    std::vector<int16_t> desireTorques_ = std::vector(6, static_cast<int16_t>(0));
    std::vector<int16_t> _desireTorques = std::vector(6, static_cast<int16_t>(200));
    double vel_LowerBound = 1000;
    double vel_HigherBound = 2378;
    double vel_HighFlag = 9;
    double vel_UpperBound = 0;        //全运行阶段最大速度上限
    std::vector<uint32_t> vel_UpperBound_V = {100,100,100,100,100,100};
    int16_t cst_torHigherBound_A = 0;
    int16_t acc_torHigherBound_A = 0;
    int16_t cst_torHigherBound_E = 0;
    int16_t acc_torHigherBound_E = 0;

    int16_t incTor = 5;
    double incVel = 50;
    Force force{};
    double delta_t = 0.01;
    bool tube_dep_flag1 = true;
    bool tube_dep_flag2 = true;
    std::vector<int> deltaV = {0,0,0,0,0,0};
    bool Optflag = false;
    bool ABCFlag = false;
    bool DEFFlag = false;

//    MotorStatus status;
    TubeStatus tubeStatus = Zero;
    std::unordered_map<MotorStatus, std::function<void (void)>> WriteFun;

/// MEMBERFUNCTION:
public:
    /// Constructor:
    explicit tubeMotionController(QObject *parent = nullptr);

    /// Destructor:
    ~tubeMotionController(){}

    /// Nomoal:
    bool init();
    void Stopdrivers();
    void restartdrivers();
    void setMotionMode(uint32_t mode);
    void set_entry(uint transCANID, uint8_t cs, uint16_t index, uint8_t subindex, uint32_t default_value);
    void ReceivemotorData();
    void PVmodeSetVel(qreal velA, qreal velB, qreal velC, qreal velD, qreal velE, qreal velF);

    void CSTmodeSetVel(qreal vel);
    void CSTmodeSetTor(qreal torA, qreal torB, qreal torC, qreal torD, qreal torE, qreal torF);

    void CSTmodeHold();
private:
    /// Normal

    void PVmodeSetVel(qreal vel);
    void CSTmodeSetTor(qreal tor);
    void LogMode();
    bool ch0_init();
    void driver_init();

    void DataProcess();

    void Enable();
    void CSTmodeStart();
    void CSTmodeWait();
    void CSTmodeManual();
    void CSTmodeAuto();
    void CSTmodeStop();

    void AutoOptimizer(bool flag, int id);
    void MinOptimizer(bool flag, int i, int16_t acc_torHigherBound);
    void MaxOptimizer(bool flag, int id, int16_t cst_torHigherBound);

    template<typename T>
    void CSTmodeWriteTorque(T val);
    template<typename T>
    void CSTmodeWriteTorque(std::vector<T> vals);

    void CSTmodeWriteVelLimit(uint32_t val);
    void CSTmodeWriteVelLimit(std::vector<uint32_t> val);

    bool CheckTube(){ static TubeStatus oriTubeStatus = tubeStatus;
                      bool rFlag = (oriTubeStatus == tubeStatus);
                      oriTubeStatus = tubeStatus;
                      return rFlag;
                    }
    bool CheckVal(){ return CheckVel() || CheckAcc();}
    bool CheckVel(){ return cur_Para.MinVel() >= 5e-1;}
    bool CheckAcc(){ return cur_Para.MinAcc() >= 5e-1;}
    bool CheckTor(){ return force.MaxVal() > 1800 ||
                    (force.MaxVal() > 500 && force.MinVal() <5e-1);}
    uint32_t ReadDataProcess(BYTE * data, int n);

/// SLOTS:
public slots:
    void ReceiveTimer(const Timer & t){globalTimer = t;};
    void readParameter();
    void Receivedhandle(DEVICE_HANDLE & dhandle);
    void ReceiveForce(Force ft);
    void SetSimple(bool flag);
    void SetImpulseZero();
    void SetAutoParameter(std::vector<double> v);
    void SetDirFlag(Direction dir);
    void OverDevProtect(std::vector<int> delta, bool flag);
    void GetStopFlag(bool flag1, bool flag2);
    void StopAutoStatus();
    void GetABCFlag(bool flag);
    void GetDEFFlag(bool flag);

/// SIGNALS:
signals:
    void tubemotionParameterUpdated(tubeMotionParameter mp);
    void PassX(double x);
    void passReceive(ZCAN_Receive_Data data);
    void ForceRequest(bool flag);
    void Logger(const QString & msg);
    void RequestLockSliders(bool flag);
    void SendDirection(Direction dir);

};

#endif // MOTIONCONTROLLER_H
