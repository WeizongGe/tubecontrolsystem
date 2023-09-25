#ifndef MOTORSTATUSSHOWGROUPBOX_H
#define MOTORSTATUSSHOWGROUPBOX_H

#include <QGroupBox>
#include <QChart>
#include <QValueAxis>
#include <QLineSeries>
#include <QSplineSeries>
#include <QTimer>
#include <QChartView>
#include <tuple>
#include "model/tubeControlSystemApp.h"
#include <QMetaType>
#include <QMutex>

using namespace QtCharts;

namespace Ui {
class motorstatusshowGroupBox;
}

class motorstatusshowGroupBox : public QGroupBox
{
    Q_OBJECT
    QThread * DrawMotorThread;
public slots:
    void updatetubeMotionParameter(tubeMotionParameter mp);
    void updateSensorData(Force ft);//->append QPoint
    void updateSensorData2(Force ft);//->replace Qlist<QPoint>
    void updateLevelSignals(Leveling lv);
    void updateDeviation(std::vector<double> dev);

private slots:
    void on_AVelocitycheckBox_stateChanged(int arg1);
    void on_BVelocitycheckBox_stateChanged(int arg2);
    void on_CVelocitycheckBox_stateChanged(int arg3);
    void on_DVelocitycheckBox_stateChanged(int arg11);
    void on_EVelocitycheckBox_stateChanged(int arg22);
    void on_FVelocitycheckBox_stateChanged(int arg33);

    void on_ATorquecheckBox_stateChanged(int arg4);
    void on_BTorquecheckBox_stateChanged(int arg5);
    void on_CTorquecheckBox_stateChanged(int arg6);
    void on_DTorquecheckBox_stateChanged(int arg44);
    void on_ETorquecheckBox_stateChanged(int arg55);
    void on_FTorquecheckBox_stateChanged(int arg66);

    void on_ACurrentcheckBox_stateChanged(int arg7);
    void on_BCurrentcheckBox_stateChanged(int arg8);
    void on_CCurrentcheckBox_stateChanged(int arg9);
    void on_DCurrentcheckBox_stateChanged(int arg77);
    void on_ECurrentcheckBox_stateChanged(int arg88);
    void on_FCurrentcheckBox_stateChanged(int arg99);

    void on_FAcheckBox_stateChanged(int arg10);
    void on_FBcheckBox_stateChanged(int arg11);
    void on_FCcheckBox_stateChanged(int arg12);
    void on_FDcheckBox_stateChanged(int arg110);
    void on_FEcheckBox_stateChanged(int arg111);
    void on_FFcheckBox_stateChanged(int arg112);

    void on_SetABtext_textChanged();
    void on_SetBCtext_textChanged();
    void on_SetCAtext_textChanged();
    void on_SetDEtext_textChanged();
    void on_SetEFtext_textChanged();
    void on_SetFDtext_textChanged();
    void on_pushButton_clicked();

    void on_TotalAcheckBox_stateChanged(int arg1);

    void on_TotalDcheckBox_stateChanged(int arg1);

public:
    explicit motorstatusshowGroupBox(QWidget *parent = nullptr);
    ~motorstatusshowGroupBox();

private:
    Ui::motorstatusshowGroupBox *ui;

    void showEvent(QShowEvent *event);
    void initAChart();
    void initBChart();
    void initCChart();
    void initDChart();
    void initEChart();
    void initFChart();
    void initTubeChart();
    void SetSignalLamp(QList<QAbstractButton*> buttons, int val);
    void SetLevelLamp(QAbstractButton * button, int lvs);

    tubeControlSystemApp *m_app;

    QChart *m_Achart;

    QValueAxis *m_axisAX;
    QValueAxis *m_axisVelAY;
    QValueAxis *m_axistorAY;
    QValueAxis *m_axiscurAY;

    QLineSeries *m_AVelocitySeries;
    QLineSeries *m_ATorqueSeries;
    QLineSeries *m_ACurrentSeries;

    QChart *m_Bchart;

    QValueAxis *m_axisBX;
    QValueAxis *m_axisVelBY;
    QValueAxis *m_axistorBY;
    QValueAxis *m_axiscurBY;

    QLineSeries *m_BVelocitySeries;
    QLineSeries *m_BTorqueSeries;
    QLineSeries *m_BCurrentSeries;

    QChart *m_Cchart;

    QValueAxis *m_axisCX;
    QValueAxis *m_axisVelCY;
    QValueAxis *m_axistorCY;
    QValueAxis *m_axiscurCY;

    QLineSeries *m_CVelocitySeries;
    QLineSeries *m_CTorqueSeries;
    QLineSeries *m_CCurrentSeries;

    QChart *m_Dchart;

    QValueAxis *m_axisDX;
    QValueAxis *m_axisVelDY;
    QValueAxis *m_axistorDY;
    QValueAxis *m_axiscurDY;

    QLineSeries *m_DVelocitySeries;
    QLineSeries *m_DTorqueSeries;
    QLineSeries *m_DCurrentSeries;

    QChart *m_Echart;

    QValueAxis *m_axisEX;
    QValueAxis *m_axisVelEY;
    QValueAxis *m_axistorEY;
    QValueAxis *m_axiscurEY;

    QLineSeries *m_EVelocitySeries;
    QLineSeries *m_ETorqueSeries;
    QLineSeries *m_ECurrentSeries;

    QChart *m_Fchart;

    QValueAxis *m_axisFX;
    QValueAxis *m_axisVelFY;
    QValueAxis *m_axistorFY;
    QValueAxis *m_axiscurFY;

    QLineSeries *m_FVelocitySeries;
    QLineSeries *m_FTorqueSeries;
    QLineSeries *m_FCurrentSeries;

    QtCharts::QChart *m_chart;
    QValueAxis *m_axisX;
    QValueAxis *m_axisFY;
    QLineSeries *m_FASeries;
    QLineSeries *m_FBSeries;
    QLineSeries *m_FCSeries;
    QLineSeries *m_FDSeries;
    QLineSeries *m_FESeries;
    QLineSeries *m_FFSeries;
    QLineSeries *m_FABCSeries;
    QLineSeries *m_FDEFSeries;
    QList<QPointF> m_FAbuffer;
    QList<QPointF> m_FBbuffer;
    QList<QPointF> m_FCbuffer;
    QList<QPointF> m_FDbuffer;
    QList<QPointF> m_FEbuffer;
    QList<QPointF> m_FFbuffer;
    QList<QPointF> m_FABCbuffer;
    QList<QPointF> m_FDEFbuffer;

    int replace_num;
    int text_display_num;
    int text_display_num2;

    QMutex mutex;

signals:
    void SendDevset(double value, int mark);
    void SendDevvec(std::vector<double> devset);
};

#endif // MOTORSTATUSSHOWGROUPBOX_H
