#ifndef SETTINGFILTERDIALOG_H
#define SETTINGFILTERDIALOG_H

#include <QDialog>
#include <QLineEdit>
#include "model/tubeControlSystemApp.h"


namespace Ui {
class SettingFilterDialog;
}

class SettingFilterDialog : public QDialog
{
    Q_OBJECT
/// Member Functions:
public:
    explicit SettingFilterDialog(QWidget *parent = nullptr);
    ~SettingFilterDialog();

private:
    void MyConnection();

private slots:
    void on_buttonBox_accepted();

    void on_buttonBox_rejected();

    void on_ParameterBox_toggled(bool arg1);

    void on_SetZero_clicked();

/// Signals:
    void on_pushButton_clicked(bool checked);

    void on_checkBox_stateChanged(int arg1);

signals:
    void SetCustomFlag(bool flag);
    void SetImpulseZero();
    void SetAutoParameter(std::vector<double> v);
    void SetDirFlag(Direction dir);
    void UseForceOptimizer(bool flag);
/// Fields:
private:
    Ui::SettingFilterDialog *ui;
    tubeControlSystemApp * mApp;    
public:
    bool flag = false;
};

#endif // SETTINGFILTERDIALOG_H
