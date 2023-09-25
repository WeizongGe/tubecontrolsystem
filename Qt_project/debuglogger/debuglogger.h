#ifndef DEBUGLOGGER_H
#define DEBUGLOGGER_H
#include <vector>
#include <QString>
#include <QObject>
#include <iostream>

class DebugLogger:public QObject
{
    Q_OBJECT;
public:
    QStringList list;

    explicit DebugLogger(QObject * parent = nullptr);
    DebugLogger(const DebugLogger & d);
    ~DebugLogger();
public slots:
    void ReceiveMsg(const QString& msg);
signals:
    void AddItem(const QString & msg);
};

#endif // DEBUGLOGGER_H
