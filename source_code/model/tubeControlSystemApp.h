#ifndef TUBECONTROLSYSTEMAPP_H
#define TUBECONTROLSYSTEMAPP_H

#include <QObject>
#include <QApplication>
#include <QWidget>
#include <QSettings>
#include <QTimer>
#include <QThread>
#include <QMetaType>

#include "model/tubeDatabase.h"
#include "model/SensorDataCollector.h"
#include "model/tubeMotionController.h"
#include "model/tubeMotionParameter.h"
#include "zlgcan.h"
#include "mywrapperzlg.h"

class tubeControlSystemApp : public QObject
{
    Q_OBJECT
    QThread *tubemotionThread;
    QThread *sensorDataCollectorThread;

public:
    explicit tubeControlSystemApp(QObject *parent = nullptr);
    ~tubeControlSystemApp();
    static tubeControlSystemApp *instance();

    int run(int argc, char *argv[]);

    QSettings *settings;
    tubeDatabase *tubedatabase;
    SensorDataCollector *sensorDataCollector;
    tubeMotionController *tubemotionController;

    DEVICE_HANDLE dhandle;//设备句柄
    IProperty* pIproperty;//接口属性

signals:
    void startReadSendData();
    void SendTimer(Timer & timer);

public slots:
    bool globalStart();
    void globalStop();

private slots:

private:
    MyTime::Timer globalTimer;
    void init();
    bool device_init();
    bool hasRelease = false;
    ZlgCan myCan;
    QApplication *m_app;
    QWidget *m_mainWidget;
    QTimer m_timer;

};

#endif // CONTROLSYSTEMAPP_H
