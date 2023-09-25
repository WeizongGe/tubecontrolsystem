#include "tubeconttrolbox.h"
#include "ui_tubeconttrolbox.h"

const static QString BackGound = "background-color: rgb";

tubeconttrolBox::tubeconttrolBox(QWidget *parent) :
    QGroupBox(parent),
    ui(new Ui::tubeconttrolBox),
    m_app(tubeControlSystemApp::instance()),
    singleVel(0), singleTor(0), groupVel(0), groupTor(0)
{
    ui->setupUi(this);
    // 设置数据库页面
    QString dbDirPath = QCoreApplication::applicationDirPath() + "/database";
    QDir dbDir(dbDirPath);
    for (QString dbFileName : dbDir.entryList()) {
        if (dbFileName == "." || dbFileName == "..") continue;
        ui->databasesComboBox->addItem(dbFileName);
    }
    ui->exportFilePathEdit->setText(QCoreApplication::applicationDirPath() + "/data.csv");

    PassVel = [this](qreal a, qreal b, qreal c){
        if(LOCKED()){
            m_app->tubemotionController->PVmodeSetVel(a * ToPassVal, b * ToPassVal, c * ToPassVal);
        }
        else
        {
            QMessageBox::information(NULL, QStringLiteral("未锁定"), QStringLiteral("请先锁定再启动"),
                                 QMessageBox::Yes | QMessageBox::No, QMessageBox::Yes);
        }};

    PassTor = [this](qreal a, qreal b, qreal c){
        if(LOCKED()){
            m_app->tubemotionController->CSTmodeSetTor(a * ToMMNM, b * ToMMNM, c * ToMMNM);
        }
        else
        {
            QMessageBox::information(NULL, QStringLiteral("未锁定"), QStringLiteral("请先锁定再启动"),
                                 QMessageBox::Yes | QMessageBox::No, QMessageBox::Yes);
        }};

    connect(m_app->tubemotionController, &tubeMotionController::passReceive,
            this, &tubeconttrolBox::ReceiveCommand, Qt::DirectConnection);

    //connect(this, &tubeconttrolBox::startReadMotor,
    //        m_app->tubemotionController, &tubeMotionController::readParameter);
    //connect(this, &tubeconttrolBox::RequestSetZero,
    //        m_app->sensorDataCollector, &SensorDataCollector::SetZero, Qt::DirectConnection);
    //connect(m_app->sensorDataCollector, &SensorDataCollector::ontubeMotionUpdate,
    //        this, &tubeconttrolBox::updatetubeMotion);// 连接力传感器更新的信号

    //connect(m_app->tubemotionController, &tubeMotionController::PassX,
    //        this, &tubeconttrolBox::ReceiveReachedX, Qt::DirectConnection);



}

tubeconttrolBox::~tubeconttrolBox()
{
    delete ui;
}

void tubeconttrolBox::on_globalStartButton_clicked()
{
    if(!CAN_STARTED)
    {
        if(m_app->globalStart())
        {
            ui->globalStartButton->setStyleSheet("background-color: rgb(0,255,0)");
            ui->globalStartButton->setText("关闭设备");
            on_tabModeWidget_currentChanged(ui->tabModeWidget->currentIndex());
            EnableSensorButton();
            EnableDriverButton();
            CAN_STARTED = true;
        }
        else
        {
            QMessageBox::information(NULL, "打开设备失败", "请检查硬件连接，特别注意USBCAN设备是否连接正确或未被占用");
            ui->globalStartButton->setStyleSheet("background-color: rgb(255,0,0)");
        }
    }
    else
    {
        globalStop();
        DisableSensorButton();
        ui->globalStartButton->setText("启动设备");
    }
}

void tubeconttrolBox::globalStop()
{
    if(SENSOR_STARTED())
    {
        on_sensorLinkButton_clicked();
    }
    m_app->globalStop();
    ui->globalStartButton->setStyleSheet("background-color:rgb(220,220,220)");
    DisableDriverButton();
    CAN_STARTED = false;
}

void tubeconttrolBox::on_deviceCloseButton_clicked()
{
    m_app->tubemotionController->changeStartStatus(false);
    m_app->tubemotionController->Stopdrivers();
    EnableDriverButton();
}

void tubeconttrolBox::on_deviceOpenButton_clicked()
{
    m_app->tubemotionController->changeStartStatus(true);
    m_app->tubemotionController->restartdrivers();
    EnableDriverButton();
}

void tubeconttrolBox::on_sensorLinkButton_clicked()
{
    m_app->sensorDataCollector->ch1_statechanged();
    if(m_app->sensorDataCollector->STARTED())
    {
         ui->sensorLinkButton->setText("断开连接");
         emit m_app->startReadSendData();
    }
    else
    {
        ui->sensorLinkButton->setText("连接并启动");
    }
}

void tubeconttrolBox::on_sensorSetZeroButton_clicked()
{
    emit RequestSetZero();
}

void tubeconttrolBox::EnableDriverButton()
{
    ui->deviceCloseButton->setEnabled(MOTOR_STARTED());
    ui->deviceOpenButton->setEnabled(!MOTOR_STARTED());
    if(MOTOR_STARTED()) emit startReadMotor();
}

void tubeconttrolBox::DisableDriverButton()
{
    ui->deviceCloseButton->setEnabled(false);
    ui->deviceOpenButton->setEnabled(false);
}

void tubeconttrolBox::EnableSensorButton()
{
    ui->sensorLinkButton->setEnabled(true);
    ui->sensorSetZeroButton->setEnabled(true);
}

void tubeconttrolBox::DisableSensorButton()
{
    ui->sensorLinkButton->setEnabled(false);
    ui->sensorSetZeroButton->setEnabled(false);
}

qreal tubeconttrolBox::move_limit(qreal input, qreal low_limit, qreal high_limit, QLineEdit* pInput)
{
    if(input < low_limit)
    {
        QMessageBox::warning(NULL, QStringLiteral("警告"), QStringLiteral("输入值过小,已为您重新赋值"),
                             QMessageBox::Yes | QMessageBox::No, QMessageBox::Yes);
        pInput->setText(QString::number(low_limit));
        return low_limit;
    }
    else if(input > high_limit)
    {
        QMessageBox::warning(NULL, QStringLiteral("警告"), QStringLiteral("输入值过大,已为您重新赋值"),
                             QMessageBox::Yes | QMessageBox::No, QMessageBox::Yes);
        pInput->setText(QString::number(high_limit));
        return high_limit;
    }
    else
        return input;
}

qreal tubeconttrolBox::vel_limit(qreal i, QLineEdit* pInput)
{
    return move_limit(i, LOWER_LIMIT, VEL_UPPER_LIMIT, pInput);
}

qreal tubeconttrolBox::tor_limit(qreal i, QLineEdit* pInput)
{
    return move_limit(i, LOWER_LIMIT, TOR_UPPER_LIMIT, pInput);
}

///
/// \brief tubeconttrolBox::on_SingleOkTorButton_clicked
/// \def 设置三个电机的速度参数
void tubeconttrolBox::on_singleVelLock_clicked()
{
    singleVel.A = vel_limit(ui->velAInput->text().toDouble(), ui->velAInput);
    singleVel.B = vel_limit(ui->velBInput->text().toDouble(), ui->velBInput);
    singleVel.C = vel_limit(ui->velCInput->text().toDouble(), ui->velCInput);
    ChangeVelInputState();
}

void tubeconttrolBox::on_singleTorLock_clicked()
{
    singleTor.A =  tor_limit(ui->torAInput->text().toDouble(), ui->torAInput);
    singleTor.B =  tor_limit(ui->torBInput->text().toDouble(), ui->torBInput);
    singleTor.C =  tor_limit(ui->torCInput->text().toDouble(), ui->torCInput);
    ChangeTorInputState();
}

void tubeconttrolBox::on_groupVelLock_clicked()
{
    groupVel = vel_limit(ui->groupVelInput->text().toDouble(), ui->groupVelInput);
    ChangeGroupVelInputState();
}

void tubeconttrolBox::on_groupTorLock_clicked()
{
    groupTor = tor_limit(ui->groupTorInput->text().toDouble(), ui->groupTorInput);
    ChangeGroupTorInputState();
}

///
/// \brief tubeconttrolBox::ChageVelInputState
/// \def 改变速度输入状态栏
void tubeconttrolBox::ChangeVelInputState()
{

    bool Lock =ui->velAInput->isReadOnly();
    ui->velAInput->setReadOnly(!Lock);
    ui->velBInput->setReadOnly(!Lock);
    ui->velCInput->setReadOnly(!Lock);

    QString color = Lock?"(255, 255, 255)":"(200, 200, 200)";
    ui->velAInput->setStyleSheet(BackGound + color);
    ui->velBInput->setStyleSheet(BackGound + color);
    ui->velCInput->setStyleSheet(BackGound + color);

    QString text = Lock?"锁定":"解锁";
    ui->singleVelLock->setText(text);
}
///
/// \brief tubeconttrolBox::ChangeTorInputState
/// 这里和上面累赘，得想办法二合一
void tubeconttrolBox::ChangeTorInputState()
{
    bool Lock =ui->torAInput->isReadOnly();
    ui->torAInput->setReadOnly(!Lock);
    ui->torBInput->setReadOnly(!Lock);
    ui->torCInput->setReadOnly(!Lock);

    QString color = Lock?"(255, 255, 255)":"(200, 200, 200)";
    ui->torAInput->setStyleSheet(BackGound + color);
    ui->torBInput->setStyleSheet(BackGound + color);
    ui->torCInput->setStyleSheet(BackGound + color);

    QString text = Lock?"锁定":"解锁";
    ui->singleTorLock->setText(text);
}

void tubeconttrolBox::ChangeGroupVelInputState()
{
    bool Lock =ui->groupVelInput->isReadOnly();
    ui->groupVelInput->setReadOnly(!Lock);

    QString color = Lock?"(255, 255, 255)":"(200, 200, 200)";
    ui->groupVelInput->setStyleSheet(BackGound + color);

    QString text = Lock?"锁定":"解锁";
    ui->groupVelLock->setText(text);
}

void tubeconttrolBox::ChangeGroupTorInputState()
{
    bool Lock =ui->groupTorInput->isReadOnly();
    ui->groupTorInput->setReadOnly(!Lock);

    QString color = Lock?"(255, 255, 255)":"(200, 200, 200)";
    ui->groupTorInput->setStyleSheet(BackGound + color);

    QString text = Lock?"锁定":"解锁";
    ui->groupTorLock->setText(text);
}

///
/// \brief tubeconttrolBox::on_singleSetModeTab_currentChanged
/// \param index
/// 切页改变模式设定
void tubeconttrolBox::on_singleSetModeTab_currentChanged(int index)
{
    if(m_app->tubemotionController->STARTED())
    {
        switch(index)
        {
            case 0: sMode = VelMode;
                    m_app->tubemotionController->setMotionMode(0x3);
                    break;
            case 1: sMode = TorMode;
                    m_app->tubemotionController->setMotionMode(0xA);
                    break;
        }
    }
}

void tubeconttrolBox::on_groupSetModeTab_currentChanged(int index)
{
    if(m_app->tubemotionController->STARTED())
    {
        switch(index)
        {
            case 0: gMode = VelMode;
                    m_app->tubemotionController->setMotionMode(0x3);
                    break;
            case 1: gMode = TorMode;
                    m_app->tubemotionController->setMotionMode(0xA);
                    break;
        }
    }
}

void tubeconttrolBox::on_tabModeWidget_currentChanged(int index)
{
    if(m_app->tubemotionController->STARTED())
    {
        switch(index)
        {
            case 0: on_groupSetModeTab_currentChanged(ui->groupSetModeTab->currentIndex());break;
            case 1: on_singleSetModeTab_currentChanged(ui->singleSetModeTab->currentIndex());break;
        }
    }
}
///
/// Release 有隐患，持续按着好费劲建议自己加个延时设置，点一下动一下
// ## 这里看着好啰嗦能不能省省
///
/// \brief tubeconttrolBox::on_motorApointextensionButton_pressed
/// 单点动传递电机A速度
void tubeconttrolBox::on_motorApointextensionButton_pressed()
{
    //TODO:
    //      加一个放未锁定误触
    if(sMode == VelMode)
        PassVel(singleVel.A, 0, 0);
    else
        PassTor(singleTor.A, 0, 0);
}

void tubeconttrolBox::on_motorApointextensionButton_released()
{
    PassZero();
}

void tubeconttrolBox::on_motorApointgatheredButton_pressed()
{
    if(sMode == VelMode)
        PassVel(-singleVel.A, 0, 0);
    else
        PassTor(-singleTor.A, 0, 0);
}

void tubeconttrolBox::on_motorApointgatheredButton_released()
{
    PassZero();
}

void tubeconttrolBox::on_motorBpointextensionButton_pressed()
{
    if(sMode == VelMode)
        PassVel(0, singleVel.B, 0);
    else
        PassTor(0, singleVel.B, 0);
}

void tubeconttrolBox::on_motorBpointgatheredButton_released()
{
    PassZero();
}

void tubeconttrolBox::on_motorBpointgatheredButton_pressed()
{
    if(sMode == VelMode)
        PassVel(0, -singleVel.B, 0);
    else
        PassTor(0, -singleVel.B, 0);
}

void tubeconttrolBox::on_motorBpointextensionButton_released()
{
    PassZero();
}

void tubeconttrolBox::on_motorCpointextensionButton_pressed()
{
    if(sMode == VelMode)
        PassVel(0, 0, singleVel.C);
    else
        PassTor(0, 0, singleVel.C);
}

void tubeconttrolBox::on_motorCpointextensionButton_released()
{
    PassZero();
}

void tubeconttrolBox::on_motorCpointgatheredButton_pressed()
{
    if(sMode == VelMode)
        PassVel(0, 0, -singleVel.C);
    else
        PassTor(0, 0, -singleVel.C);
}

void tubeconttrolBox::on_motorCpointgatheredButton_released()
{
    PassZero();
}
///
/// \brief tubeconttrolBox::PassZero
/// 所有停止均可复用的函数
void tubeconttrolBox::PassZero()
{
    MotorMode mode = ui->tabModeWidget->currentIndex() == 0?
                gMode:sMode;
    if(mode == VelMode)
        PassVel(0, 0, 0);
    else
        PassTor(0, 0, 0);

}

void tubeconttrolBox::on_tubeextensionButton_clicked()
{
    // 这里可以做重载改进一下
    // 即传单值等于重复传同一值
    PassGroup(gMode == VelMode?groupVel:groupTor);
}

void tubeconttrolBox::on_tubegatheredButton_clicked()
{
    PassGroup(gMode == VelMode?-groupVel:-groupTor);
}

void tubeconttrolBox::PassGroup(qreal val)
{
    if(gMode == VelMode)
        PassVel(val, val, val);
    else
        PassTor(val, val, val);
}

void tubeconttrolBox::on_stopButton_clicked()
{
    PassZero();
}

void tubeconttrolBox::on_pointextensionButton_pressed()
{
    on_tubeextensionButton_clicked();
}

void tubeconttrolBox::on_pointextensionButton_released()
{
    PassZero();
}

void tubeconttrolBox::on_pointgatheredButton_pressed()
{
    on_tubegatheredButton_clicked();
}

void tubeconttrolBox::on_pointgatheredButton_released()
{
    PassZero();
}



///
/// \brief tubeconttrolBox::on_exportButton_clicked
/// Button<导出>Call_Back
/// TODO:
///     导出数据需要大改，
///     1.无法导出数据

void tubeconttrolBox::on_exportButton_clicked()
{
    QString dbFilePath = QCoreApplication::applicationDirPath() + "/database/" + ui->databasesComboBox->currentText();
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
    qDebug() << "export data:";
    qDebug() << "db file: " << dbFilePath;
    qDebug() << "csv file: " << exportFilePath;
    qDebug() << "table: " << tableName;
    if (dbFilePath.isEmpty() || exportFilePath.isEmpty() || tableName.isEmpty()) {
        return;
    }
    tubeControlSystemApp::instance()->tubedatabase->exportData(dbFilePath, exportFilePath, tableName);
}

///
/// \brief tubeconttrolBox::on_exportFilePathBrowerButton_clicked
/// Button<浏览>Call_Back
void tubeconttrolBox::on_exportFilePathBrowerButton_clicked()
{
    QString fileName = QFileDialog::getSaveFileName(this, tr("Save File"),
                               "",
                               tr("CSV File (*.csv)"));
    if (!fileName.isEmpty()) {
        ui->exportFilePathEdit->setText(fileName);
    }
}

void tubeconttrolBox::ReceiveCommand(ZCAN_Receive_Data data)
{
    uint64_t TEXT = 0;
    for(int i = 0; i < 8; ++i)
    {
        TEXT|= (uint64_t)data.frame.data[i] << (8 * (7 - i));
    }
    uint16_t id = GET_ID(data.frame.can_id);
    ui->ReceiveCommand->setText("0x" + QString::number(id, 16)
                                +" : " + QString::number(TEXT, 16));
}

///
/// \brief tubeconttrolBox::LOCKED
/// \return
/// 这里写的不好，最好设置Widget组的抽象
/// 可以统一划定Widget接口
bool tubeconttrolBox::LOCKED()
{
    if(ui->tabModeWidget->currentIndex() == 0)
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

///
/// \brief tubeconttrolBox::on_canSendButton_clicked
/// 该函数存在越权行为，
/// 调用了很多can命令，
/// 后续有待封装处理
void tubeconttrolBox::on_canSendButton_clicked()
{
    static auto hexToDec = [](QString s){
        int num = 0;
        for(auto a: s)
        {
            num = num * 16 + (a> 'A'?a.toLower().unicode() - 'a'+10: a.unicode() - '0');
        }
        return num;
    };

    if(m_app->tubemotionController->STARTED())
    {
        ZCAN_Transmit_Data data;
        memset(&data, 0, sizeof(data));
        data.frame.can_id = MAKE_CAN_ID(hexToDec(ui->canIDInput->text()),
                                        ui->EFFInput->text().toInt(), 0, 0);
        data.frame.can_dlc = CAN_MAX_DLEN;
        data.frame.data[0] = hexToDec(ui->data1Input->text());
        data.frame.data[1] = hexToDec(ui->data2Input->text());
        data.frame.data[2] = hexToDec(ui->data3Input->text());
        data.frame.data[3] = hexToDec(ui->data4Input->text());
        data.frame.data[4] = hexToDec(ui->data5Input->text());
        data.frame.data[5] = hexToDec(ui->data6Input->text());
        data.frame.data[6] = hexToDec(ui->data7Input->text());
        data.frame.data[7] = hexToDec(ui->data8Input->text());
        if (ZCAN_Transmit(m_app->tubemotionController->CH(), &data, 1) <= 0)
        {
            ui->canIDInput->setText("传输数据失败！");
        }
        else
        {
            ZCAN_Receive_Data can_frame[50];
            if (ZCAN_GetReceiveNum(m_app->tubemotionController->CH(), TYPE_CAN))
            {
                uint len = ZCAN_Receive(m_app->tubemotionController->CH(), &can_frame[0], 50, 100);
                for(uint i = 0; i < len; ++i)
                {
                    uint id = GET_ID(can_frame[i].frame.can_id);
                    if(id == 0x581)
                    {
                        ReceiveCommand(can_frame[i]);
                        break;
                    }
                }
            }
            else
            {
                ui->ReceiveCommand->setText("没有任何返回值！");
            }
        }
    }
    else
    {
        QMessageBox::information(NULL, QStringLiteral("未启动CAN"), QStringLiteral("请点击启动按钮且显示绿色"),
                             QMessageBox::Yes | QMessageBox::No, QMessageBox::Yes);
    }
}

void tubeconttrolBox::updatetubeMotion(const int tube_state)
{
    switch(tube_state)
    {
    case 0:
        ui->signalLamp1->setIcon(QIcon("Image/red.png"));
        break;
    case 1:
        ui->signalLamp1->setIcon(QIcon("Image/green.png"));
        ui->signalLamp2->setIcon(QIcon("Image/red.png"));
        break;
    case 2:
        ui->signalLamp2->setIcon(QIcon("Image/green.png"));
        ui->signalLamp3->setIcon(QIcon("Image/red.png"));
        break;
    case 3:
        ui->signalLamp3->setIcon(QIcon("Image/green.png"));
        ui->signalLamp4->setIcon(QIcon("Image/red.png"));
        break;
    case 4:
        ui->signalLamp4->setIcon(QIcon("Image/green.png"));
        ui->signalLamp5->setIcon(QIcon("Image/red.png"));
        break;
    case 5:
        ui->signalLamp5->setIcon(QIcon("Image/green.png"));
        m_app->tubemotionController->Stopdrivers();
        break;

    default:
        qDebug()<<"展开到位信息未成功接受";
        break;
    }
}

void tubeconttrolBox::ReceiveReachedX(double ix)
{
    reachedX = ix / 1000.0 / 15.0;
    ui->progressBar->setValue(reachedX);
}
