#ifndef CONTROLBUTTONGROUP_H
#define CONTROLBUTTONGROUP_H

#include <QGroupBox>
#include "model/tubeControlSystemApp.h"
#include "settingfilterdialog.h"

namespace Ui {
class ControlButtonGroup;
}

class ControlButtonGroup : public QGroupBox
{
    Q_OBJECT
/// Fields:
public:

private:
    Ui::ControlButtonGroup *ui;
    tubeControlSystemApp* mApp;
    SettingFilterDialog * settingDialog;

    bool CAN_STARTED = false;

    bool MOTOR_STARTED(){ return mApp->tubemotionController->STARTED();}
    bool SENSOR_STARTED(){ return mApp->sensorDataCollector->STARTED();}
    void SetSENSOR_STARTED(bool f = true){mApp->sensorDataCollector->changeStartStatus(f);}

/// Member Functions:
public:
    explicit ControlButtonGroup(QWidget *parent = nullptr);
    ~ControlButtonGroup();

private:
    void globalStart();
    void globalStop();
    void buttonEnable(std::vector<QPushButton*> p_buttons, bool flag) const;
    void motorButtonEnable();
    void motorButtonDisable();
    void sensorButtonEnable(bool flag);

/// Signals:
signals:
    void startReadMotor();
    void RequestSetZero();

/// Slots Function:
private slots:
    void on_motorEnable_clicked();

    void on_motorDiable_clicked();

    void on_sensorLink_clicked();

    void on_sensorSetZero_clicked();

    void on_StartAndStop_clicked();

    void on_Setting_clicked();

};

#endif // CONTROLBUTTONGROUP_H
