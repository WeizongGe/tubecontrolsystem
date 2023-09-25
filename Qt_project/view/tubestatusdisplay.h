#ifndef TUBESTATUSDISPLAY_H
#define TUBESTATUSDISPLAY_H

#include <QGroupBox>
#include "model/tubeControlSystemApp.h"

namespace Ui {
class TubeStatusDisplay;
}

class TubeStatusDisplay : public QGroupBox
{
    Q_OBJECT
/// Fields:
public:

private:
    Ui::TubeStatusDisplay *ui;
    tubeControlSystemApp* mApp;
    QThread * tubeStatusThread;
/// Member Functoins:
public:
    explicit TubeStatusDisplay(QWidget *parent = nullptr);
    ~TubeStatusDisplay();

signals:
    void tubemotionModeUpdated(int &mode);
private slots:
    void ReceiveTubeState(const int state);
    void ReceiveReachedX(double ix);

};

#endif // TUBESTATUSDISPLAY_H
