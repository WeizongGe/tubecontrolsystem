#ifndef CONTROLTAB_H
#define CONTROLTAB_H

#include <QDir>
#include <QFileDialog>
#include <QTabWidget>
#include <QLineEdit>
#include <QSlider>
#include "model/tubeControlSystemApp.h"



namespace Ui {
class ControlTab;
}

class ControlTab : public QTabWidget
{
    Q_OBJECT
/// Definition:
private:
    using PassFun = std::function<void(qreal, qreal, qreal, qreal, qreal, qreal)>;
    enum MotorMode{
        VelMode,
        TorMode
    };
/// Fileds:
public:

private:
    Ui::ControlTab *ui;
    tubeControlSystemApp * mApp;
    QThread* ctrTabThread;
    // The val Control
    MotorMode sMode = VelMode;
    MotorMode gMode = VelMode;
    // The val Send
    qreal groupVel;
    qreal groupVelUpperBound;
    qreal groupTor;
    qreal groupTorUpperBound;
    qreal velLimit;
    qreal velLimitUpperBound;

    Direction dir = Direction::stop;

    bool flag1 = false;
    bool flag2 = false;
/// MemberFunction:
public:
    explicit ControlTab(QWidget *parent = nullptr);
    ~ControlTab(); 
private:
    void initDataBaseDisplay();
    void initFunction();
    // In case Error Input
    qreal move_limit(qreal input,qreal upper_limit,qreal lower_limit, QLineEdit* pInput);
    qreal vel_limit(qreal i, QLineEdit* pInput);
    qreal tor_limit(qreal i, QLineEdit* pInput);
    // Some help Function with Lambda Expression
    PassFun PassVel;
    PassFun PassTor;

    void PassZero();
    void PassGroup(qreal val);
    // 这四个重复度好大, 后期考虑拓展性可以想想如何优化
    void ChangeVelInputState();
    void ChangeTorInputState();
    void ChangeGroupVelInputState();
    void ChangeGroupTorInputState();
    void ChangeInputState(std::vector<QLineEdit*> edits, QPushButton* button, std::vector<QSlider*> sliders = {});
    bool LOCKED();
/// Static Constant Val:
private:
    constexpr static const qreal LOWER_LIMIT = 0;
    constexpr static const qreal VEL_UPPER_LIMIT = ( 7220 / 411 * 3.1415926535 * 33.0)/ 60.0;
    constexpr static const qreal TOR_UPPER_LIMIT = (411.0 * 33.8 / 1000 / 0.0165) * 0.6;
    constexpr static const qreal ToPassVal = 411 * 60 / 3.1415926535 / 33.0;
    constexpr static const qreal ToMMNM =  16.5  / 411;
    constexpr static const qreal Ratio = 1000.0/TOR_UPPER_LIMIT;
    /*注释
     *7220：电机额定转速
     *411：减速器减速比
     *33.8：电机额定电流（mNm）
     *33.0：线辊直径+钢丝绳直径
     *16.5、0.165为上述的半径
     *0.6：减速器机械效率
     */
/// Slots Function
private slots:
    void on_ControlTab_currentChanged(int index);
    void on_groupSetModeTab_currentChanged(int index);
    void on_singleSetModeTab_currentChanged(int index);
    void on_tubeExtensionButton_clicked();
    void on_stopButton_clicked();
    void on_tubeGatheredButton_clicked();
    void on_pointExtensionButton_pressed();
    void on_pointExtensionButton_released();
    void on_pointGatheredButton_pressed();
    void on_pointGatheredButton_released();
    void on_groupVelLock_clicked();
    void on_groupTorLock_clicked();
    void on_singleVelLock_clicked();
    void on_singleTorLock_clicked();
    void on_exportFilePathBrowerButton_clicked();
    void on_exportButton_clicked();

    void on_Aextension_pressed();
    void on_Agathered_released();
    void on_Aextension_released();
    void on_Agathered_pressed();

    void on_Bextension_pressed();
    void on_Bextension_released();
    void on_Bgathered_pressed();
    void on_Bgathered_released();

    void on_Cextension_pressed();
    void on_Cextension_released();
    void on_Cgathered_pressed();
    void on_Cgathered_released();

    void on_Dextension_pressed();
    void on_Dextension_released();
    void on_Dgathered_pressed();
    void on_Dgathered_released();

    void on_Eextension_pressed();
    void on_Eextension_released();
    void on_Egathered_pressed();
    void on_Egathered_released();

    void on_Fextension_pressed();
    void on_Fextension_released();
    void on_Fgathered_pressed();
    void on_Fgathered_released();

    void on_VelSlider_valueChanged(int value);
    void on_torVelSlider_valueChanged(int value);
    void on_torSlider_valueChanged(int value);

    void LockSlider(bool flag);

    void ReceiveDirection(Direction dir);
    void on_checkABC_stateChanged(int arg1);
    void on_checkDEF_stateChanged(int arg1);

signals:
    void StopAuto();
    void SendABCFlag(bool flag);
    void SendDEFFlag(bool flag);
};

#endif // CONTROLTAB_H
