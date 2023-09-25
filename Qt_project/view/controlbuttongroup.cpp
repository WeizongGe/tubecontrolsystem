#include "controlbuttongroup.h"
#include "ui_controlbuttongroup.h"


ControlButtonGroup::ControlButtonGroup(QWidget *parent) :
    QGroupBox(parent),
    ui(new Ui::ControlButtonGroup),
    mApp(tubeControlSystemApp::instance()),
    settingDialog(new SettingFilterDialog(this))
{
    ui->setupUi(this);

    connect(this, &ControlButtonGroup::startReadMotor,
            mApp->tubemotionController, &tubeMotionController::readParameter);

    connect(this, &ControlButtonGroup::RequestSetZero,
            mApp->sensorDataCollector, &SensorDataCollector::SetZero, Qt::DirectConnection);
}

ControlButtonGroup::~ControlButtonGroup()
{
    delete ui;
}

/**********************************************
 *              Help Function
 *
 *
 * *******************************************/
void ControlButtonGroup::globalStart()
{
    if(mApp->globalStart())
    {
        ui->StartAndStop->setStyleSheet("background-color: rgb(0,255,0)");
        ui->StartAndStop->setText("关闭设备");
        CAN_STARTED = true;
        motorButtonEnable();
        sensorButtonEnable(true);

    }
    else
    {
        QMessageBox::information(NULL, "打开设备失败", "请检查硬件连接，特别注意USBCAN设备是否连接正确或未被占用");
        ui->StartAndStop->setStyleSheet("background-color: rgb(255,0,0)");
    }
}

void ControlButtonGroup::globalStop()
{
    if(SENSOR_STARTED())
    {
        on_sensorLink_clicked();
    }
    mApp->globalStop();
    ui->StartAndStop->setStyleSheet("background-color:rgb(220,220,220)");
    ui->StartAndStop->setText("启动设备");
    motorButtonDisable();
    sensorButtonEnable(false);
    CAN_STARTED = false;
}

void ControlButtonGroup::buttonEnable(std::vector<QPushButton*> pbuttons, bool flag) const
{
    for(auto & pb: pbuttons)
    {
        pb->setEnabled(flag);
    }
}

void ControlButtonGroup::motorButtonEnable()
{
    ui->motorDiable->setEnabled(MOTOR_STARTED());
    ui->motorEnable->setEnabled(!MOTOR_STARTED());
    if(MOTOR_STARTED())
        emit startReadMotor();
}

void ControlButtonGroup::motorButtonDisable()
{
    buttonEnable({ui->motorEnable,
                  ui->motorDiable}, false);
}

void ControlButtonGroup::sensorButtonEnable(bool flag)
{
    buttonEnable({ui->sensorLink,
                  ui->sensorSetZero}, flag);
}

/***********************************************
 *               Slot Function
 *
 *
 * ********************************************/
void ControlButtonGroup::on_StartAndStop_clicked()
{
    if(!CAN_STARTED)
    {
        globalStart();
    }
    else
    {
        globalStop();
    }
}

void ControlButtonGroup::on_motorEnable_clicked()
{
    mApp->tubemotionController->changeStartStatus(true);
    mApp->tubemotionController->restartdrivers();
    motorButtonEnable();
}

void ControlButtonGroup::on_motorDiable_clicked()
{
    mApp->tubemotionController->changeStartStatus(false);
    mApp->tubemotionController->Stopdrivers();
    motorButtonEnable();
}

void ControlButtonGroup::on_sensorLink_clicked()
{
    mApp->sensorDataCollector->ch1_statechanged();
    if(mApp->sensorDataCollector->STARTED())
    {
         ui->sensorLink->setText("断开连接");
         emit mApp->startReadSendData();
    }
    else
    {
        ui->sensorLink->setText("连接并启动");
    }
}

void ControlButtonGroup::on_sensorSetZero_clicked()
{
    emit RequestSetZero();
}

void ControlButtonGroup::on_Setting_clicked()
{
    settingDialog->open();
}

