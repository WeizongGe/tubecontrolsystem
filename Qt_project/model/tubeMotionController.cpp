#include "model\tubeMotionController.h"
#include "model\tubeControlSystemApp.h"
#include "model\tubeUtils.h"

#include <synchapi.h>
#include <QDebug>
#include <QMetaEnum>
#include<QMetaType>
#include <string.h>


tubeMotionController::tubeMotionController(QObject *parent) :
//  Qt Ui
    QObject(parent),
//  Timer
    myTimer(),
//  Function
    inter(), filter(MOTOR::ALPHA),
    m_app(tubeControlSystemApp::instance()),
//  Can Handle
    m_dhandle0(nullptr), chHandle0(nullptr),
//  Send Data Tube
    cur_Para(), pre_Para(),
//  Read Data Motor
    motor()
{
    // for custom DataStructure as Signal parameters
    qRegisterMetaType<tubeMotionParameter>("tubeMotionParameter");
    qRegisterMetaType<tubeMotionParameter*>("tubeMotionParameter*");
    qRegisterMetaType<ZCAN_Receive_Data*>("ZCAN_Receive_Data");

    // Function Map Initialization
    WriteFun = {
        {Manual, [this](){CSTmodeManual();}},
        {Auto,   [this](){CSTmodeAuto();}},
        {Wait,   [this](){CSTmodeWait();}},
        {Stop,   [this](){CSTmodeStop();}}
    };

}

bool tubeMotionController::init()
{
    // TODO: 把这里返回值写清楚
    if(ch0_init())
    {
       driver_init();
       Sleep(100);
       return true;
    }
    return false;
}

//cfg0 删除完全没用仅在该函数中使用，用cfg替代
bool tubeMotionController::ch0_init()
{
    memset(&cfg0, 0, sizeof(cfg0));
    cfg0.can_type = TYPE_CAN;
    cfg0.can.filter = 0;
    cfg0.can.mode = 0;                   //正常模式, 1为只听模式
    cfg0.can.acc_code = 0;
    cfg0.can.acc_mask = 0xffffffff;
    chHandle0 = ZCAN_InitCAN(m_dhandle0, 0, &cfg0);
    if (INVALID_CHANNEL_HANDLE == chHandle0)
    {
        qDebug("FAILED::CHANNEL:INITIALZE");
        qDebug("LOCATION::TUBE::MOTION::CONTROLLER::CH0::INIT");
        QMessageBox::information(NULL, QStringLiteral("初始化通道失败"), QStringLiteral("通道指针为空指针"));
        ZCAN_ClearBuffer(chHandle0);      //清空缓冲区
        ZCAN_ResetCAN(chHandle0);         //通道复位
        return false;
    }
    if (ZCAN_StartCAN(chHandle0) != STATUS_OK)
    {
        qDebug() << "启动通道失败" ;
        QMessageBox::information(NULL, QStringLiteral("启动通道0失败"), QStringLiteral("请检查通道0连接"));
        ZCAN_ClearBuffer(chHandle0);      //清空缓冲区
        ZCAN_ResetCAN(chHandle0);         //通道复位
        return false;
    }
    return true;
}


void tubeMotionController::driver_init()
{
#ifdef _DEBUG
    emit Logger("调用者Driver_init:");
#endif
    QMetaEnum e = QMetaEnum::fromType<MotorIndex>();
    for (int i = 0; i < e.keyCount(); i++)
    {
        // 0x1800: index of "TPDO1 参数索引"
        // 0x1A00: index of "TPDO1 匹配索引"
        set_entry(0x601 + i, 0x2F, 0x6060, 0x00, (int32_t)0x0003); //设置运行模式
        Sleep(100);
        set_entry(0x601 + i, 0x2B, 0x6040, 0x00, (int32_t)0x0006); //全部电机去使能
        Sleep(100);
        set_entry(0x601 + i, 0x2B, 0x6040, 0x00, (int32_t)0x000F);  //全部电机为使能状态
        Sleep(100);
        //Sleep(100);
    }
    cur_Para.setEnable(true);
}


/****************************************************************
                    The Main Loop


*****************************************************************/
void tubeMotionController::readParameter()
{
#ifdef _DEBUG
    emit Logger("调用者：ReadParameter：");
#endif

    set_entry(0, 0x01, 0, 0, 0);
    emit ForceRequest(true);
    while(DEVICE_START)
    {

        set_entry(0x80, 0, 0, 0, 0);
        Sleep(10);
        // 读数据
        ReceivemotorData();
        // 数据处理
        DataProcess();
//        tubeStateChange();
        // 数据检查
        if(CheckTor())
        {
            //做松绳操作
            CSTmodeWriteVelLimit(0);
            CSTmodeWriteTorque(0);
            Enable();

        }

        // 写数据使用Function Map 进行函数匹配
        // 实现有限状态机
        WriteFun[status]();

        emit tubemotionParameterUpdated(cur_Para);
//        emit PassX(reachedX);
    }
    set_entry(0, 0x81, 0, 0, 0);
    emit ForceRequest(false);
}

void tubeMotionController::PVmodeSetVel(qreal velA, qreal velB, qreal velC, qreal velD, qreal velE, qreal velF)
{
#ifdef _DEBUG
    emit Logger("调用者PVmodeSetVel：");
#endif
    int32_t vel[6] ={(int32_t) velA,  //电机A期望速度
                     (int32_t) velB,  //电机B期望速度
                     (int32_t) velC,  //电机C期望速度
                     (int32_t) velD,
                     (int32_t) velE,
                     (int32_t) velF};
    for(auto & v:vel)
    {
        v *= static_cast<int>(dirFlag);
    }
    for (int i = 0; i < 6; i++)
    {
        set_entry(0x601+i, 0x23, 0x6080, 0x00, (uint32_t)vel[i]);
        set_entry(0x601+i, 0x23, 0x607F, 0x00, (uint32_t)vel[i]);
        set_entry(0x601+i, 0x23, 0x60FF, 0x00, (uint32_t)vel[i]); //设置目标速度
    }
//  注：底层函数不要改动，先找到调用的位置，有相应的函数接口。
//   if(motionflag1 && motionflag2){
//        for (int i = 0; i < 6; i++)
//        {
//            set_entry(0x601+i, 0x23, 0x6080, 0x00, (uint32_t)vel[i]);
//            set_entry(0x601+i, 0x23, 0x607F, 0x00, (uint32_t)vel[i]);
//            set_entry(0x601+i, 0x23, 0x60FF, 0x00, (uint32_t)vel[i]); //设置目标速度}}
//    else if(motionflag1 && !motionflag2){
//        for (int i = 0; i < 3; i++)
//        {
//            set_entry(0x601+i, 0x23, 0x6080, 0x00, (uint32_t)vel[i]);
//            set_entry(0x601+i, 0x23, 0x607F, 0x00, (uint32_t)vel[i]);
//            set_entry(0x601+i, 0x23, 0x60FF, 0x00, (uint32_t)vel[i]); //设置目标速度}}
//    else if(!motionflag1 && motionflag2){
//        for (int i = 3; i < 6; i++)
//        {
//            set_entry(0x601+i, 0x23, 0x6080, 0x00, (uint32_t)vel[i]);
//            set_entry(0x601+i, 0x23, 0x607F, 0x00, (uint32_t)vel[i]);
//            set_entry(0x601+i, 0x23, 0x60FF, 0x00, (uint32_t)vel[i]); //设置目标速度}}
//    else{
//        emit Logger("请选择电机组");}
    Enable();
}

void tubeMotionController::PVmodeSetVel(qreal vel)
{
#ifdef _DEBUG
    emit Logger("调用者PVmodeSetVel：{double}：");
#endif
    PVmodeSetVel(vel, vel, vel, vel, vel, vel);
}

void tubeMotionController::CSTmodeSetTor(qreal torA, qreal torB, qreal torC, qreal torD, qreal torE, qreal torF)
{
#ifdef _DEBUG
    emit Logger("调用者PVmodeSetTor：");
#endif
    // 赋值
    desireTorques = {static_cast<int16_t>(torA),
                     static_cast<int16_t>(torB),
                     static_cast<int16_t>(torC),
                     static_cast<int16_t>(torD),
                     static_cast<int16_t>(torE),
                     static_cast<int16_t>(torF)};
    for(auto & t:desireTorques)
    {
        t *= static_cast<int>(dirFlag);
    }
    desireTorque = (torA + torB + torC + torD + torE + torF)/6.0;
    CSTmodeStart();
}

void tubeMotionController::CSTmodeSetTor(qreal tor)
{
#ifdef _DEBUG
    emit Logger("调用者PVmodeSetTor：{double}");
#endif
    CSTmodeSetTor(tor, tor, tor, tor, tor, tor);
}

void tubeMotionController::CSTmodeSetVel(qreal vel)
{
    vel_UpperBound = vel;
}

void tubeMotionController::Receivedhandle(DEVICE_HANDLE & dhandle)
{
    m_dhandle0 = dhandle;
    if (INVALID_DEVICE_HANDLE == m_dhandle0)
    {
        qDebug( "设备句柄传递失败" );
        QMessageBox::information(NULL, QStringLiteral("设备句柄传递失败"), QStringLiteral("请检查发送ID"),
                             QMessageBox::Yes | QMessageBox::No, QMessageBox::Yes);
        return;
    }
}


///
/// \brief tubeMotionController::mapTpdo
/// \param parameterOffset
/// \param mappingOffset
/// \param CANID
/// \param T_COBID
/// \details 用于can传输sdo的原辅助函数，
///          暂保留
void tubeMotionController::mapTpdo(uint16_t parameterOffset, uint16_t mappingOffset,uint CANID, uint T_COBID)
{
    set_entry(CANID, 0x2F, parameterOffset, 0x0, 0x0);   // pdo should be disable before mapping

    set_entry(CANID, 0x2F, mappingOffset, 0x0, 0x0);     // number of entries should set to 0 before mapping

    uint32_t mapInfo = 0;                                       // 操作数初始化为0
    mapInfo |= 32;                                              // 输入参数位数（bit）: 32 bits
    mapInfo |= 0x606C << 16;                                    // 输入参数的对象字典：实际转速值
    set_entry(CANID, 0x23, mappingOffset, 0x1, mapInfo);        // 匹配操作

    mapInfo = 0;
    mapInfo |= 16;                                              // 输入参数位数（bit）: 16 bits
    mapInfo |= 0x6077 << 16;                                    // 输入参数的对象字典：实际扭矩值
    set_entry(CANID, 0x23, mappingOffset, 0x1, mapInfo);        // 匹配操作

    set_entry(CANID, 0x23, mappingOffset, 0x1, mapInfo);        // 匹配操作

    set_entry(CANID, 0x2F, mappingOffset, 0x0, 0x2);            // 2 entries
    set_entry(CANID, 0x2F, parameterOffset, 0x1, T_COBID);          // enable pdo
    set_entry(CANID, 0x2F, parameterOffset, 0x2, 0x1);          // send every 1 SYNC
}

void tubeMotionController::Enable()
{
#ifdef _DEBUG
    emit Logger("调用者Enable：状态 "+QString::number(status));
#endif
    constexpr static const uint16_t INDEX = 0x6040;
    constexpr static const uint8_t SUB_INDEX= 0x00;
    for(int i = 0; i < 6; ++i)
    {
        set_entry(SDOServerID + i,
                  LENGTH_8,
                  INDEX,
                  SUB_INDEX,
                  StartCommand);
    }
}


/// \brief   tubeMotionController::restartdrivers
/// \details 电机重启的函数，关键在向604000发送06和0F
/// \param   Index      + subindex：
///          {uint16_t} + {uint8_t}
///          Size: 6Byte
///          Exp:  {0x6040} + {0x00}
///                0x604000 实际数据格式0x406000
/// \param   Data:
///          {uint32_t}
///          Exp:
///              0x6  --电机去使能
///              0xF  --电机使能
void tubeMotionController::restartdrivers()
{
#ifdef _DEBUG
    emit Logger("调用者restartDrivers:");
#endif
    QMetaEnum e = QMetaEnum::fromType<MotorIndex>();
    for (int i=0; i<e.keyCount(); i++)
    {
         set_entry(0x601+i, 0x2B, 0x6040, 0x00, (int32_t)0x0006); //全部电机去使能
         Sleep(50);
         set_entry(0x601+i, 0x2B, 0x6040, 0x00, (int32_t)0x000F); //模式设置完成后点击->全部电机运行
         Sleep(50);
    }
    Sleep(100);
    cur_Para.setEnable(true);
    status = Wait;
}

void tubeMotionController::Stopdrivers()
{
#ifdef _DEBUG
    emit Logger("调用者StopDrivers:");
#endif
    QMetaEnum e = QMetaEnum::fromType<MotorIndex>();  
    for (int i=0; i<e.keyCount(); i++)
     {
         set_entry(0x601+i, 0x2B, 0x6040, 0x00, (int32_t)0x0006); //全部电机去使能
         //Sleep(30);
     }

    Sleep(100);
    cur_Para.setEnable(false);
    status = Wait;
}

void tubeMotionController::setMotionMode(uint32_t mode)
{
#ifdef _DEBUG
    emit Logger("调用者SetMotionMode:");
#endif
    emit Logger("模式已改变：\n 现在模式为" + modeString[mode]);
    QMetaEnum e = QMetaEnum::fromType<MotorIndex>();
    for (int i=0; i<e.keyCount(); i++)
     {
         set_entry(0x601+i, 0x2F, 0x6060, 0x00, (int32_t)mode); //设置运行模式
     }
}

///
/// \brief tubeMotionController::DataProcess
/// 数据处理函数把MotorData 转为 Parameters
void tubeMotionController::DataProcess()
{
    cur_Para.time = globalTimer.nowTime();// m_app->base_time;
    delta_t = cur_Para.time - pre_Para.time;

    // TODO:
    //      使用新的结构体简化代码，细节过多
    cur_Para.velocityA = (double)motorA_Read.v/MOTOR_VEL_RATIO;      //单位：rpm
    cur_Para.torqueA = (double)motorA_Read.T/FORCE_RATIO * eta;                 //单位：mNm转Nm

    cur_Para.currentA = (double)motorA_Read.T / CURRENT_RATIO;     //单位：A，24.3mNm/A(电机常数)
    cur_Para.accA = (cur_Para.velocityA-pre_Para.velocityA)/delta_t;

    cur_Para.velocityB = (double)motorB_Read.v/MOTOR_VEL_RATIO;           //单位：rpm
    cur_Para.torqueB = (double)motorB_Read.T/FORCE_RATIO * eta;                     //单位：mNm转Nm

    cur_Para.currentB = (double)motorB_Read.T / CURRENT_RATIO;                 //单位：A，24.3mNm/A(电机常数)
    cur_Para.accB = (cur_Para.velocityB-pre_Para.velocityB)/delta_t;

    cur_Para.velocityC = (double)motorC_Read.v/MOTOR_VEL_RATIO;           //单位：rpm
    cur_Para.torqueC = (double)motorC_Read.T/FORCE_RATIO * eta;                     //单位：mNm转Nm

    cur_Para.currentC = motorC_Read.T / CURRENT_RATIO;                         //单位：A，24.3mNm/A(电机常数)
    cur_Para.accC = (cur_Para.velocityC-pre_Para.velocityC)/delta_t;

    cur_Para.velocityD = (double)motorD_Read.v/MOTOR_VEL_RATIO;      //单位：rpm
    cur_Para.torqueD = (double)motorD_Read.T/FORCE_RATIO * eta;                 //单位：mNm转Nm

    cur_Para.currentD = (double)motorD_Read.T / CURRENT_RATIO;     //单位：A，24.3mNm/A(电机常数)
    cur_Para.accD = (cur_Para.velocityD-pre_Para.velocityD)/delta_t;

    cur_Para.velocityE = (double)motorE_Read.v/MOTOR_VEL_RATIO;      //单位：rpm
    cur_Para.torqueE = (double)motorE_Read.T/FORCE_RATIO * eta;                 //单位：mNm转Nm

    cur_Para.currentE = (double)motorE_Read.T / CURRENT_RATIO;     //单位：A，24.3mNm/A(电机常数)
    cur_Para.accE = (cur_Para.velocityE-pre_Para.velocityE)/delta_t;

    cur_Para.velocityF = (double)motorF_Read.v/MOTOR_VEL_RATIO;      //单位：rpm
    cur_Para.torqueF = (double)motorF_Read.T/FORCE_RATIO * eta;                 //单位：mNm转Nm

    cur_Para.currentF = (double)motorF_Read.T / CURRENT_RATIO;     //单位：A，24.3mNm/A(电机常数)
    cur_Para.accF = (cur_Para.velocityF-pre_Para.velocityF)/delta_t;

    cur_Para.setDirection(tubeMotionParameter::mode::velocity);

    // 处理增量数据
    impulse.a = motorA_Read.i;
    impulse.b = motorB_Read.i;
    impulse.c = motorC_Read.i;
    impulse.d = motorD_Read.i;
    impulse.e = motorE_Read.i;
    impulse.f = motorF_Read.i;

    // low Pass Filter
    cur_Para = filter(cur_Para, pre_Para);
    pre_Para = cur_Para;
    reachedX += cur_Para.MinVel() * delta_t;
    //reachedX += 10000 * (getCurrentTime() - zeroTime);
}

void tubeMotionController::tubeStateChange()
{
//    if(tubeStatus!= Four
//       &&
//       impulse.toLength(1.0/MOTOR_RATIO/4096.0) - 3.0 * tubeStatus > 2.5)
//    {
//       tubeStatus = (TubeStatus)(static_cast<int>(tubeStatus) + 1);
//       emit Logger("状态已切换：\n当前套筒状态为" + QString::number(tubeStatus));
//    }
}

/*****************************************************************
 *                            CSTMode
 *
 *
 *
 * **************************************************************/
void tubeMotionController::CSTmodeStart()
{
    auto static MinVal = [](auto & nums){
        auto minval = INT_MAX;
        for(auto & n : nums)
        {
            minval = std::min(std::abs(n), minval);
        }
        return minval;
    };
    auto static MaxVal = [](auto & nums){
        auto maxval = 0;
        for(auto & n: nums)
        {
            maxval = std::max(std::abs(n), maxval);
        }
        return maxval;
    };
    if(status == Wait)
    {
        if(simpleFlag || MinVal(desireTorques) == 0)
        {
            emit RequestLockSliders(false);
            status = Manual;
        }
        else
        {
            emit RequestLockSliders(true);
            status = Auto;
        }
    }
}

void tubeMotionController::CSTmodeManual()
{
    CSTmodeWriteTorque(desireTorques);
    CSTmodeWriteVelLimit(vel_UpperBound);
    Enable();
    status = Wait;
}

void tubeMotionController::CSTmodeWait()
{
    Sleep(10);
}

void tubeMotionController::CSTmodeStop()
{
    CSTmodeWriteVelLimit(0);
    CSTmodeWriteTorque(0);
    Enable();
}

void tubeMotionController::AutoOptimizer(bool flag, int id)
{
    std::vector<int> ls = {0,0,0};
    switch(id)
    {
    case 1:  ls = {0,1,2};
    case 2:  ls = {3,4,5};
    }
    if(flag){
        for(auto i : ls){
            switch(deltaV[i]){
            case -1:    desireTorques[i] -= incTor; vel_UpperBound -= incVel/2;
                        vel_UpperBound  = (vel_UpperBound < vel_LowerBound?
                                            vel_LowerBound : vel_UpperBound);
            case 1:     desireTorques[i] += incTor; vel_UpperBound -= incVel/2;
                        vel_UpperBound  = (vel_UpperBound < vel_LowerBound?
                                            vel_LowerBound : vel_UpperBound);
            case 0:     vel_UpperBound += incVel;
                        vel_UpperBound  = (vel_UpperBound>8000?8000:vel_UpperBound);
            }}}
}

void tubeMotionController::MinOptimizer(bool flag, int id)
{
    std::vector<int> ls = {0,0,0};
    switch(id)
    {
    case 1:  ls = {0,1,2};
    case 2:  ls = {3,4,5};
    }
    if(cur_Para.MinVel(id) <= 5e-1 && flag)
    {
        for(auto i : ls)
        {
            desireTorques[i] += incTor;
            desireTorques[i]  = (desireTorques[i] > 1000? 1000 :desireTorques[i]);
        }
        vel_UpperBound -= incVel;
        vel_UpperBound  = (vel_UpperBound < vel_LowerBound?
                               vel_LowerBound : vel_UpperBound);
    }
}

void tubeMotionController::MaxOptimizer(bool flag, int id)
{
    std::vector<int> ls = {0,0,0};
    switch(id)
    {
    case 1:  ls = {0,1,2};
    case 2:  ls = {3,4,5};
    }
    if(cur_Para.MinVel() > 5e-1 &&cur_Para.MaxVel(id) <= 7 && flag)
    {
        for(auto i : ls)
        {
            desireTorques[i] -= incTor;
            desireTorques[i]  = (desireTorques[i] < torqueLowerBound?
                      torqueLowerBound:desireTorques[i]);
        }
        vel_UpperBound += incVel;
        vel_UpperBound  = (vel_UpperBound>8000?8000:vel_UpperBound);
    }
}
// TODO:
void tubeMotionController::CSTmodeAuto()
{
    AutoOptimizer(tube_dep_flag1, 1);
    AutoOptimizer(tube_dep_flag2, 2);
    MinOptimizer(tube_dep_flag1, 1);
    MinOptimizer(tube_dep_flag2, 2);
    MaxOptimizer(tube_dep_flag1, 1);
    MaxOptimizer(tube_dep_flag2, 2);
//    if(cur_Para.MinVel() <= 5e-1 && tube_dep_flag1)
//    {
//        for(auto & t:desireTorques)
//        {
//            t += incTor;
//            t  = (t > 1000? 1000 :t);
//        }
//        vel_UpperBound -= incVel;
//        vel_UpperBound  = (vel_UpperBound < vel_LowerBound?
//                               vel_LowerBound : vel_UpperBound);
//    }
//    else if(cur_Para.MinVel() > 5e-1 && cur_Para.MaxVel() <= 7 && tube_dep_flag1)
//    {
//        for(auto & t:desireTorques)
//        {
//            t -= incTor;
//            t  = (t < torqueLowerBound?
//                      torqueLowerBound:t);
//        }
//        vel_UpperBound += incVel;
//        vel_UpperBound  = (vel_UpperBound>8000?8000:vel_UpperBound);
//    }
    if(!tube_dep_flag1 && !tube_dep_flag2)
    {
        status = Stop;
    }
    CSTmodeWriteVelLimit(vel_UpperBound);
    CSTmodeWriteTorque(desireTorques);
    Enable();
}

template <typename T>
void tubeMotionController::CSTmodeWriteTorque(T val)
{
    CSTmodeWriteTorque(std::vector<T>{val, val, val, val, val, val});
}

template <typename T>
void tubeMotionController::CSTmodeWriteTorque(std::vector<T> vals)
{
    constexpr static const uint8_t LENGTH = 0x2B;
    constexpr static const uint16_t TOR_SET_INDEX = 0x6071;
    constexpr static const uint8_t TOR_SET_SUBINDEX = 0x00;
    for(auto & val: vals)
    {
        val *= static_cast<int>(dirFlag);
    }
    for(int i = 0; i < 6; ++i)
    {
        set_entry(0x601+i,                          // SDO字典id
                  LENGTH,                           // 数据写长度
                  TOR_SET_INDEX, TOR_SET_SUBINDEX,  // index + subindex
        (uint32_t)vals[i]);                             // 数据力矩值
    }
}

void tubeMotionController::CSTmodeWriteVelLimit(uint32_t val)
{
    constexpr static const uint8_t LENGTH = 0x23;
    constexpr static const uint16_t VEL_LIMIT_SET_INDEX = 0x6080;
    constexpr static const uint8_t VEL_LIMIT_SET_SUBINDEX = 0x00;

    val *= static_cast<int>(dirFlag);

    for(int i = 0; i < 6; ++i)
    {
        set_entry(SDOServerID+i,                          // SDO字典id
                  LENGTH,                           // 数据写长度
                  VEL_LIMIT_SET_INDEX,              // index
                  VEL_LIMIT_SET_SUBINDEX,           // subindex
        (uint32_t)val);                             // 数据力矩值
    }
}


/*******************************************************************
                        Helper Function


********************************************************************/
void tubeMotionController::LogMode()
{
    emit Logger("模式已切换，现在模式为：\n" + motorStatusString[status]);
}

void tubeMotionController::set_entry(uint transCANID, uint8_t cs, uint16_t index, uint8_t subindex, uint32_t default_value)
{
    /*
     * transCANID 为COBID；
     * index 为索引（命令字典）；
     * subindex 为子索引（命令字典中的功能）；
     * default_value 为数据或操作内容；
     * cs 为sdo模式的命令字：
     *  0x22表示不指定数据长度；
     *  0x23表示帧数据中8个字节全部有效，有效数据32位；
     *  0x27表示数据中7个字节数据有效，有效数据24位；
     *  0x2B表示数据中6个字节数据有效，有效数据16位；
     *  0x2F表示数据中5个字节数据有效，有效数据8位；
     */
    ZCAN_Transmit_Data m_Message;
    memset(&m_Message, 0, sizeof(m_Message));
    m_Message.frame.can_id = MAKE_CAN_ID(transCANID, 0, 0, 0);
    m_Message.frame.can_dlc = CAN_MAX_DLEN;
    uint8_t index_temph= index >> 8;
    uint8_t index_tempL= index;
    m_Message.frame.data[0] =cs;
    m_Message.frame.data[1] =index_tempL;
    m_Message.frame.data[2] =index_temph;
    m_Message.frame.data[3] =subindex;
    for (int i = 4; i < CAN_MAX_DLEN ; i++)
    {
        m_Message.frame.data[i] = default_value >> (8 * (i - 4));
    }

    QString msg = "传输目标：" + QString::number(transCANID,16) +"\n";
    if (ZCAN_Transmit(chHandle0, &m_Message, 1) <= 0)
    {
        emit Logger("指令发送失败！");
        msg += "传输失败，失败代码为：0x";
    }
    else
    {
        msg += "传输成功，成功代码为：0x";
    }
#ifdef _DEBUG
    for(auto & d: m_Message.frame.data)
    {
        msg+= QString::number(d, 16);
    }
    if(transCANID != 0x80)
        emit Logger(msg);
#endif
}

void tubeMotionController::ReceivemotorData()
{
    ZCAN_Receive_Data can_rframeinfo[50];//电机驱动can通道接收结构体

    if (ZCAN_GetReceiveNum(chHandle0, TYPE_CAN))
    {
        uint len = ZCAN_Receive(chHandle0, can_rframeinfo, 50, 100);//ZCAN_Receive(CAN通道句柄，接收信息结构体，每一次接收个数50，等待时间ms)函数接收数据。
        long long flag = 0x111111111111;
        for(uint i = 0; i < len && flag != 0 ; i++)
        {
            uint id = GET_ID(can_rframeinfo[i].frame.can_id);
            if(IS_RTR (can_rframeinfo[i].frame.can_id) == 0)//如果是数据帧，获取数据帧里面的数据
            {
                switch (id) {
                case 0x181:
                    motorA_Read.v = (int32_t)ReadDataProcess(&can_rframeinfo[i].frame.data[0], 4);
                    motorA_Read.T = (int32_t)ReadDataProcess(&can_rframeinfo[i].frame.data[4], 2);
                    flag &= 0x111111111110;
                    break;
                case 0x182:
                    motorB_Read.v = (int32_t)ReadDataProcess(&can_rframeinfo[i].frame.data[0], 4);
                    motorB_Read.T = (int32_t)ReadDataProcess(&can_rframeinfo[i].frame.data[4], 2);
                    flag &= 0x111111111101;
                    break;
                case 0x183:
                    motorC_Read.v = (int32_t)ReadDataProcess(&can_rframeinfo[i].frame.data[0], 4);
                    motorC_Read.T = (int32_t)ReadDataProcess(&can_rframeinfo[i].frame.data[4], 2);
                    flag &= 0x111111111011;
                    break;
                case 0x184:
                    motorD_Read.v = (int32_t)ReadDataProcess(&can_rframeinfo[i].frame.data[0], 4);
                    motorD_Read.T = (int32_t)ReadDataProcess(&can_rframeinfo[i].frame.data[4], 2);
                    flag &= 0x111111110111;
                    break;
                case 0x185:
                    motorE_Read.v = (int32_t)ReadDataProcess(&can_rframeinfo[i].frame.data[0], 4);
                    motorE_Read.T = (int32_t)ReadDataProcess(&can_rframeinfo[i].frame.data[4], 2);
                    flag &= 0x111111101111;
                    break;
                case 0x186:
                    motorF_Read.v = (int32_t)ReadDataProcess(&can_rframeinfo[i].frame.data[0], 4);
                    motorF_Read.T = (int32_t)ReadDataProcess(&can_rframeinfo[i].frame.data[4], 2);
                    flag &= 0x111111011111;
                    break;
                case 0x281:
                    motorA_Read.i = (uint32_t)ReadDataProcess(&can_rframeinfo[i].frame.data[0],4);
                    flag &= 0x111110111111;
                    break;
                case 0x282:
                    motorB_Read.i = (uint32_t)ReadDataProcess(&can_rframeinfo[i].frame.data[0],4);
                    flag &= 0x111101111111;
                    break;
                case 0x283:
                    motorC_Read.i = (uint32_t)ReadDataProcess(&can_rframeinfo[i].frame.data[0],4);
                    flag &= 0x111011111111;
                    break;
                case 0x284:
                    motorD_Read.i = (uint32_t)ReadDataProcess(&can_rframeinfo[i].frame.data[0],4);
                    flag &= 0x110111111111;
                    break;
                case 0x285:
                    motorE_Read.i = (uint32_t)ReadDataProcess(&can_rframeinfo[i].frame.data[0],4);
                    flag &= 0x101111111111;
                    break;
                case 0x286:
                    motorF_Read.i = (uint32_t)ReadDataProcess(&can_rframeinfo[i].frame.data[0],4);
                    flag &= 0x011111111111;
                    break;
                default:
                    continue;
                }
            }
        }
    }
}

///
/// \brief tubeMotionController::ReadDataProcess
/// \param datas
/// \param n
/// \return
/// 用于处理CAN数据
uint32_t tubeMotionController::ReadDataProcess(BYTE *datas, int n)
{
    uint32_t data = 0;
    for(int i = 0; i < n; ++i)
    {
        data |= datas[i] << (8 * i);
    }
    return data;
}

/***********************************************************
                   SLOT FUNCTION



************************************************************/
void tubeMotionController::ReceiveForce(Force ft)
{
    force = ft;
}


void tubeMotionController::SetSimple(bool flag)
{
    QString s = flag?"关闭":"启动";
    emit Logger(s + "Custom自定义模式");
    simpleFlag = flag;
}

void tubeMotionController::SetImpulseZero()
{
    impulse.SetZero();
}

void tubeMotionController::SetAutoParameter(std::vector<double> v)
{
    incTor = v[0];
    incVel = v[1];
    torqueLowerBound = v[2];
    vel_LowerBound = v[3];
}

void tubeMotionController::SetDirFlag(Direction dir)
{
    QString s = dir==Direction::forward?"正向":"反向";
    emit Logger("方向已改变:\n当前方向"+ s);
    dirFlag = dir;
}

void tubeMotionController::OverDevProtect(std::vector<int> delta)
{
    deltaV = delta;
}

void tubeMotionController::GetStopFlag(bool flag1, bool flag2)
{
    tube_dep_flag1 = !flag1;
    tube_dep_flag2 = !flag2;
}

void tubeMotionController::GetFlag1(bool flag)
{
    motionflag1 = flag;
}

void tubeMotionController::GetFlag2(bool flag)
{
    motionflag2 = flag;
}
