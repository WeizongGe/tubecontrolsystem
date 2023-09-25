#ifndef MSGBOXER_H
#define MSGBOXER_H

#include <QGroupBox>
#include <QMutex>
#include "model/tubeControlSystemApp.h"
#include "debuglogger/debuglogger.h"
namespace Ui {
class MsgBoxer;
}

class MsgBoxer : public QGroupBox
{
    Q_OBJECT
private:
    Ui::MsgBoxer *ui;
    tubeControlSystemApp * mApp;
// MEMBER FUNCTION:
public:
    QThread * msgThread;
    DebugLogger msgLogger;
    explicit MsgBoxer(QWidget *parent = nullptr);
    ~MsgBoxer();

private:
    int Size();
    QMutex mutex;
private slots:
    void AddItem(const QString & item);
    void on_clearButton_clicked();
signals:
    void ClearExtremum();
};

#endif // MSGBOXER_H
