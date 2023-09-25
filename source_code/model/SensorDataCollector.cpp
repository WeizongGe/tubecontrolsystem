#include "model\SensorDataCollector.h"
#include "model\tubeUtils.h"

#include<QDebug>
#include<QString>
#include<QByteArray>
#include<QMetaType>
#include<synchapi.h>
///
/// Conf:
///      isstart 在哪里被设置为true？
///      怎么一直是false
SensorDataCollector::SensorDataCollector( QObject *parent): QObject(parent),
    pre_ft(), forceFilter(SENSOR::ALPHA),
    m_dhandle1(nullptr), chHandle1(nullptr)
{
    qRegisterMetaType<Force>("Force");
    qRegisterMetaType<Force*>("Force*");
}

void SensorDataCollector::run()
{
    isstart = false;
    ch1_init();
}
void SensorDataCollector::ch1_init()
{
    memset(&cfg1, 0, sizeof(cfg1));
    cfg1.can_type = TYPE_CAN;
    cfg1.can.filter = 0;
    cfg1.can.mode = 0;                   //0 正常模式, 1为只听模式
    cfg1.can.acc_code = 0;
    cfg1.can.acc_mask = 0xffffffff;
    chHandle1 = ZCAN_InitCAN(m_dhandle1, 1, &cfg1);
    if (INVALID_CHANNEL_HANDLE == chHandle1)
    {
        emit Logger("通道1初始化失败,请检查USBCAN设备");
        qDebug("FAILED::CHANNEL:INITIALZE");
        qDebug("LOCATION::SENSOR::DATA::COLLECTOR::CH1::INIT");
        ZCAN_ClearBuffer(chHandle1);      //清空缓冲区
        ZCAN_ResetCAN(chHandle1);         //通道复位
    }
    if (ZCAN_StartCAN(chHandle1) != STATUS_OK)
    {
        qDebug() << "启动通道失败" ;
        qDebug("FAILED::CHANNEL::SENSOR::DATACOLLECTOR::INITIALIZATION");
        ZCAN_ClearBuffer(chHandle1); //清空缓冲区
        ZCAN_ResetCAN(chHandle1); //通道复位
    }
    qDebug("ch1%lld",(long long)chHandle1);
    ZCAN_CHANNEL_STATUS * pinfo = new ZCAN_CHANNEL_STATUS;
    ZCAN_ReadChannelStatus(chHandle1, pinfo);
    qDebug("PAUSE");
}

///
/// \brief SensorDataCollector::ch1_statechanged
/// 这里感觉功能写反了互相换一下
void SensorDataCollector::ch1_statechanged()
{
    isstart = !isstart;
    if(isstart == false)
    {
        emit Logger("传感器通道Channel 1关闭");
        qDebug("SENSOR::CHANNEL:CLOSING");
        ZCAN_ClearBuffer(chHandle1); //清空缓冲区
        ZCAN_ResetCAN(chHandle1); //通道复位
    }
    else
    {
        emit Logger("传感器通道Channel 1开启");
        qDebug("SENSOR::CHANNEL::OPENNING");
        if (ZCAN_StartCAN(chHandle1) != STATUS_OK)
        {
            isstart = false;
            emit Logger("传感器通道Channel 1关闭");
            qDebug("FAILED::CHANNEL::SENSOR::DATACOLLECTOR::INITIALIZATION");
            ZCAN_ClearBuffer(chHandle1); //清空缓冲区
            ZCAN_ResetCAN(chHandle1); //通道复位
        }
    }
}

void SensorDataCollector::Receivedhandle(DEVICE_HANDLE &dhandle)
{
    m_dhandle1 = dhandle;
    if (INVALID_DEVICE_HANDLE == m_dhandle1)
    {
        qDebug( "设备句柄传递失败" );
        qDebug("FAILED::PASS::DEVICE::HANDLE");
        qDebug("LOCATION::SENSOR::DATA::COLLECTOR::RECECIVED::HANDLE");
        return;
    }
}

/************************************************************
                        Main Loop


*************************************************************/
void SensorDataCollector::ReceiveData()
{
    while(isstart)
    {
        // 从CAN口读取数据        
        ReadCAN();
        //emit Logger("从CAN口读取数据");
        // 对数据进行调整处理
        AdjustData();
        //emit Logger("对数据进行调整处理");
        // 发送信号函数
        SendSignals();
        //emit Logger("发送信号函数");
        Sleep(50);
    }
}

void SensorDataCollector::SendSignals()
{
    emit SensorDataUpdated(ft_data);
    emit SendDeviation(_curdeviation);
    if(forceRequestFlag)
    {
        emit SendForce(ft_data);
    }
    if(_flag)
    {
        emit DeviationOversize(_delta, _flag);
    }
}

void SensorDataCollector::AdjustData()
{
//    ft_data = FORCE_RATIO * ft_data - biasForce;
    ft_data_ori = 0.02 * ft_data;//使用原始读数计算bias，使下式成立
    ft_data = SLOPE * (ft_data_ori- biasForce) - INTERCEPT;

    ft_data = forceFilter(ft_data, pre_ft);
    pre_ft = ft_data;
    CalculateDeviation(ft_data);
//    MeanForce(ft_data);

    if(forceOptimizerFlag)
    {
        detectDeviation(/*ft_data*/);
    }

    tubestatechange(le_signals);
}

void SensorDataCollector::MeanForce(Force ft)
{
    static int i = 0;
    if(i < 20)
    {
       mean_force[0] += std::abs(ft.FA);
       mean_force[1] += std::abs(ft.FB);
       mean_force[2] += std::abs(ft.FC);
       mean_force[3] += std::abs(ft.FD);
       mean_force[4] += std::abs(ft.FE);
       mean_force[5] += std::abs(ft.FF);
        ++i;
    }
    else
    {
        double mean = mean_force[3]/20;
        if(mean < min)
            min = mean;
            emit Logger("每20组F的均值最小为：" + QString::number(min));
        if(mean > max)
            max = mean;
            emit Logger("每20组F的均值最大为：" + QString::number(max));
        total += mean;
        ++count;
        emit Logger("过程中F的均值为：" + QString::number(total/count));
        for(int j = 0; j < 6; j++)
        {
            mean_force[j] = 0;
        }
        i = 0;
    }
}

void SensorDataCollector::ReadCAN()
{
    //emit Logger("进入ReadCAN!");
    static ZCAN_Receive_Data buff[50];

    static double basetime = 0;
    if(!basetime)
    {
        basetime = getCurrentTime();
    }
    if (ZCAN_GetReceiveNum(chHandle1, TYPE_CAN))
    {
        //emit Logger("进入通道1");
        uint len = ZCAN_Receive(chHandle1, buff, 50, 100);//ZCAN_Receive(CAN通道句柄，接收信息结构体，本次接收报文最大个数50，等待时间ms)函数接收数据。
        bool flag181 = true, flag281 = true, flag182 = true;
        for(uint i = 0; i < len && (flag181||flag281||flag182); i++)
        {
            uint id = GET_ID(buff[i].frame.can_id);
            if(!IS_RTR(buff[i].frame.can_id))//如果是数据帧，获取数据帧里面的数据
            {
                //emit Logger("开始读力/电平");
                switch(id)
                {
                    case 0x181:
                        ft_data.FA = (int16_t)ReadDataProcess(&buff[i].frame.data[0], 2);   //mv转v，量程(200N/10v),单位：N
                        ft_data.FB = (int16_t)ReadDataProcess(&buff[i].frame.data[2], 2);
                        ft_data.FC = (int16_t)ReadDataProcess(&buff[i].frame.data[4], 2);
                        ft_data.FD = (int16_t)ReadDataProcess(&buff[i].frame.data[6], 2);//mv转v，量程(500mA/10v),单位：mA
                        flag181 = false;
                        //emit Logger(QString::number(ft_data.FA));
                        break;
                    case 0x281:
                        ft_data.FE = (int16_t)ReadDataProcess(&buff[i].frame.data[0], 2);//mv转v，量程(500mA/10v),单位：mA
                        ft_data.FF = (int16_t)ReadDataProcess(&buff[i].frame.data[2], 2);
                        flag281 = false;
                        break;
                    case 0x182:
                        le_signals.Readleveling(buff[i].frame.data[0]);
                        flag182 = false;
                        break;
                    default:
                        continue;
                }
            }
        }
        ft_data.time = globalTimer.nowTime();
    }
}

uint32_t SensorDataCollector::ReadDataProcess(BYTE * datas, int n)
{
    uint32_t data = 0;
    for(int i = 0; i < n; ++i)
    {
        data |= datas[i] << (8 * i);
    }
    return data;
}

void SensorDataCollector::CalculateDeviation(Force ft)
{
    _curdeviation[0] = ft.FA - ft.FB;
    _curdeviation[1] = ft.FB - ft.FC;
    _curdeviation[2] = ft.FC - ft.FA;
    _curdeviation[3] = ft.FD - ft.FE;
    _curdeviation[4] = ft.FE - ft.FF;
    _curdeviation[5] = ft.FF - ft.FD;
}

void SensorDataCollector::tubestatechange(Leveling level)
{
    if(level.a + level.b + level.c >= 2 && level.d + level.e + level.f >=2)
    {
        //tube_state = 5;
        emit SendStop(true,true);
        emit Logger("展开到位成功");
    }
    else if(level.a + level.b + level.c < 2 && level.d + level.e + level.f >=2)
    {
        emit SendStop(false,true);
        emit Logger("二号机组展开到位");
    }
    else if(level.a + level.b + level.c >= 2 && level.d + level.e + level.f <2)
    {
        emit SendStop(true,false);
        emit Logger("一号机组展开到位");
    }
    else
    {
        //qDebug() << "展开到位检测信号无法识别" ;
        //tube_state = 0;
        emit SendStop(false,false);
    }
    emit SendLevel(level);
}

void SensorDataCollector::DetermineStatus(int i)
{
    if(std::abs(_curdeviation[i]) > _deviation[i])
    {
        if(_curdeviation[i] > 0)
            _delta[i] = 1;//力有方向，为负
        else
            _delta[i] = -1;
    }
    else
        _delta[i] = 0;
//    qDebug()<<"delta:"<<QString::number(_delta[i]);
}

void SensorDataCollector::detectDeviation(/*Force ft*/)
{
    for(int i = 0; i < 6; i++)
    {
        DetermineStatus(i);
    }
    _flag = true;
}

/*****************************************************
                  SLOTS  FUNCTION


******************************************************/
void SensorDataCollector::SetZero()
{
    //解决倍增bug
    for(int i = 0; i< 6;i ++)
    {
        biasForce[i] = 0;
    }

    std::vector<Force> fs;
    for(int i = 0; i < 5; ++i)
    {
        fs.push_back(ft_data_ori);
        Sleep(50);
    }
    for(auto & f: fs)
    {
        biasForce += f/fs.size();//始终累加，
    }
    //置零同时重新计算截距
    for(int i = 0; i < 6; ++i)
    {
        INTERCEPT[i] = 0;
    }
}

void SensorDataCollector::ListenerRequstForce(bool flag)
{
    forceRequestFlag = flag;
}

void SensorDataCollector::ForceOptimizer(bool flag)
{
    forceOptimizerFlag = flag;
}

void SensorDataCollector::GetDeviation(double setdev, int at)
{
    _deviation[at] = setdev;
}

void SensorDataCollector::GetDevVector(std::vector<double> devvec)
{
    for (int i=0;i<6;++i) {
        _deviation[i] = devvec[i];
        qDebug()<<"dev:"<<QString::number(_deviation[i]);
    }
}

void SensorDataCollector::ResetExtremum()
{
//    emit Logger("reset extremum");
    min = 10000;
    max = 0;
    total = 0;
    count = 0;
}
