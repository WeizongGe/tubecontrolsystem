#include "profilecurvewidget.h"
#include "ui_profilecurvewidget.h"
#include<QDebug>

ProfileCurveWidget::ProfileCurveWidget(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::ProfileCurveWidget),
    mApp(tubeControlSystemApp::instance())
{
    ui->setupUi(this);

    pInter =  new CubicInter<double>;

    const QString prefix = "第";
    const QString sufix = "阶段曲线";
    for(unsigned i = 1; i < 7; ++i)
    {
        ui->comboBox->addItem(prefix + QString::number(i) + sufix);
    }
    on_comboBox_activated(ui->comboBox->currentText());

    InitChart();
}

void ProfileCurveWidget::InitChart()
{
    pchart = std::make_unique<QChart>(new QChart);
    pxAxis = std::make_unique<QValueAxis>(new QValueAxis(this));
    pyAxis = std::make_unique<QValueAxis>(new QValueAxis(this));
    pline  = std::make_unique<QLineSeries>(new QLineSeries);

    pxAxis->setTitleText("阶段规划时间/s");
    pyAxis->setTitleText("力/N");

    pchart->setTheme(QChart::ChartTheme::ChartThemeDark);
    pchart->addSeries(pline.get());
    pchart->addAxis(pxAxis.get(), Qt::AlignBottom);
    pchart->addAxis(pyAxis.get(), Qt::AlignLeft);
    pchart->legend()->setAlignment(Qt::AlignBottom);
    pline->attachAxis(pxAxis.get());
    pline->attachAxis(pyAxis.get());
    pline->setName("规划力曲线");
}

ProfileCurveWidget::~ProfileCurveWidget()
{
    delete ui;
}

/********************************************
 *              Helper Functions
 *
 *
 *
 * *****************************************/
int ProfileCurveWidget::IDX() const noexcept
{
    return ui->comboBox->currentIndex();
}

double ProfileCurveWidget::DesireTorque() const noexcept
{
    return ui->dTorVal->text().toDouble();
}

const QString getNumString(const QString & s)
{
    QString num;
    for(auto & c: s)
    {
        if('0' <= c && c <= '9')
        {
            num += c;
        }
        else if(num.size() > 0)
        {
            break;
        }
    }
    return num;
}

int getNum(const QString & s)
{
    int num = 0;
    for(auto & c: s)
    {
        num = num * 10 + c.unicode() - '0';
    }
    return num;
}

void ProfileCurveWidget::Draw()
{
    pline->clear();
    DrawFirst();
    DrawSecond();
    DrawThird();
    SetChart();
}

void ProfileCurveWidget::SetChart()
{

    pxAxis->setRange(0, times[0] + times[1] + 60.0);
    pyAxis->setRange(0, std::max(DesireTorque(), vals[0]) + 50.0);

    ui->figure->setChart(pchart.get());
    ui->figure->setRenderHint(QPainter::Antialiasing);
}

void ProfileCurveWidget::DrawFirst()
{
    constexpr static int count = 20;
    double delta = times[0]/ count;
    // 更新插值参数
    pInter->CalcPara(( IDX() == 0 ?
                           0.0:DesireTorque()),
                       vals[0],
                       times[0]);
    for(unsigned i = 0; i < count + 1; ++i)
    {
        double t = delta * i;
        double val = (*pInter)(t);
        pline->append(t, val);
    }
}

void ProfileCurveWidget::DrawSecond()
{
    constexpr static int count = 20;
    double delta = times[1]/ count;
    // 更新插值参数
    pInter->CalcPara(  vals[0],
                     (IDX() == 5 ?
                           0.0:DesireTorque()),
                       times[1]);
    for(unsigned i = 0; i < count + 1; ++i)
    {
        double t = delta * i;
        double val = (*pInter)(t);
        t += times[0];
        pline->append(t, val);
    }
}

void ProfileCurveWidget::DrawThird()
{
    constexpr static int count = 20;
    double delta = 60.0/ count;
    for(unsigned i = 0; i < count + 1; ++i)
    {
        double t = delta * i;
        double val = IDX() == 5? 0.0 : DesireTorque();
        t += times[0] + times[1];
        pline->append(t, val);
    }
}
/*************************************************
                Slot Functions


*************************************************/
void ProfileCurveWidget::ReceiveParameters(const vector<double>& vs,
                                           const vector<double>& ts)
{
    vals  = vs;
    times = ts;
    Draw();
}

void ProfileCurveWidget::on_comboBox_activated(const QString &arg1)
{
    int idx = getNum(getNumString(arg1));
    emit RequestParameters(idx);
}

void ProfileCurveWidget::on_dTorSlider_valueChanged(int value)
{
    double val = static_cast<double>(value) / ui->dTorSlider->maximum() * 3190.0;
    ui->dTorVal->setText(QString::number(val, 'f', 2));
    on_comboBox_activated(ui->comboBox->currentText());
}

