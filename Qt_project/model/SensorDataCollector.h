#ifndef SENSORDATACOLLECTOR_H
#define SENSORDATACOLLECTOR_H

#include <QtGlobal>
#include <QObject>
#include <QDataStream>
#include <QTimer>
#include <QMetaObject>
#include "tubeUtils.h"
#include "model/Force.h"
//#include "model/tubeUtils.h"
#include "model/Leveling.h"
#include "MyLib/Filters/myFilter.h"

#include <QThread>
#include "zlgcan.h"
using MyTime::Timer;
namespace SENSOR {
    constexpr const double ALPHA = 0.3;
}

///
/// \brief The SensorDataCollector class
/// This Class is Used for Supllying
/// Control to the Can
class SensorDataCollector : public QObject
{
    Q_OBJECT
public:
    explicit SensorDataCollector(QObject *parent = nullptr);
    ~SensorDataCollector(){}
    void ch1_statechanged();
    void ch1_init();
    void tubestatechange(Leveling level);
    bool STARTED(){ return isstart;}
    // Interface for Write
    void changeStartStatus(bool flag = true){isstart = flag;}
    void detectDeviation(/*Force ft*/);

    Timer globalTimer;
    Force ft_data;
    Force ft_data_ori;
    Force pre_ft;
    std::vector<double> _curdeviation = std::vector<double>(6);
    std::vector<double> _deviation = std::vector<double>(6); //急停阈值，防跳线
    std::vector<int> _delta = std::vector<int>(6);
    bool _flag = false;

    Leveling le_signals;
    int tube_state = 0;

    CHANNEL_HANDLE CH(){return chHandle1;}
signals:
    void SensorDataUpdated(Force ft);          //通过信号的方式，将子线程中的张力数据发送给主线程
    void SendForce(Force  ft);
    void Logger(const QString& msg);
    void SendLevel(Leveling lv);
    //void SendState(int state);
    void DeviationOversize(std::vector<int> _delta);
    void SendStop(bool flag1, bool flag2);
    void SendDeviation(std::vector<double> curdev);

protected:
    void run();

private slots:

public slots:
    void ReceiveTimer(const Timer & t){globalTimer = t;};
    void ListenerRequstForce(bool flag);
    void ReceiveData();
    void Receivedhandle(DEVICE_HANDLE &dhandle);
    void SetZero();
    void ForceOptimizer(bool flag);
    void GetDeviation(double setdev, int at);
    void GetDevVector(std::vector<double> devvec);
    void ResetExtremum();

private:
    bool forceRequestFlag = false;
    bool forceOptimizerFlag = false;
    lowPassFilter<Force> forceFilter;

    bool isstart = false;//打开通道，接收数据
    double biasForce[6] = {0};
    int ch0_zero_state = 0;
    int ch1_zero_state = 0;
    //constexpr static const double FORCE_RATIO = 9.13 * 20 /1000.0;
    constexpr static const double FORCE_RATIO = 8.308 * 20 /1000.0;    
    double SLOPE[6] = {3.7679, 4.2178, 3.755, 4.3631, 4.1868, 4.2334};
    double INTERCEPT[6] = {-11.315, 6.6489, 6.6455, -12.514, -4.4258, -4.3128};
    double mean_force[6] = {0,0,0,0,0,0};
    double min = 10000;
    double max = 0;
    double total = 0;
    double count = 0;

    DEVICE_HANDLE m_dhandle1;
    ZCAN_CHANNEL_INIT_CONFIG cfg1;//can通道结构体初始化
    CHANNEL_HANDLE chHandle1;

    void ReadCAN();
    // 可以攒一个CAN类
    void AdjustData();
    void SendSignals();
    uint32_t ReadDataProcess(BYTE * datas, int n);
    void CalculateDeviation(Force ft);
    void DetermineStatus(int i);
    void MeanForce(Force ft);

};

#endif // SENSORDATACOLLECTOR_H
