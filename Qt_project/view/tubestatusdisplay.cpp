#include "tubestatusdisplay.h"
#include "ui_tubestatusdisplay.h"

TubeStatusDisplay::TubeStatusDisplay(QWidget *parent) :
    QGroupBox(parent),
    ui(new Ui::TubeStatusDisplay),
    mApp(tubeControlSystemApp::instance())
{
    ui->setupUi(this);

    connect(mApp->tubemotionController, &tubeMotionController::PassX,
            this, &TubeStatusDisplay::ReceiveReachedX);

}

TubeStatusDisplay::~TubeStatusDisplay()
{
    delete ui;
}


/******************************************
 *            Slot Function
 *
 *
 * ****************************************/
void TubeStatusDisplay::ReceiveTubeState(const int state)
{
    switch(state)
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
        break;
    default:
        QMessageBox::information(NULL, "状态错误", "检查ReceiveTubeState的信号函数");
        break;
    }
}

void TubeStatusDisplay::ReceiveReachedX(double x)
{
    int val = static_cast<int>(x *0.001 * 0.0666666666667);
    ui->progressBar->setValue(std::max(0, std::min(val, 100)));
    // x / 1000.0 / 15.0;
}
