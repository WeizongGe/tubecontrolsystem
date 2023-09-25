#include "debuglogger.h"

DebugLogger::DebugLogger(QObject * parent):QObject(parent)
{

}
DebugLogger::DebugLogger(const DebugLogger & d)
{
    list = d.list;
}

DebugLogger::~DebugLogger()
{

}

void DebugLogger::ReceiveMsg(const QString & msg)
{
    emit AddItem(msg);
}
