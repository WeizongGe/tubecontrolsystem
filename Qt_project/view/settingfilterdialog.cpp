#include "settingfilterdialog.h"
#include "ui_settingfilterdialog.h"
#include <QDebug>

SettingFilterDialog::SettingFilterDialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::SettingFilterDialog),
    mApp(tubeControlSystemApp::instance())

{
    ui->setupUi(this);
    MyConnection();
}

SettingFilterDialog::~SettingFilterDialog()
{
    delete ui;
}

void SettingFilterDialog::MyConnection()
{

    connect(this, &SettingFilterDialog::SetCustomFlag,
            mApp->tubemotionController, &tubeMotionController::SetSimple, Qt::DirectConnection);
    connect(this, &SettingFilterDialog::SetImpulseZero,
            mApp->tubemotionController, &tubeMotionController::SetImpulseZero, Qt::DirectConnection);
    connect(this, &SettingFilterDialog::SetAutoParameter,
            mApp->tubemotionController, &tubeMotionController::SetAutoParameter, Qt::DirectConnection);
    connect(this, &SettingFilterDialog::SetDirFlag,
            mApp->tubemotionController, &tubeMotionController::SetDirFlag, Qt::DirectConnection);
    connect(this, &SettingFilterDialog::UseForceOptimizer,
            mApp->sensorDataCollector, &SensorDataCollector::ForceOptimizer, Qt::DirectConnection);
}


void SettingFilterDialog::on_buttonBox_accepted()
{
    if(ui->ParameterBox->isChecked())
    {
        emit SetAutoParameter({
                                  ui->ForceInc->text().toDouble(),
                                  ui->VelInc->text().toDouble(),
                                  ui->ForceLB->text().toDouble(),
                                  ui->VelLB->text().toDouble()
                              });
        QMessageBox::information(this, "参数已保存", "请确认参数准确无误！");
    }
}

void SettingFilterDialog::on_buttonBox_rejected()
{

}

void SettingFilterDialog::on_ParameterBox_toggled(bool arg1)
{
    emit SetCustomFlag(!arg1);
}

void SettingFilterDialog::on_SetZero_clicked()
{
    QMessageBox::information(NULL, "脉冲记数置零", "脉冲置零已完成，确保电机已连接");
    emit SetImpulseZero();
}

void SettingFilterDialog::on_pushButton_clicked(bool checked)
{
    emit SetDirFlag(checked?
                        Direction::backward:Direction::forward);
}

void SettingFilterDialog::on_checkBox_stateChanged(int arg1)
{
    if(arg1 == 0)
    {
        flag = false;
    }
    else{
        flag = true;
    }
    emit UseForceOptimizer(flag);
}

