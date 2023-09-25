#include "controltab.h"
#include "ui_controltab.h"
#include <QtMath>
#include <QMetaType>

static auto checkZero = [](std::vector<double> && is)->Direction{
    for(auto & i : is)
    {
        if(std::abs(i) > 1e-5)
        {
            if(i > 1e-5)
            {
                return Direction::forward;
            }
            else
            {
                return Direction::backward;
            }

        }
    }
    return Direction::stop;
};

ControlTab::ControlTab(QWidget *parent) :
    QTabWidget(parent),
    ui(new Ui::ControlTab),
    mApp(tubeControlSystemApp::instance())
{
    ui->setupUi(this);
    initFunction();
    initDataBaseDisplay();
    qRegisterMetaType<Direction>("Direction");
    connect(mApp->tubemotionController, &tubeMotionController::RequestLockSliders,
            this, &ControlTab::LockSlider, Qt::AutoConnection);
    connect(mApp->tubemotionController, &tubeMotionController::SendDirection,
            this, &ControlTab::ReceiveDirection, Qt::AutoConnection);
    connect(this, &ControlTab::StopAuto,
            mApp->tubemotionController, &tubeMotionController::StopAutoStatus,Qt::DirectConnection);
    connect(this,&ControlTab::SendABCFlag,
            mApp->tubemotionController, &tubeMotionController::GetABCFlag, Qt::DirectConnection);
    connect(this,&ControlTab::SendDEFFlag,
            mApp->tubemotionController, &tubeMotionController::GetDEFFlag, Qt::DirectConnection);

}

ControlTab::~ControlTab()
{
    delete ui;
}

/*****************************************************
                   Init Function


*******************************************************/
void ControlTab::initDataBaseDisplay()
{
    QString dbDirPath = QCoreApplication::applicationDirPath() + "/database";
    QDir dbDir(dbDirPath);
    dbDir.setSorting(QDir::Time);//修改时间排序
    for (QString dbFileName : dbDir.entryList()) {
        if (dbFileName == "." || dbFileName == "..") continue;
        ui->comboBox->addItem(dbFileName);
    }
    ui->exportFilePathEdit->setText(QCoreApplication::applicationDirPath() + "/data_output/data.csv");
}

void ControlTab::initFunction()
{

    // Lambda Definition Function-Liker
    PassVel = [this](qreal a, qreal b, qreal c, qreal d, qreal e, qreal f){
        if(LOCKED()){
            dir = checkZero({a, b, c, d, e, f});
            mApp->tubemotionController->PVmodeSetVel(a * ToPassVal, b * ToPassVal, c * ToPassVal,
                                                     d * ToPassVal, e * ToPassVal, f * ToPassVal);
        }
        else
        {
            QMessageBox::information(NULL, QStringLiteral("未锁定"), QStringLiteral("请先锁定再启动"));
        }
    };

    PassTor = [this](qreal a, qreal b, qreal c, qreal d, qreal e, qreal f){
        if(LOCKED()){
            dir = checkZero({a, b, c, d, e, f});
            mApp->tubemotionController->CSTmodeSetVel(velLimit * ToPassVal);
            mApp->tubemotionController->CSTmodeSetTor(a * Ratio, b * Ratio, c * Ratio,
                                                      d * Ratio, e * Ratio, f * Ratio);
        }
        else
        {
            QMessageBox::information(NULL, QStringLiteral("未锁定"), QStringLiteral("请先锁定再启动"));
        }
    };
}

/******************************
 *          Limit Function
 *
 *
 *
*******************************/
qreal ControlTab::move_limit(qreal input, qreal low_limit, qreal high_limit, QLineEdit* pInput)
{
    if(input < low_limit)
    {
        QMessageBox::warning(NULL, "警告", "输入值过小,已为您重新赋值");
        pInput->setText(QString::number(low_limit));
        return low_limit;
    }
    else if(input > high_limit)
    {
        QMessageBox::warning(NULL, "警告", "输入值过大,已为您重新赋值");
        pInput->setText(QString::number(high_limit));
        return high_limit;
    }
    else
        return input;
}

qreal ControlTab::vel_limit(qreal i, QLineEdit* pInput)
{
    return move_limit(i, LOWER_LIMIT, VEL_UPPER_LIMIT, pInput);
}

qreal ControlTab::tor_limit(qreal i, QLineEdit* pInput)
{
    return move_limit(i, LOWER_LIMIT, TOR_UPPER_LIMIT, pInput);
}

/******************************
 *          Lock Function
 *
 *
 *
*******************************/
const static QString BackGound = "background-color: rgb";
///
/// \brief tubeconttrolBox::ChageVelInputState
/// \def 改变速度输入状态栏
void ControlTab::ChangeVelInputState()
{
    ChangeInputState({ui->velAInput,
                      ui->velBInput,
                      ui->velCInput,
                      ui->velDInput,
                      ui->velEInput,
                      ui->velFInput}, ui->singleVelLock);
}

void ControlTab::ChangeTorInputState()
{
    ChangeInputState({ui->torAInput,
                      ui->torBInput,
                      ui->torCInput,
                      ui->torDInput,
                      ui->torEInput,
                      ui->torFInput}, ui->singleTorLock);
}

void ControlTab::ChangeGroupVelInputState()
{
    ChangeInputState({ui->groupVelInput}, ui->groupVelLock, {ui->VelSlider});
}

void ControlTab::ChangeGroupTorInputState()
{
    ChangeInputState({ui->groupTorInput,
                      ui->groupVelLimitInput}, ui->groupTorLock,
                      {ui->torSlider,
                       ui->torVelSlider});
}

void ControlTab::ChangeInputState(std::vector<QLineEdit*> edits, QPushButton* button, std::vector<QSlider*> sliders)
{
    bool Lock = edits[0]->isReadOnly();
    QString color = Lock?"(255, 255, 255)":"(200, 200, 200)";
    for(auto & edit: edits)
    {
        edit->setReadOnly(!Lock);
        edit->setStyleSheet(BackGound + color);
    }

    for(auto & slider: sliders)
    {
        slider->setEnabled(!Lock);
        slider->setValue(Lock?0:slider->maximum());
        slider->valueChanged(Lock?0:slider->maximum());
    }

    QString text = Lock?"锁定":"解锁";
    button->setText(text);

}


void ControlTab::PassGroup(qreal val)
{
    if(gMode == VelMode){
        if(flag1 && flag2)
            PassVel(val, val, val, val, val, val);
        else if(flag1 && !flag2){
            PassVel(val,val,val,0,0,0);}
        else if(!flag1 && flag2){
            PassVel(0,0,0,val,val,val);}
        else
            QMessageBox::information(NULL, QStringLiteral("未勾选"), QStringLiteral("请选择电机组"));
    }
    else
    {
        velLimit = ui->actualVelLimit->text().toDouble();
        if(flag1 && flag2)
            PassTor(val, val, val, val, val, val);
        else if(flag1 && !flag2){
            PassTor(val,val,val,0,0,0);}
        else if(!flag1 && flag2){
            PassTor(0,0,0,val,val,val);}
        else
            QMessageBox::information(NULL, QStringLiteral("未勾选"), QStringLiteral("请选择电机组"));
    }
}

void ControlTab::PassZero()
{
    MotorMode mode = currentIndex() == 0? gMode:sMode;
    if(mode == VelMode)
        PassVel(0, 0, 0, 0, 0, 0);
    else{        
//        PassTor(0, 0, 0, 0, 0, 0);
        mApp->tubemotionController->status = mApp->tubemotionController->Stop;
    }
    emit StopAuto();
}

bool ControlTab::LOCKED()
{
    if(currentIndex() == 0)
    {
        if(ui->groupSetModeTab->currentIndex() == 0)
        {
            return ui->groupVelInput->isReadOnly();
        }
        else
        {
            return ui->groupTorInput->isReadOnly();
        }
    }
    else
    {
        if(ui->singleSetModeTab->currentIndex() == 0)
        {
            return ui->velAInput->isReadOnly();
        }
        else
        {
            return ui->torAInput->isReadOnly();
        }
    }
}
/*****************************************************
                   SLOT FUNCTION


*******************************************************/
void ControlTab::on_ControlTab_currentChanged(int index)
{
    if(mApp->tubemotionController->STARTED())
    {
        switch(index)
        {
            case 0: on_groupSetModeTab_currentChanged(ui->groupSetModeTab->currentIndex());break;
            case 1: on_singleSetModeTab_currentChanged(ui->singleSetModeTab->currentIndex());break;
        }
    }
}

void ControlTab::on_groupSetModeTab_currentChanged(int index)
{
    if(mApp->tubemotionController->STARTED())
    {
        switch(index)
        {
            case 0: gMode = VelMode;
                    mApp->tubemotionController->setMotionMode(0x3);
                    break;
            case 1: gMode = TorMode;
                    mApp->tubemotionController->setMotionMode(0xA);
                    mApp->tubemotionController->CSTmodeHold();
                    break;
        }
    }
}

void ControlTab::on_singleSetModeTab_currentChanged(int index)
{
    if(mApp->tubemotionController->STARTED())
    {
        switch(index)
        {
            case 0: sMode = VelMode;
                    mApp->tubemotionController->setMotionMode(0x3);
                    break;
            case 1: sMode = TorMode;
                    mApp->tubemotionController->setMotionMode(0xA);
                    mApp->tubemotionController->CSTmodeHold();
                    break;
        }
    }
}

void ControlTab::on_tubeExtensionButton_clicked()
{
    PassGroup(gMode == VelMode?groupVel:groupTor);
}

void ControlTab::on_stopButton_clicked()
{
    PassZero();
}

void ControlTab::on_tubeGatheredButton_clicked()
{
    PassGroup(gMode == VelMode?-groupVel:-groupTor);
}

void ControlTab::on_pointExtensionButton_pressed()
{
    on_tubeExtensionButton_clicked();
}

void ControlTab::on_pointExtensionButton_released()
{
    PassZero();
}

void ControlTab::on_pointGatheredButton_pressed()
{
    on_tubeGatheredButton_clicked();
}

void ControlTab::on_pointGatheredButton_released()
{
    PassZero();
}

void ControlTab::on_groupVelLock_clicked()
{
    groupVelUpperBound = vel_limit(ui->groupVelInput->text().toDouble(), ui->groupVelInput);
    ChangeGroupVelInputState();
}

void ControlTab::on_groupTorLock_clicked()
{
    groupTorUpperBound = tor_limit(ui->groupTorInput->text().toDouble(), ui->groupTorInput);
    velLimitUpperBound = vel_limit(ui->groupVelLimitInput->text().toDouble(), ui->groupVelLimitInput);
    ChangeGroupTorInputState();
}

void ControlTab::on_singleVelLock_clicked()
{
    vel_limit(ui->velAInput->text().toDouble(), ui->velAInput);
    vel_limit(ui->velBInput->text().toDouble(), ui->velBInput);
    vel_limit(ui->velCInput->text().toDouble(), ui->velCInput);
    vel_limit(ui->velDInput->text().toDouble(), ui->velDInput);
    vel_limit(ui->velEInput->text().toDouble(), ui->velEInput);
    vel_limit(ui->velFInput->text().toDouble(), ui->velFInput);
    ChangeVelInputState();
}

void ControlTab::on_singleTorLock_clicked()
{
    tor_limit(ui->torAInput->text().toDouble(), ui->torAInput);
    tor_limit(ui->torBInput->text().toDouble(), ui->torBInput);
    tor_limit(ui->torCInput->text().toDouble(), ui->torCInput);
    tor_limit(ui->torDInput->text().toDouble(), ui->torDInput);
    tor_limit(ui->torEInput->text().toDouble(), ui->torEInput);
    tor_limit(ui->torFInput->text().toDouble(), ui->torFInput);
    ChangeTorInputState();
}

void ControlTab::on_exportFilePathBrowerButton_clicked()
{
    QString fileName = QFileDialog::getSaveFileName(this, tr("Save File"),
                               "",
                               tr("CSV File (*.csv)"));
    if (!fileName.isEmpty()) {
        ui->exportFilePathEdit->setText(fileName);
    }
}

void ControlTab::on_exportButton_clicked()
{
    QString dbFilePath = QCoreApplication::applicationDirPath() + "/database/" + ui->comboBox->currentText();
    QString exportFilePath = ui->exportFilePathEdit->text();
    QString tableButtonName = ui->DataBaseButtonGroup->checkedButton()->objectName();
    QString tableName;
    if (tableButtonName == "ForceSensorDataRadioButton")
    {
        tableName = "force_sensor_data";
    }
    else if (tableButtonName == "tubemotionParameterRadioButton")
    {
        tableName = "tube_motion_parameter";
    }
    QMessageBox::information(NULL,"数据已导出",
                             "导出数据如下：\n"
                             "db file" + dbFilePath +"\n"
                             "csv file" +exportFilePath + "\n"
                             "table" + tableName);
    if (dbFilePath.isEmpty() || exportFilePath.isEmpty() || tableName.isEmpty()) {
        return;
    }
    tubeControlSystemApp::instance()->tubedatabase->exportData(dbFilePath, exportFilePath, tableName);
}

void ControlTab::on_Aextension_pressed()
{
    if(ui->singleSetModeTab->currentIndex())
    {
        PassTor(ui->torAInput->text().toDouble(), 0, 0, 0, 0, 0);
    }
    else
    {
        PassVel(ui->velAInput->text().toDouble(), 0, 0, 0, 0, 0);
    }
}

void ControlTab::on_Agathered_pressed()
{
    if(ui->singleSetModeTab->currentIndex())
    {
        PassTor(-ui->torAInput->text().toDouble(), 0, 0, 0, 0, 0);
    }
    else
    {
        PassVel(-ui->velAInput->text().toDouble(), 0, 0, 0, 0, 0);
    }
}

void ControlTab::on_Agathered_released()
{
    PassZero();
}

void ControlTab::on_Aextension_released()
{
    PassZero();
}

void ControlTab::on_Bextension_pressed()
{
    if(ui->singleSetModeTab->currentIndex())
    {
        PassTor(0, ui->torBInput->text().toDouble(), 0, 0, 0, 0);
    }
    else
    {
        PassVel(0, ui->velBInput->text().toDouble(), 0, 0, 0, 0);
    }
}

void ControlTab::on_Bextension_released()
{
    PassZero();
}

void ControlTab::on_Bgathered_pressed()
{
    if(ui->singleSetModeTab->currentIndex())
    {
        PassTor(0, -ui->torBInput->text().toDouble(), 0, 0, 0, 0);
    }
    else
    {
        PassVel(0, -ui->velBInput->text().toDouble(), 0, 0, 0, 0);
    }
}

void ControlTab::on_Bgathered_released()
{
    PassZero();
}

void ControlTab::on_Cextension_pressed()
{
    if(ui->singleSetModeTab->currentIndex())
    {
        PassTor(0, 0, ui->torCInput->text().toDouble(), 0, 0, 0);
    }
    else
    {
        PassVel(0, 0, ui->velCInput->text().toDouble(), 0, 0, 0);
    }
}

void ControlTab::on_Cextension_released()
{
    PassZero();
}

void ControlTab::on_Cgathered_pressed()
{
    if(ui->singleSetModeTab->currentIndex())
    {
        PassTor(0, 0, -ui->torCInput->text().toDouble(), 0, 0, 0);
    }
    else
    {
        PassVel(0, 0, -ui->velCInput->text().toDouble(), 0, 0, 0);
    }
}

void ControlTab::on_Cgathered_released()
{
    PassZero();
}

void ControlTab::on_Dextension_pressed()
{
    if(ui->singleSetModeTab->currentIndex())
    {
        PassTor(0, 0, 0, ui->torDInput->text().toDouble(), 0, 0);
    }
    else
    {
        PassVel(0, 0, 0, ui->velDInput->text().toDouble(), 0, 0);
    }
}

void ControlTab::on_Dextension_released()
{
    PassZero();
}

void ControlTab::on_Dgathered_pressed()
{
    if(ui->singleSetModeTab->currentIndex())
    {
        PassTor(0, 0, 0, -ui->torDInput->text().toDouble(), 0, 0);
    }
    else
    {
        PassVel(0, 0, 0, -ui->velDInput->text().toDouble(), 0, 0);
    }
}

void ControlTab::on_Dgathered_released()
{
    PassZero();
}

void ControlTab::on_Eextension_pressed()
{
    if(ui->singleSetModeTab->currentIndex())
    {
        PassTor(0, 0, 0, 0, ui->torEInput->text().toDouble(), 0);
    }
    else
    {
        PassVel(0, 0, 0, 0, ui->velEInput->text().toDouble(), 0);
    }
}

void ControlTab::on_Eextension_released()
{
    PassZero();
}

void ControlTab::on_Egathered_pressed()
{
    if(ui->singleSetModeTab->currentIndex())
    {
        PassTor(0, 0, 0, 0, -ui->torEInput->text().toDouble(), 0);
    }
    else
    {
        PassVel(0, 0, 0, 0, -ui->velEInput->text().toDouble(), 0);
    }
}

void ControlTab::on_Egathered_released()
{
    PassZero();
}

void ControlTab::on_Fextension_pressed()
{
    if(ui->singleSetModeTab->currentIndex())
    {
        PassTor(0, 0, 0, 0, 0, ui->torFInput->text().toDouble());
    }
    else
    {
        PassVel(0, 0, 0, 0, 0, ui->velFInput->text().toDouble());
    }
}

void ControlTab::on_Fextension_released()
{
    PassZero();
}

void ControlTab::on_Fgathered_pressed()
{
    if(ui->singleSetModeTab->currentIndex())
    {
        PassTor(0, 0, 0, 0, 0, -ui->torFInput->text().toDouble());
    }
    else
    {
        PassVel(0, 0, 0, 0, 0, -ui->velFInput->text().toDouble());
    }
}

void ControlTab::on_Fgathered_released()
{
    PassZero();
}

void ControlTab::on_VelSlider_valueChanged(int value)
{
    double vel = value / 400.0 * groupVelUpperBound;
    ui->actualVel->setText(QString::number(vel,'g', 2));
    groupVel = vel;
    if(dir != Direction::stop)
    {        
        double val = static_cast<int>(dir) * vel;
        if(flag1 && flag2)
            PassVel(val, val, val, val, val, val);
        else if(flag1 && !flag2)
            PassVel(val,val,val,0,0,0);
        else if(!flag1 && flag2)
            PassVel(0,0,0,val,val,val);
    }
}

void ControlTab::on_torVelSlider_valueChanged(int value)
{
    double vel = value/ 400.0 * velLimitUpperBound;
    ui->actualVelLimit->setText(QString::number(vel, 'g', 2));
    velLimit = vel;
    if(dir != Direction::stop)
    {
        //TODO:
        // 其实这里可以看出没必要传值PassVal系列函数
        // 因为其捕获了this
        // void(void)
        double val = static_cast<int>(dir) * groupTor;
        if(flag1 && flag2)
            PassTor(val, val, val, val, val, val);
        else if(flag1 && !flag2)
            PassTor(val,val,val,0,0,0);
        else if(!flag1 && flag2)
            PassTor(0,0,0,val,val,val);
    }
}

void ControlTab::on_torSlider_valueChanged(int value)
{
    double tor = static_cast<double>(value) / ui->torSlider->maximum() * groupTorUpperBound;
    ui->actualTor->setText(QString::number(tor, 'f', 2));
    groupTor = tor;
    if(dir != Direction::stop)
    {
        double val = static_cast<int>(dir) * groupTor;
        if(flag1 && flag2)
            PassTor(val, val, val, val, val, val);
        else if(flag1 && !flag2)
            PassTor(val,val,val,0,0,0);
        else if(!flag1 && flag2)
            PassTor(0,0,0,val,val,val);
    }
}

void ControlTab::LockSlider(bool flag)
{
    ui->groupSetModeTab->setEnabled(!flag);
    ui->tubeExtensionButton->setEnabled(!flag);
    ui->tubeGatheredButton->setEnabled(!flag);
    ui->pointExtensionButton->setEnabled(!flag);
    ui->pointGatheredButton->setEnabled(!flag);
}

void ControlTab::ReceiveDirection(Direction dir)
{
    ControlTab::dir = dir;
}

void ControlTab::on_checkABC_stateChanged(int arg1)
{
    flag1 = arg1? true : false;
    emit SendABCFlag(flag1);
}


void ControlTab::on_checkDEF_stateChanged(int arg1)
{
    flag2 = arg1? true : false;
    emit SendDEFFlag(flag2);
}

