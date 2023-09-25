#include "motorstatusshowgroupbox.h"
#include "ui_motorstatusshowgroupbox.h"
#include <QToolButton>
#include <synchapi.h>

motorstatusshowGroupBox::motorstatusshowGroupBox(QWidget *parent) :
    QGroupBox(parent),
    ui(new Ui::motorstatusshowGroupBox),
    m_app(tubeControlSystemApp::instance())
{
    ui->setupUi(this);

    initAChart();
    initBChart();
    initCChart();
    initDChart();
    initEChart();
    initFChart();
    initTubeChart();

    text_display_num = 0;

    connect(m_app->sensorDataCollector, &SensorDataCollector::SensorDataUpdated,
            this, &motorstatusshowGroupBox::updateSensorData, Qt::DirectConnection);// 连接力传感器更新的信号
    connect(m_app->sensorDataCollector, &SensorDataCollector::SendLevel,
            this, &motorstatusshowGroupBox::updateLevelSignals, Qt::DirectConnection);
    connect(m_app->sensorDataCollector, &SensorDataCollector::SendDeviation,
            this, &motorstatusshowGroupBox::updateDeviation, Qt::DirectConnection);
    replace_num=0;
    connect(m_app->tubemotionController, &tubeMotionController::tubemotionParameterUpdated,
            this, &motorstatusshowGroupBox::updatetubeMotionParameter, Qt::DirectConnection);

    connect(this, &motorstatusshowGroupBox::SendDevset,
            m_app->sensorDataCollector,&SensorDataCollector::GetDeviation);
    connect(this, &motorstatusshowGroupBox::SendDevvec,
            m_app->sensorDataCollector,&SensorDataCollector::GetDevVector);

    // Setting Thread
    DrawMotorThread = new QThread(this);
    connect(DrawMotorThread,  &QThread::finished, this, &QObject::deleteLater);
    DrawMotorThread->start();


}

motorstatusshowGroupBox::~motorstatusshowGroupBox()
{
    DrawMotorThread->quit();
    DrawMotorThread->wait();
    delete ui;
}

void motorstatusshowGroupBox::updatetubeMotionParameter(tubeMotionParameter mp)
{

    text_display_num++;
    // 更新数值显示
    if (text_display_num == 5)
    {
        if(m_AVelocitySeries->count() > 200)
        {
            m_AVelocitySeries->removePoints(0, 1);
            m_BVelocitySeries->removePoints(0, 1);
            m_CVelocitySeries->removePoints(0, 1);
            m_DVelocitySeries->removePoints(0, 1);
            m_EVelocitySeries->removePoints(0, 1);
            m_FVelocitySeries->removePoints(0, 1);
        }
        // 更新曲线图
        m_AVelocitySeries->append(mp.time, mp.velocityA);
        m_BVelocitySeries->append(mp.time, mp.velocityB);
        m_CVelocitySeries->append(mp.time, mp.velocityC);
        m_DVelocitySeries->append(mp.time, mp.velocityD);
        m_EVelocitySeries->append(mp.time, mp.velocityE);
        m_FVelocitySeries->append(mp.time, mp.velocityF);


        m_ATorqueSeries->append(mp.time, mp.torqueA);
        m_BTorqueSeries->append(mp.time, mp.torqueB);
        m_CTorqueSeries->append(mp.time, mp.torqueC);
        m_DTorqueSeries->append(mp.time, mp.torqueD);
        m_ETorqueSeries->append(mp.time, mp.torqueE);
        m_FTorqueSeries->append(mp.time, mp.torqueF);

        m_ACurrentSeries->append(mp.time, mp.currentA);
        m_BCurrentSeries->append(mp.time, mp.currentB);
        m_CCurrentSeries->append(mp.time, mp.currentC);
        m_DCurrentSeries->append(mp.time, mp.currentD);
        m_ECurrentSeries->append(mp.time, mp.currentE);
        m_FCurrentSeries->append(mp.time, mp.currentF);

        // 实现横轴随时间滚动
        // 当前时间映射到绘图区域的坐标
        qreal AtimePosition = m_Achart->mapToPosition(QPointF(mp.time, 0)).x();
        qreal BtimePosition = m_Bchart->mapToPosition(QPointF(mp.time, 0)).x();
        qreal CtimePosition = m_Cchart->mapToPosition(QPointF(mp.time, 0)).x();
        qreal DtimePosition = m_Dchart->mapToPosition(QPointF(mp.time, 0)).x();
        qreal EtimePosition = m_Echart->mapToPosition(QPointF(mp.time, 0)).x();
        qreal FtimePosition = m_Fchart->mapToPosition(QPointF(mp.time, 0)).x();

        // 当前绘图区域最右侧的坐标
        qreal ArightPosition = m_Achart->plotArea().topRight().x();
        qreal BrightPosition = m_Achart->plotArea().topRight().x();
        qreal CrightPosition = m_Achart->plotArea().topRight().x();
        qreal DrightPosition = m_Achart->plotArea().topRight().x();
        qreal ErightPosition = m_Achart->plotArea().topRight().x();
        qreal FrightPosition = m_Achart->plotArea().topRight().x();

        // 当前时间超出绘图区域右侧时滚动
        auto charts = {std::make_pair((AtimePosition - ArightPosition), m_Achart),
                       std::make_pair((BtimePosition - BrightPosition), m_Bchart),
                       std::make_pair((CtimePosition - CrightPosition), m_Cchart),
                       std::make_pair((DtimePosition - DrightPosition), m_Dchart),
                       std::make_pair((EtimePosition - ErightPosition), m_Echart),
                       std::make_pair((FtimePosition - FrightPosition), m_Fchart)};
        for(auto & chart: charts)
        {
            if(chart.first > 0)
            {
                chart.second->scroll(chart.first, 0);
            }
        }

        ui->AVelocitycheckBox->setText(QString::number(mp.velocityA, 'f', 2));
        ui->BVelocitycheckBox->setText(QString::number(mp.velocityB, 'f', 2));
        ui->CVelocitycheckBox->setText(QString::number(mp.velocityC, 'f', 2));
        ui->DVelocitycheckBox->setText(QString::number(mp.velocityD, 'f', 2));
        ui->EVelocitycheckBox->setText(QString::number(mp.velocityE, 'f', 2));
        ui->FVelocitycheckBox->setText(QString::number(mp.velocityF, 'f', 2));

        ui->ATorquecheckBox->setText(QString::number(mp.torqueA, 'f', 2));
        ui->BTorquecheckBox->setText(QString::number(mp.torqueB, 'f', 2));
        ui->CTorquecheckBox->setText(QString::number(mp.torqueC, 'f', 2));
        ui->DTorquecheckBox->setText(QString::number(mp.torqueD, 'f', 2));
        ui->ETorquecheckBox->setText(QString::number(mp.torqueE, 'f', 2));
        ui->FTorquecheckBox->setText(QString::number(mp.torqueF, 'f', 2));


        ui->ACurrentcheckBox->setText(QString::number(mp.currentA, 'f', 2));
        ui->BCurrentcheckBox->setText(QString::number(mp.currentB, 'f', 2));
        ui->CCurrentcheckBox->setText(QString::number(mp.currentC, 'f', 2));
        ui->DCurrentcheckBox->setText(QString::number(mp.currentD, 'f', 2));
        ui->ECurrentcheckBox->setText(QString::number(mp.currentE, 'f', 2));
        ui->FCurrentcheckBox->setText(QString::number(mp.currentF, 'f', 2));


        auto enableIcons = {std::make_pair(mp.enableA, ui->AEnableButton),
                            std::make_pair(mp.enableB, ui->BEnableButton),
                            std::make_pair(mp.enableC, ui->CEnableButton),
                            std::make_pair(mp.enableD, ui->DEnableButton),
                            std::make_pair(mp.enableE, ui->EEnableButton),
                            std::make_pair(mp.enableF, ui->FEnableButton)};
        for(auto & icon: enableIcons)
        {
            if(icon.first)
            {
                icon.second->setIcon(QIcon("Image/green.png"));
            }
            else
            {
                icon.second->setIcon(QIcon("Image/red.png"));
            }
        }

        SetSignalLamp({ui->AExtensionButton,
                       ui->AGatheredButton }, mp.directionA);
        SetSignalLamp({ui->BExtensionButton,
                       ui->BGatheredButton }, mp.directionB);
        SetSignalLamp({ui->CExtensionButton,
                       ui->CGatheredButton }, mp.directionC);
        SetSignalLamp({ui->DExtensionButton,
                       ui->DGatheredButton }, mp.directionD);
        SetSignalLamp({ui->EExtensionButton,
                       ui->EGatheredButton }, mp.directionE);
        SetSignalLamp({ui->FExtensionButton,
                       ui->FGatheredButton }, mp.directionF);
        text_display_num = 0;
    }
//    QWidget::update();
    Sleep(20);
}

void motorstatusshowGroupBox::SetSignalLamp(QList<QAbstractButton *> buttons, int val)
{
    if(val == 1)
    {
        buttons[0]->setIcon(QIcon("Image/green.png"));
        buttons[1]->setIcon(QIcon("Image/red.png"));
    }
    else if(val == -1)
    {
        buttons[0]->setIcon(QIcon("Image/red.png"));
        buttons[1]->setIcon(QIcon("Image/green.png"));
    }
    else
    {
        buttons[0]->setIcon(QIcon("Image/red.png"));
        buttons[1]->setIcon(QIcon("Image/red.png"));
    }
}

void motorstatusshowGroupBox::showEvent(QShowEvent *event)
{
    setAttribute(Qt::WA_Mapped);
    QWidget::showEvent(event);
}
/*
 * 初始化图表部件
 */
void motorstatusshowGroupBox::initAChart()
{
    m_Achart = new QChart();
    m_Achart->legend()->setAlignment(Qt::AlignBottom);
    QFont font = m_Achart->legend()->font();
    font.setPointSizeF(10);
    m_Achart->legend()->setFont(font);
    m_Achart->legend()->setVisible(false);
    ui->MotorAParameterGraphChartView->setChart(m_Achart);
    ui->MotorAParameterGraphChartView->setRenderHint(QPainter::Antialiasing);

    // 时间轴
    m_axisAX = new QValueAxis(this);
    m_axisAX->setRange(0, 60);
    m_Achart->addAxis(m_axisAX, Qt::AlignBottom);

    // 速度坐标轴
    m_axisVelAY = new QValueAxis(this);
    m_axisVelAY->setRange(-10, 10);
    m_Achart->addAxis(m_axisVelAY, Qt::AlignRight);

    // 力矩坐标轴
    m_axistorAY = new QValueAxis(this);
    m_axistorAY->setRange(-2000, 2000);
    m_Achart->addAxis(m_axistorAY, Qt::AlignLeft);

//    // 电流坐标轴
    m_axiscurAY = new QValueAxis(this);
    m_axiscurAY->setRange(-10, 10);
    //m_Achart->addAxis(m_axiscurAY, Qt::AlignLeft);

    // 速度曲线
    m_AVelocitySeries = new QLineSeries(this);
    m_AVelocitySeries->setName("Vel A");
    m_AVelocitySeries->setVisible(ui->AVelocitycheckBox->isChecked());
    m_Achart->addSeries(m_AVelocitySeries);
    m_AVelocitySeries->attachAxis(m_axisAX);
    m_AVelocitySeries->attachAxis(m_axisVelAY);

    // 力矩曲线
    m_ATorqueSeries = new QLineSeries(this);
    m_ATorqueSeries->setName("Tor A");
    m_ATorqueSeries->setVisible(ui->ATorquecheckBox->isChecked());
    m_Achart->addSeries(m_ATorqueSeries);
    m_ATorqueSeries->attachAxis(m_axisAX);
    m_ATorqueSeries->attachAxis(m_axistorAY);

    // 电流曲线
    m_ACurrentSeries = new QLineSeries(this);
    m_ACurrentSeries->setName("Cur A");
    m_ACurrentSeries->setVisible(ui->ACurrentcheckBox->isChecked());
    m_Achart->addSeries(m_ACurrentSeries);
    m_ACurrentSeries->attachAxis(m_axisAX);
    m_ACurrentSeries->attachAxis(m_axisVelAY);
}

void motorstatusshowGroupBox::initBChart()
{
    m_Bchart = new QChart();
    m_Bchart->legend()->setAlignment(Qt::AlignLeading);
    QFont font = m_Bchart->legend()->font();
    font.setPointSizeF(8);
    m_Bchart->legend()->setFont(font);
    m_Bchart->legend()->setVisible(false);
    ui->MotorBParameterGraphChartView->setChart(m_Bchart);
    ui->MotorBParameterGraphChartView->setRenderHint(QPainter::Antialiasing);

    // 时间轴
    m_axisBX = new QValueAxis(this);
    m_axisBX->setRange(0, 60);
    m_Bchart->addAxis(m_axisBX, Qt::AlignBottom);

    // 速度坐标轴
    m_axisVelBY = new QValueAxis(this);
    m_axisVelBY->setRange(-10, 10);
    m_Bchart->addAxis(m_axisVelBY, Qt::AlignRight);

    // 力矩坐标轴
    m_axistorBY = new QValueAxis(this);
    m_axistorBY->setRange(-2000, 2000);
    m_Bchart->addAxis(m_axistorBY, Qt::AlignLeft);

    // 电流坐标轴
    m_axiscurBY = new QValueAxis(this);
    m_axiscurBY->setRange(-10, 10);

    // 速度曲线
    m_BVelocitySeries = new QLineSeries(this);
    m_BVelocitySeries->setName("Vel B");
    m_BVelocitySeries->setVisible(ui->BVelocitycheckBox->isChecked());
    m_Bchart->addSeries(m_BVelocitySeries);
    m_BVelocitySeries->attachAxis(m_axisBX);
    m_BVelocitySeries->attachAxis(m_axisVelBY);

    // 力矩曲线
    m_BTorqueSeries = new QLineSeries(this);
    m_BTorqueSeries->setName("Tor B");
    m_BTorqueSeries->setVisible(ui->BTorquecheckBox->isChecked());
    m_Bchart->addSeries(m_BTorqueSeries);
    m_BTorqueSeries->attachAxis(m_axisBX);
    m_BTorqueSeries->attachAxis(m_axistorBY);

    // 电流曲线
    m_BCurrentSeries = new QLineSeries(this);
    m_BCurrentSeries->setName("Cur B");
    m_BCurrentSeries->setVisible(ui->BCurrentcheckBox->isChecked());
    m_Bchart->addSeries(m_BCurrentSeries);
    m_BCurrentSeries->attachAxis(m_axisBX);
    m_BCurrentSeries->attachAxis(m_axisVelBY);
}

void motorstatusshowGroupBox::initCChart()
{
    m_Cchart = new QChart();
    m_Cchart->legend()->setAlignment(Qt::AlignBottom);
    QFont font = m_Cchart->legend()->font();
    font.setPointSizeF(10);
    m_Cchart->legend()->setFont(font);
    m_Cchart->legend()->setVisible(false);
    ui->MotorCParameterGraphChartView->setChart(m_Cchart);
    ui->MotorCParameterGraphChartView->setRenderHint(QPainter::Antialiasing);

    // 时间轴
    m_axisCX = new QValueAxis(this);
    m_axisCX->setRange(0, 60);
    m_Cchart->addAxis(m_axisCX, Qt::AlignBottom);

    // 速度坐标轴
    m_axisVelCY = new QValueAxis(this);
    m_axisVelCY->setRange(-10, 10);
    m_Cchart->addAxis(m_axisVelCY, Qt::AlignRight);

    // 力矩坐标轴
    m_axistorCY = new QValueAxis(this);
    m_axistorCY->setRange(-2000, 2000);
    m_Cchart->addAxis(m_axistorCY, Qt::AlignLeft);

    // 电流坐标轴
    m_axiscurCY = new QValueAxis(this);
    m_axiscurCY->setRange(-10, 10);

    // 速度曲线
    m_CVelocitySeries = new QLineSeries(this);
    m_CVelocitySeries->setName("Vel C");
    m_CVelocitySeries->setVisible(ui->CVelocitycheckBox->isChecked());
    m_Cchart->addSeries(m_CVelocitySeries);
    m_CVelocitySeries->attachAxis(m_axisCX);
    m_CVelocitySeries->attachAxis(m_axisVelCY);

    // 力矩曲线
    m_CTorqueSeries = new QLineSeries(this);
    m_CTorqueSeries->setName("Tor C");
    m_CTorqueSeries->setVisible(ui->CTorquecheckBox->isChecked());
    m_Cchart->addSeries(m_CTorqueSeries);
    m_CTorqueSeries->attachAxis(m_axisCX);
    m_CTorqueSeries->attachAxis(m_axistorCY);

    // 电流曲线
    m_CCurrentSeries = new QLineSeries(this);
    m_CCurrentSeries->setName("Cur C");
    m_CCurrentSeries->setVisible(ui->CCurrentcheckBox->isChecked());
    m_Cchart->addSeries(m_CCurrentSeries);
    m_CCurrentSeries->attachAxis(m_axisCX);
    m_CCurrentSeries->attachAxis(m_axisVelCY);
}

void motorstatusshowGroupBox::initDChart()
{
    m_Dchart = new QChart();
    m_Dchart->legend()->setAlignment(Qt::AlignBottom);
    QFont font = m_Dchart->legend()->font();
    font.setPointSizeF(10);
    m_Dchart->legend()->setFont(font);
    m_Dchart->legend()->setVisible(false);
    ui->MotorDParameterGraphChartView->setChart(m_Dchart);
    ui->MotorDParameterGraphChartView->setRenderHint(QPainter::Antialiasing);

    // 时间轴
    m_axisDX = new QValueAxis(this);
    m_axisDX->setRange(0, 60);
    m_Dchart->addAxis(m_axisDX, Qt::AlignBottom);

    // 速度坐标轴
    m_axisVelDY = new QValueAxis(this);
    m_axisVelDY->setRange(-10, 10);
    m_Dchart->addAxis(m_axisVelDY, Qt::AlignRight);

    // 力矩坐标轴
    m_axistorDY = new QValueAxis(this);
    m_axistorDY->setRange(-2000, 2000);
    m_Dchart->addAxis(m_axistorDY, Qt::AlignLeft);

    // 电流坐标轴
    m_axiscurDY = new QValueAxis(this);
    m_axiscurDY->setRange(-10, 10);

    // 速度曲线
    m_DVelocitySeries = new QLineSeries(this);
    m_DVelocitySeries->setName("Vel D");
    m_DVelocitySeries->setVisible(ui->DVelocitycheckBox->isChecked());
    m_Dchart->addSeries(m_DVelocitySeries);
    m_DVelocitySeries->attachAxis(m_axisDX);
    m_DVelocitySeries->attachAxis(m_axisVelDY);

    // 力矩曲线
    m_DTorqueSeries = new QLineSeries(this);
    m_DTorqueSeries->setName("Tor D");
    m_DTorqueSeries->setVisible(ui->DTorquecheckBox->isChecked());
    m_Dchart->addSeries(m_DTorqueSeries);
    m_DTorqueSeries->attachAxis(m_axisDX);
    m_DTorqueSeries->attachAxis(m_axistorDY);

    // 电流曲线
    m_DCurrentSeries = new QLineSeries(this);
    m_DCurrentSeries->setName("Cur D");
    m_DCurrentSeries->setVisible(ui->DCurrentcheckBox->isChecked());
    m_Dchart->addSeries(m_DCurrentSeries);
    m_DCurrentSeries->attachAxis(m_axisDX);
    m_DCurrentSeries->attachAxis(m_axisVelDY);
}

void motorstatusshowGroupBox::initEChart()
{
    m_Echart = new QChart();
    m_Echart->legend()->setAlignment(Qt::AlignBottom);
    QFont font = m_Echart->legend()->font();
    font.setPointSizeF(10);
    m_Echart->legend()->setFont(font);
    m_Echart->legend()->setVisible(false);
    ui->MotorEParameterGraphChartView->setChart(m_Echart);
    ui->MotorEParameterGraphChartView->setRenderHint(QPainter::Antialiasing);

    // 时间轴
    m_axisEX = new QValueAxis(this);
    m_axisEX->setRange(0, 60);
    m_Echart->addAxis(m_axisEX, Qt::AlignBottom);

    // 速度坐标轴
    m_axisVelEY = new QValueAxis(this);
    m_axisVelEY->setRange(-10, 10);
    m_Echart->addAxis(m_axisVelEY, Qt::AlignRight);

    // 力矩坐标轴
    m_axistorEY = new QValueAxis(this);
    m_axistorEY->setRange(-2000, 2000);
    m_Echart->addAxis(m_axistorEY, Qt::AlignLeft);

    // 电流坐标轴
    m_axiscurEY = new QValueAxis(this);
    m_axiscurEY->setRange(-10, 10);

    // 速度曲线
    m_EVelocitySeries = new QLineSeries(this);
    m_EVelocitySeries->setName("Vel E");
    m_EVelocitySeries->setVisible(ui->EVelocitycheckBox->isChecked());
    m_Echart->addSeries(m_EVelocitySeries);
    m_EVelocitySeries->attachAxis(m_axisEX);
    m_EVelocitySeries->attachAxis(m_axisVelEY);

    // 力矩曲线
    m_ETorqueSeries = new QLineSeries(this);
    m_ETorqueSeries->setName("Tor E");
    m_ETorqueSeries->setVisible(ui->ETorquecheckBox->isChecked());
    m_Echart->addSeries(m_ETorqueSeries);
    m_ETorqueSeries->attachAxis(m_axisEX);
    m_ETorqueSeries->attachAxis(m_axistorEY);

    // 电流曲线
    m_ECurrentSeries = new QLineSeries(this);
    m_ECurrentSeries->setName("Cur E");
    m_ECurrentSeries->setVisible(ui->ECurrentcheckBox->isChecked());
    m_Echart->addSeries(m_ECurrentSeries);
    m_ECurrentSeries->attachAxis(m_axisEX);
    m_ECurrentSeries->attachAxis(m_axisVelEY);
}

void motorstatusshowGroupBox::initFChart()
{
    m_Fchart = new QChart();
    m_Fchart->legend()->setAlignment(Qt::AlignBottom);
    QFont font = m_Fchart->legend()->font();
    font.setPointSizeF(10);
    m_Fchart->legend()->setFont(font);
    m_Fchart->legend()->setVisible(false);
    ui->MotorFParameterGraphChartView->setChart(m_Fchart);
    ui->MotorFParameterGraphChartView->setRenderHint(QPainter::Antialiasing);

    // 时间轴
    m_axisFX = new QValueAxis(this);
    m_axisFX->setRange(0, 60);
    m_Fchart->addAxis(m_axisFX, Qt::AlignBottom);

    // 速度坐标轴
    m_axisVelFY = new QValueAxis(this);
    m_axisVelFY->setRange(-10, 10);
    m_Fchart->addAxis(m_axisVelFY, Qt::AlignRight);

    // 力矩坐标轴
    m_axistorFY = new QValueAxis(this);
    m_axistorFY->setRange(-2000, 2000);
    m_Fchart->addAxis(m_axistorFY, Qt::AlignLeft);

    // 电流坐标轴
    m_axiscurFY = new QValueAxis(this);
    m_axiscurFY->setRange(-10, 10);

    // 速度曲线
    m_FVelocitySeries = new QLineSeries(this);
    m_FVelocitySeries->setName("Vel F");
    m_FVelocitySeries->setVisible(ui->FVelocitycheckBox->isChecked());
    m_Fchart->addSeries(m_FVelocitySeries);
    m_FVelocitySeries->attachAxis(m_axisFX);
    m_FVelocitySeries->attachAxis(m_axisVelFY);

    // 力矩曲线
    m_FTorqueSeries = new QLineSeries(this);
    m_FTorqueSeries->setName("Tor F");
    m_FTorqueSeries->setVisible(ui->FTorquecheckBox->isChecked());
    m_Fchart->addSeries(m_FTorqueSeries);
    m_FTorqueSeries->attachAxis(m_axisFX);
    m_FTorqueSeries->attachAxis(m_axistorFY);

    // 电流曲线
    m_FCurrentSeries = new QLineSeries(this);
    m_FCurrentSeries->setName("Cur F");
    m_FCurrentSeries->setVisible(ui->FCurrentcheckBox->isChecked());
    m_Fchart->addSeries(m_FCurrentSeries);
    m_FCurrentSeries->attachAxis(m_axisFX);
    m_FCurrentSeries->attachAxis(m_axisVelFY);
}
/************************************************/
// 点击复选框改变曲线可视状态

void motorstatusshowGroupBox::on_AVelocitycheckBox_stateChanged(int arg1)
{
    m_AVelocitySeries->setVisible(arg1);
}

void motorstatusshowGroupBox::on_BVelocitycheckBox_stateChanged(int arg2)
{
    m_BVelocitySeries->setVisible(arg2);
}

void motorstatusshowGroupBox::on_CVelocitycheckBox_stateChanged(int arg3)
{
    m_CVelocitySeries->setVisible(arg3);
}

void motorstatusshowGroupBox::on_DVelocitycheckBox_stateChanged(int arg11)
{
    m_DVelocitySeries->setVisible(arg11);
}

void motorstatusshowGroupBox::on_EVelocitycheckBox_stateChanged(int arg22)
{
    m_EVelocitySeries->setVisible(arg22);
}

void motorstatusshowGroupBox::on_FVelocitycheckBox_stateChanged(int arg33)
{
    m_FVelocitySeries->setVisible(arg33);
}

void motorstatusshowGroupBox::on_ATorquecheckBox_stateChanged(int arg4)
{
    m_ATorqueSeries->setVisible(arg4);
}

void motorstatusshowGroupBox::on_BTorquecheckBox_stateChanged(int arg5)
{
    m_BTorqueSeries->setVisible(arg5);
}

void motorstatusshowGroupBox::on_CTorquecheckBox_stateChanged(int arg6)
{
    m_CTorqueSeries->setVisible(arg6);
}

void motorstatusshowGroupBox::on_DTorquecheckBox_stateChanged(int arg44)
{
    m_DTorqueSeries->setVisible(arg44);
}

void motorstatusshowGroupBox::on_ETorquecheckBox_stateChanged(int arg55)
{
    m_ETorqueSeries->setVisible(arg55);
}

void motorstatusshowGroupBox::on_FTorquecheckBox_stateChanged(int arg66)
{
    m_FTorqueSeries->setVisible(arg66);
}

void motorstatusshowGroupBox::on_ACurrentcheckBox_stateChanged(int arg7)
{
    m_ACurrentSeries->setVisible(arg7);
}

void motorstatusshowGroupBox::on_BCurrentcheckBox_stateChanged(int arg8)
{
    m_BCurrentSeries->setVisible(arg8);
}

void motorstatusshowGroupBox::on_CCurrentcheckBox_stateChanged(int arg9)
{
    m_CCurrentSeries->setVisible(arg9);
}

void motorstatusshowGroupBox::on_DCurrentcheckBox_stateChanged(int arg77)
{
    m_DCurrentSeries->setVisible(arg77);
}

void motorstatusshowGroupBox::on_ECurrentcheckBox_stateChanged(int arg88)
{
    m_ECurrentSeries->setVisible(arg88);
}

void motorstatusshowGroupBox::on_FCurrentcheckBox_stateChanged(int arg99)
{
    m_FCurrentSeries->setVisible(arg99);
}
/************************************************
                    传感器数据


************************************************/
//更新传感器数据
void motorstatusshowGroupBox::updateSensorData(Force ft)
{
    replace_num++;
    if(m_FAbuffer.size()>=200)
    {
         m_FAbuffer.pop_front();
         m_FBbuffer.pop_front();
         m_FCbuffer.pop_front();
         m_FDbuffer.pop_front();
         m_FEbuffer.pop_front();
         m_FFbuffer.pop_front();
         m_FASeries->removePoints(0, 1);
         m_FBSeries->removePoints(0, 1);
         m_FCSeries->removePoints(0, 1);
         m_FDSeries->removePoints(0, 1);
         m_FESeries->removePoints(0, 1);
         m_FFSeries->removePoints(0, 1);
         replace_num--;
    }
    m_FAbuffer.append(QPointF(ft.time, -ft.FA/*std::abs(ft.FA)*/));
    m_FBbuffer.append(QPointF(ft.time, -ft.FB/*std::abs(ft.FB)*/));
    m_FCbuffer.append(QPointF(ft.time, -ft.FC/*std::abs(ft.FC)*/));
    m_FDbuffer.append(QPointF(ft.time, -ft.FD/*std::abs(ft.FD)*/));
    m_FEbuffer.append(QPointF(ft.time, -ft.FE/*std::abs(ft.FE)*/));
    m_FFbuffer.append(QPointF(ft.time, -ft.FF/*std::abs(ft.FF)*/));

    // 更新曲线图
    if(replace_num)
    {


        m_FASeries->append(m_FAbuffer.back());
        m_FBSeries->append(m_FBbuffer.back());
        m_FCSeries->append(m_FCbuffer.back());
        m_FDSeries->append(m_FDbuffer.back());
        m_FESeries->append(m_FEbuffer.back());
        m_FFSeries->append(m_FFbuffer.back());
        // 实现横轴随时间滚动
        // 当前时间映射到绘图区域的坐标
        qreal timePosition = m_chart->mapToPosition(QPointF(ft.time, 0)).x();
        // 当前绘图区域最右侧的坐标
        qreal rightPosition = m_chart->plotArea().topRight().x();
        // 当前时间超出绘图区域右侧时滚动
        if (timePosition - rightPosition > 0) {
            m_chart->scroll(timePosition - rightPosition, 0);
        }

    }
    // 更新数值显示
    ui->FAcheckBox->setText(QString::number(/*std::abs(ft.FA)*/-ft.FA, 'f', 4));
    ui->FBcheckBox->setText(QString::number(/*std::abs(ft.FB)*/-ft.FB, 'f', 4));
    ui->FCcheckBox->setText(QString::number(/*std::abs(ft.FC)*/-ft.FC, 'f', 4));
    ui->FDcheckBox->setText(QString::number(/*std::abs(ft.FD)*/-ft.FD, 'f', 4));
    ui->FEcheckBox->setText(QString::number(/*std::abs(ft.FE)*/-ft.FE, 'f', 4));
    ui->FFcheckBox->setText(QString::number(/*std::abs(ft.FF)*/-ft.FF, 'f', 4));

//    QWidget::update();
    Sleep(20);
}

void motorstatusshowGroupBox::initTubeChart()
{
    m_chart = new QChart();
    m_chart->legend()->setAlignment(Qt::AlignLeft);
    QFont font = m_chart->legend()->font();
    font.setPointSizeF(10);
    m_chart->legend()->setFont(font);
    m_chart->legend()->setVisible(false);
    ui->SensorGraphChartView->setChart(m_chart);
    ui->SensorGraphChartView->setRenderHint(QPainter::Antialiasing);

    // 时间轴
    m_axisX = new QValueAxis(this);
    m_axisX->setRange(0, 10);
    m_chart->addAxis(m_axisX, Qt::AlignBottom);

    // 力坐标轴
    m_axisFY = new QValueAxis(this);
    m_axisFY->setRange(0, 600);
    m_chart->addAxis(m_axisFY, Qt::AlignLeft);

    // 张力曲线
    m_FASeries = new QLineSeries(this);
    m_FASeries->setName("FA");
    m_FASeries->setVisible(ui->FAcheckBox->isChecked());
    m_chart->addSeries(m_FASeries);
    m_FASeries->attachAxis(m_axisX);
    m_FASeries->attachAxis(m_axisFY);

    m_FBSeries = new QLineSeries(this);
    m_FBSeries->setName("FB");
    m_FBSeries->setVisible(ui->FBcheckBox->isChecked());
    m_chart->addSeries(m_FBSeries);
    m_FBSeries->attachAxis(m_axisX);
    m_FBSeries->attachAxis(m_axisFY);

    m_FCSeries = new QLineSeries(this);
    m_FCSeries->setName("FC");
    m_FCSeries->setVisible(ui->FCcheckBox->isChecked());
    m_chart->addSeries(m_FCSeries);
    m_FCSeries->attachAxis(m_axisX);
    m_FCSeries->attachAxis(m_axisFY);

    m_FDSeries = new QLineSeries(this);
    m_FDSeries->setName("FD");
    m_FDSeries->setVisible(ui->FDcheckBox->isChecked());
    m_chart->addSeries(m_FDSeries);
    m_FDSeries->attachAxis(m_axisX);
    m_FDSeries->attachAxis(m_axisFY);

    m_FESeries = new QLineSeries(this);
    m_FESeries->setName("FE");
    m_FESeries->setVisible(ui->FEcheckBox->isChecked());
    m_chart->addSeries(m_FESeries);
    m_FESeries->attachAxis(m_axisX);
    m_FESeries->attachAxis(m_axisFY);

    m_FFSeries = new QLineSeries(this);
    m_FFSeries->setName("FF");
    m_FFSeries->setVisible(ui->FFcheckBox->isChecked());
    m_chart->addSeries(m_FFSeries);
    m_FFSeries->attachAxis(m_axisX);
    m_FFSeries->attachAxis(m_axisFY);
}

void motorstatusshowGroupBox::updateLevelSignals(Leveling lv)
{
    SetLevelLamp(ui -> LevelButton1, lv.a);
    SetLevelLamp(ui -> LevelButton2, lv.b);
    SetLevelLamp(ui -> LevelButton3, lv.c);
    SetLevelLamp(ui -> LevelButton4, lv.d);
    SetLevelLamp(ui -> LevelButton5, lv.e);
    SetLevelLamp(ui -> LevelButton6, lv.f);
//    QWidget::update();
}

void motorstatusshowGroupBox::SetLevelLamp(QAbstractButton * button, int lvs)
{
    if(lvs)
    {
        button -> setIcon(QIcon("Image/green.png"));
    }
    else{
        button -> setIcon(QIcon("Image/red.png"));
    }
}

void motorstatusshowGroupBox::updateDeviation(std::vector<double> dev)
{
    ui->CurAB->setText(QString::number(dev[0], 'f', 3));
    ui->CurBC->setText(QString::number(dev[1], 'f', 3));
    ui->CurCA->setText(QString::number(dev[2], 'f', 3));
    ui->CurDE->setText(QString::number(dev[3], 'f', 3));
    ui->CurEF->setText(QString::number(dev[4], 'f', 3));
    ui->CurFD->setText(QString::number(dev[5], 'f', 3));
//    QWidget::update();
}

/************************************************/
// 点击复选框改变曲线可视状态

void motorstatusshowGroupBox::on_FAcheckBox_stateChanged(int arg10)
{
    m_FASeries->setVisible(arg10);
}

void motorstatusshowGroupBox::on_FBcheckBox_stateChanged(int arg11)
{
    m_FBSeries->setVisible(arg11);
}

void motorstatusshowGroupBox::on_FCcheckBox_stateChanged(int arg12)
{
    m_FCSeries->setVisible(arg12);
}

void motorstatusshowGroupBox::on_FDcheckBox_stateChanged(int arg110)
{
    m_FDSeries->setVisible(arg110);
}

void motorstatusshowGroupBox::on_FEcheckBox_stateChanged(int arg111)
{
    m_FESeries->setVisible(arg111);
}

void motorstatusshowGroupBox::on_FFcheckBox_stateChanged(int arg112)
{
    m_FFSeries->setVisible(arg112);
}

void motorstatusshowGroupBox::on_SetABtext_textChanged()
{
    emit SendDevset(ui->SetABtext->toPlainText().toDouble(),0);
}

void motorstatusshowGroupBox::on_SetBCtext_textChanged()
{
    emit SendDevset(ui->SetBCtext->toPlainText().toDouble(),1);
}

void motorstatusshowGroupBox::on_SetCAtext_textChanged()
{
    emit SendDevset(ui->SetCAtext->toPlainText().toDouble(),2);
}

void motorstatusshowGroupBox::on_SetDEtext_textChanged()
{
    emit SendDevset(ui->SetDEtext->toPlainText().toDouble(),3);
}

void motorstatusshowGroupBox::on_SetEFtext_textChanged()
{
    emit SendDevset(ui->SetEFtext->toPlainText().toDouble(),4);
}

void motorstatusshowGroupBox::on_SetFDtext_textChanged()
{
    emit SendDevset(ui->SetFDtext->toPlainText().toDouble(),5);
}

void motorstatusshowGroupBox::on_pushButton_clicked()
{
    std::vector<double> devset = {0,0,0,0,0,0};
    devset[0] = ui->SetABtext->toPlainText().toDouble();
    devset[1] = ui->SetBCtext->toPlainText().toDouble();
    devset[2] = ui->SetCAtext->toPlainText().toDouble();
    devset[3] = ui->SetDEtext->toPlainText().toDouble();
    devset[4] = ui->SetEFtext->toPlainText().toDouble();
    devset[5] = ui->SetFDtext->toPlainText().toDouble();
    emit SendDevvec(devset);
}

