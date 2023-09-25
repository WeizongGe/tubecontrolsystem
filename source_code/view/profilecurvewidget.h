#ifndef PROFILECURVEWIDGET_H
#define PROFILECURVEWIDGET_H

#include <QWidget>
#include <QChart>
#include <QValueAxis>
#include <QLineSeries>
#include <QChartView>
#include "model/tubeControlSystemApp.h"

namespace Ui {
class ProfileCurveWidget;
}

using QtCharts::QChart;
using QtCharts::QValueAxis;
using QtCharts::QLineSeries;
using QtCharts::QChartView;
using std::vector;
using std::unique_ptr;

class ProfileCurveWidget : public QWidget
{
    Q_OBJECT

/// Fields:
private:
    Ui::ProfileCurveWidget *ui;
    tubeControlSystemApp * mApp;
    Interpolation<double>* pInter;

    unique_ptr<QChart> pchart;
    unique_ptr<QValueAxis> pxAxis;
    unique_ptr<QValueAxis> pyAxis;
    unique_ptr<QLineSeries> pline;

    vector<double> vals;
    vector<double> times;

/// Signals:
signals:
    void RequestParameters(const int & idx);

/// Member Function:
public:
    explicit ProfileCurveWidget(QWidget *parent = nullptr);
    ~ProfileCurveWidget();
private:
    void Draw();
    void DrawFirst();
    void DrawSecond();
    void DrawThird();
    void SetChart();
    void InitChart();
    int IDX()const noexcept;
    double DesireTorque() const noexcept;
/// Slots Function:
public slots:
    void ReceiveParameters(const vector<double>& vs,
                           const vector<double>& ts);
private slots:
    void on_comboBox_activated(const QString &arg1);


    void on_dTorSlider_valueChanged(int value);
};

#endif // PROFILECURVEWIDGET_H
