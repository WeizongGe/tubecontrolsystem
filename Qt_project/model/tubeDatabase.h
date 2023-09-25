#ifndef tubeDatabase_H
#define tubeDatabase_H

#include <QObject>
#include <QSqlDatabase>
#include <QSqlQuery>
#include <QSqlTableModel>
#include <QTimer>
#include <QMessageBox>

#include "Force.h"
#include "tubeMotionParameter.h"

///
/// \brief The tubeDatabase class
/// This class is used to record data
///
class tubeDatabase : public QObject
{
    Q_OBJECT
public:
    explicit tubeDatabase(QObject *parent = nullptr);
    ~tubeDatabase();

    void exportData(QString &dbPath, QString &path, QString &table);

public slots:
    void saveSensorData(Force ft);
    void savetubeMotionParameter(const tubeMotionParameter &mp);

signals:

private:
    void init();
    void committubeDatabase();
    void closeDatabase();
    void bootDatabase();
    QSqlDatabase m_tubeDatabase;
    QSqlQuery m_SensorDataQuerry;
    QSqlQuery m_motionParameterQuerry;
    QString m_dbFilePath;
    QSqlTableModel *exportModel;
    QTimer m_timer;
public:
    QString dbDirPath;
    QString dbFilePath;
};

#endif // tubeDatabase_H
