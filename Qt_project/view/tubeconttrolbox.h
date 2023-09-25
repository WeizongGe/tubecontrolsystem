#ifndef TUBECONTTROLBOX_H
#define TUBECONTTROLBOX_H

#include <QDir>
#include <QFileDialog>
#include <QDebug>
#include <QGroupBox>
#include <QLineEdit>
#include <functional>
#include "model\tubeControlSystemApp.h"

namespace  Ori{
    ///
    /// \brief The SingleVel struct
    /// 单独的速度参数
    /// \param
    /// \A: desc: 电机A速度参数   Type: {double\qreal}  examp: 0.0
    /// \B: 同上 ^    B
    /// \C: 同上 |    C
    struct SingleVel
    {
        qreal A;
        qreal B;
        qreal C;

        SingleVel(qreal a, qreal b, qreal c):
            A(a), B(b), C(c){};
        explicit SingleVel(qreal i = 0):
            SingleVel{i, i, i}{};
    };

    ///
    /// \brief The SingleTor struct
    /// 单独的力矩参数
    struct SingleTor
    {
        qreal A;
        qreal B;
        qreal C;

        SingleTor(qreal a, qreal b, qreal c):
            A(a), B(b), C(c){};
        explicit SingleTor(qreal i = 0):
            SingleTor{i, i, i}{};
    };
}

using namespace Ori;

namespace Ui {
class tubeconttrolBox;
}

class tubeconttrolBox : public QGroupBox
{
    Q_OBJECT
public:
    explicit tubeconttrolBox(QWidget *parent = nullptr);
    ~tubeconttrolBox();
private slots:
    void ReceiveCommand(ZCAN_Receive_Data data);
    //void onSyncTimerTimeout();
    void on_globalStartButton_clicked();

    void on_deviceOpenButton_clicked();
    void on_deviceCloseButton_clicked();

    void on_exportButton_clicked();
    void on_exportFilePathBrowerButton_clicked();

    void on_singleVelLock_clicked();

    void on_singleSetModeTab_currentChanged(int index);

    void on_motorApointextensionButton_pressed();

    void on_motorApointgatheredButton_pressed();

    void on_motorApointextensionButton_released();

    void on_motorApointgatheredButton_released();

    void on_motorBpointextensionButton_released();

    void on_motorBpointgatheredButton_released();



    void on_motorBpointextensionButton_pressed();

    void on_motorBpointgatheredButton_pressed();

    void on_motorCpointextensionButton_pressed();

    void on_motorCpointextensionButton_released();

    void on_motorCpointgatheredButton_pressed();

    void on_motorCpointgatheredButton_released();

    void on_singleTorLock_clicked();

    void on_groupVelLock_clicked();

    void on_groupTorLock_clicked();

    void on_tubeextensionButton_clicked();

    void on_groupSetModeTab_currentChanged(int index);

    void on_stopButton_clicked();

    void on_tubegatheredButton_clicked();

    void on_pointextensionButton_pressed();

    void on_pointextensionButton_released();

    void on_pointgatheredButton_pressed();

    void on_pointgatheredButton_released();

    void on_tabModeWidget_currentChanged(int index);

    void on_canSendButton_clicked();

    void on_sensorLinkButton_clicked();

    void on_sensorSetZeroButton_clicked();

signals:
    void tubemotionModeUpdated(int &mode);
    void startReadMotor();
    void RequestSetZero();

private slots:
    void updatetubeMotion(const int tube_state);
    void ReceiveReachedX(double ix);
private:
    void globalStop();
    using PassFun = std::function<void(qreal, qreal, qreal)>;
    enum MotorMode{
        VelMode,
        TorMode
    };


    Ui::tubeconttrolBox *ui;
    tubeControlSystemApp *m_app;

    qreal move_limit(qreal input,qreal upper_limit,qreal lower_limit, QLineEdit* pInput);
    qreal vel_limit(qreal i, QLineEdit* pInput);
    qreal tor_limit(qreal i, QLineEdit* pInput);

    Ori::SingleVel singleVel;
    Ori::SingleTor singleTor;
    qreal groupVel;
    qreal groupTor;

    qreal reachedX;

    MotorMode sMode = VelMode;
    MotorMode gMode = VelMode;

    constexpr static const qreal LOWER_LIMIT = 0;
    constexpr static const qreal VEL_UPPER_LIMIT = 563.0/ 60.0;
    constexpr static const qreal TOR_UPPER_LIMIT = 47.85;
    constexpr static const qreal ToPassVal = 5.65 * 246.79 / 3.1415926535 / 30.0;
    constexpr static const qreal ToMMNM = 1000.0 * 5.65 * 246.79 / 3.1415926535 / 30.0;

    void EnableDriverButton();
    void DisableDriverButton();
    void EnableSensorButton();
    void DisableSensorButton();

    void PassZero();
    void PassGroup(qreal val);
    // 这四个重复度好大, 后期考虑拓展性可以想想如何优化
    void ChangeVelInputState();
    void ChangeTorInputState();
    void ChangeGroupVelInputState();
    void ChangeGroupTorInputState();

    PassFun PassVel;
    PassFun PassTor;

    bool CAN_STARTED = false;

    bool MOTOR_STARTED(){ return m_app->tubemotionController->STARTED();}
    bool SENSOR_STARTED(){ return m_app->sensorDataCollector->STARTED();}
    void SetSENSOR_STARTED(bool f = true){m_app->sensorDataCollector->changeStartStatus(f);}
    bool LOCKED();
};




#endif // TUBECONTTROLBOX_H
