#include "msgboxer.h"
#include "ui_msgboxer.h"

MsgBoxer::MsgBoxer(QWidget *parent) :
    QGroupBox(parent),
    ui(new Ui::MsgBoxer),
    mApp(tubeControlSystemApp::instance()),
    msgLogger()
{
    ui->setupUi(this);

    msgThread = new QThread(this);
    msgLogger.moveToThread(msgThread);
    connect(msgThread, &QThread::finished, &msgLogger, &DebugLogger::deleteLater);
    connect(&msgLogger, &DebugLogger::AddItem,
            this, &MsgBoxer::AddItem, Qt::DirectConnection);
    connect(mApp->tubemotionController, &tubeMotionController::Logger,
            &msgLogger, &DebugLogger::ReceiveMsg);
    connect(mApp->sensorDataCollector, &SensorDataCollector::Logger,
            &msgLogger, &DebugLogger::ReceiveMsg);
    connect(this, &MsgBoxer::ClearExtremum,
            mApp->sensorDataCollector, &SensorDataCollector::ResetExtremum, Qt::DirectConnection);

    msgThread->start();
}

MsgBoxer::~MsgBoxer()
{
    msgThread->quit();
    msgThread->wait();
    delete ui;

}

void MsgBoxer::AddItem(const QString & item)
{
    mutex.lock();

    ui->listWidget->addItem(item);
    if(Size() > 10)
    {
        ui->listWidget->takeItem(0);
        //找移除函数
    }
    mutex.unlock();
}

int MsgBoxer::Size()
{
    return ui->listWidget->count();
}

void MsgBoxer::on_clearButton_clicked()
{
    mutex.lock();
    ui->listWidget->clear();
    emit ClearExtremum();
    mutex.unlock();
}


