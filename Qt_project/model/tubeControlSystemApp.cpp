
#include "model/tubeControlSystemApp.h"
#include "view/TubeControllSystem.h"


#include <QDebug>
#include <QtMath>
#include <synchapi.h>

Q_GLOBAL_STATIC(tubeControlSystemApp, g_tubecontrolSystemApp)

tubeControlSystemApp::tubeControlSystemApp(QObject *parent) : QObject(parent) {
    QApplication::setOrganizationName("BUAA");
    QApplication::setApplicationName("Tube Control System");
    QApplication::setApplicationVersion("0.2.1");

}

tubeControlSystemApp::~tubeControlSystemApp()
{
    tubemotionThread->quit();
    tubemotionThread->wait();

    sensorDataCollectorThread->quit();
    sensorDataCollectorThread->wait();

    if(hasRelease && pIproperty)
    {
        hasRelease = true;
        ReleaseIProperty(pIproperty);
        ZCAN_CloseDevice(dhandle);
    }
    delete m_mainWidget;
}

tubeControlSystemApp * tubeControlSystemApp::instance()
{
    return g_tubecontrolSystemApp;
}

int tubeControlSystemApp::run(int argc, char **argv)
{
    m_app = new QApplication(argc, argv);
    qRegisterMetaType<tubeMotionParameter>("MotionParameter");
    //设置字体
    QFont font  = m_app->font();
    font.setPointSize(8);
    //SimSun SimHei
    font.setFamily("Microsoft YaHei");
    m_app->setFont(font);
    init();
    m_mainWidget = new MainWidget;
    m_mainWidget->setWindowTitle("套筒展开控制软件");
    m_mainWidget->show();
    return  m_app->exec();
}

///
/// \brief tubeControlSystemApp::globalStart
/// \return {bool} Exap:false or true
/// 改了返回类型
bool tubeControlSystemApp::globalStart()
{
//    if(!myCan.DeviceInit())
//    {
//        retur
//    }
    if(!tubemotionController->STARTED() && device_init())
    {
        tubemotionController->init();

        if (pIproperty->SetValue("1/baud_rate", "500000" ) != STATUS_OK)
        {
            qDebug() << "设置波特率失败" ;
            qDebug("FAILED::SETTING::BAURD::RATE");
            qDebug("LOCATION::TUBE::MOTION::CONTROLLER::DEVICE::INIT");
            ReleaseIProperty(pIproperty);
            ZCAN_CloseDevice(dhandle);
            return false;
        }
        sensorDataCollector->ch1_init();
        tubemotionController->changeCanStatus(true);
        tubemotionController->changeStartStatus(true);

        globalTimer.start();
        emit SendTimer(globalTimer);
        return true;
    }

    qDebug("FAILD::INITIALIZE!");
    return false;
}

///
/// \brief tubeControlSystemApp::globalStop
/// TODO:
///     连续两次按下停止报错
void tubeControlSystemApp::globalStop()
{
    if(tubemotionController->CAN_STARTED())
    {
        tubemotionController->changeCanStatus(false);
        tubemotionController->changeStartStatus(false);
        tubemotionController->Stopdrivers();
        ReleaseIProperty(pIproperty);
        ZCAN_CloseDevice(dhandle);
    }
}

///
/// \brief tubeControlSystemApp::device_init
/// 这里有改动
/// 原：
///     void tubeControlSystemApp::device_init()
/// 改：
///     bool tubeControlSystemApp::device_init()
bool tubeControlSystemApp::device_init()
{
    dhandle = ZCAN_OpenDevice(ZCAN_USBCAN2, 0, 0);

    if (INVALID_DEVICE_HANDLE == dhandle)
    {
        qDebug( "打开设备失败" );
        qDebug("FAILED::OPEN::DEVICE");
        qDebug("LOCATION::TUBE::MOTION::CONTROLLER::DEVICE::INIT");
        return false;
    }
    pIproperty = GetIProperty(dhandle);
    if (NULL == pIproperty)
    {
        qDebug()<< "属性指针为空" ;
        qDebug("FAILED::NULLPTR::PROPERTY::POINTER");
        qDebug("LOCATION::TUBE::MOTION::CONTROLLER::DEVICE::INIT");
        ReleaseIProperty(pIproperty);
        ZCAN_CloseDevice(dhandle);
        return false;
    }

    if (pIproperty->SetValue("0/baud_rate", "500000" ) != STATUS_OK)
    {
        qDebug() << "设置波特率失败" ;
        qDebug("FAILED::SETTING::BAURD::RATE");
        qDebug("LOCATION::TUBE::MOTION::CONTROLLER::DEVICE::INIT");
        ReleaseIProperty(pIproperty);
        ZCAN_CloseDevice(dhandle);
        return false;
    }  

    //emit Senddhandle(dhandle);
    // 效果等同可以互相替换 好像并不行
    sensorDataCollector->Receivedhandle(dhandle);
    tubemotionController->Receivedhandle(dhandle);

    return true;
}

void tubeControlSystemApp::init()
{
    // 在exe同目录下保存应用程序的配置
    settings = new QSettings(QApplication::applicationDirPath() + "/config/settings.ini", QSettings::IniFormat, this);

    // 初始化传感器
    sensorDataCollector = new SensorDataCollector;
    sensorDataCollectorThread = new QThread(this);
    sensorDataCollector->moveToThread(sensorDataCollectorThread);
    connect(sensorDataCollectorThread, &QThread::finished, sensorDataCollector, &QObject::deleteLater);
    connect(this, &tubeControlSystemApp::startReadSendData, sensorDataCollector, &SensorDataCollector::ReceiveData);
    sensorDataCollectorThread->start();

    //初始化运动控制器
    tubemotionController = new tubeMotionController;
    tubemotionThread = new QThread(this);
    tubemotionController->moveToThread(tubemotionThread);
    connect(tubemotionThread, &QThread::finished, tubemotionController, &QObject::deleteLater);
    tubemotionThread->start();

    // 初始化数据库
    tubedatabase = new tubeDatabase(this);

    connect(sensorDataCollector, &SensorDataCollector::SensorDataUpdated,
            tubedatabase, &tubeDatabase::saveSensorData);
    connect(tubemotionController, &tubeMotionController::tubemotionParameterUpdated,
            tubedatabase, &tubeDatabase::savetubeMotionParameter);

    // Timer
    connect(this, &tubeControlSystemApp::SendTimer, tubemotionController,
            &tubeMotionController::ReceiveTimer,Qt::DirectConnection );
    connect(this, &tubeControlSystemApp::SendTimer, sensorDataCollector,
            &SensorDataCollector::ReceiveTimer, Qt::DirectConnection);

    connect(sensorDataCollector, &SensorDataCollector::SendForce,
            tubemotionController, &tubeMotionController::ReceiveForce, Qt::DirectConnection);

    connect(tubemotionController, &tubeMotionController::ForceRequest,
            sensorDataCollector, &SensorDataCollector::ListenerRequstForce, Qt::DirectConnection);

    connect(sensorDataCollector, &SensorDataCollector::DeviationOversize,
            tubemotionController, &tubeMotionController::OverDevProtect, Qt::DirectConnection);

    connect(sensorDataCollector, &SensorDataCollector::SendStop,
            tubemotionController, &tubeMotionController::GetStopFlag, Qt::DirectConnection);    
}

